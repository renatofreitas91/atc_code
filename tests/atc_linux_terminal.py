"""Isolated pseudo-terminal sessions for Linux ATC integration checks."""
import errno
import fcntl
import os
import pty
import re
import select
import shutil
import signal
import struct
import subprocess
import tempfile
import termios
import time
from pathlib import Path

SANITIZER_ERROR = re.compile(
    r'ERROR: (?:AddressSanitizer|LeakSanitizer)|runtime error:|'
    r'AddressSanitizer:DEADLYSIGNAL|LeakSanitizer has encountered|'
    r'Could not attach to thread|Failed suspending threads')


class TerminalSession:
    def __init__(self, executable, arguments=(), timeout=60, intro=False):
        self.executable = Path(executable).resolve(strict=True)
        self.arguments = list(arguments)
        self.timeout = timeout
        self.intro = intro
        self.output = bytearray()
        self.observations = []
        self.process = None
        self.master = None
        self.directory = None
        self.eof = False

    def __enter__(self):
        self.directory = tempfile.TemporaryDirectory(prefix='atc-terminal-')
        self.cwd = Path(self.directory.name)
        binary = self.cwd / 'atc'
        shutil.copy2(self.executable, binary)
        fixtures = {'mode.txt': '1', 'numSystems.txt': '0', 'siPrefixes.txt': '0',
                    'verboseResolution.txt': '0', 'actualTime.txt': '0',
                    'higherPrecision.txt': '0'}
        # ATC checks the existence of this flag, not its contents.
        if not self.intro:
            fixtures['aboutDisabled.txt'] = '1'
        for name, value in fixtures.items():
            (self.cwd / name).write_text(value)
        self.master, slave = pty.openpty()
        try:
            fcntl.ioctl(slave, termios.TIOCSWINSZ, struct.pack('HHHH', 30, 100, 0, 0))
            self.started = time.monotonic()
            self.deadline = self.started + self.timeout
            environment = os.environ.copy()
            environment.setdefault('ATC_TEST_DISABLE_EXTERNAL_OPEN', '1')
            self.process = subprocess.Popen(
                [str(binary), *self.arguments], cwd=self.cwd, stdin=slave,
                stdout=slave, stderr=slave, start_new_session=True, env=environment)
        except BaseException:
            os.close(self.master)
            self.master = None
            self.directory.cleanup()
            raise
        finally:
            os.close(slave)
        return self

    @property
    def text(self):
        return bytes(self.output).decode('utf-8', errors='replace')

    def read(self):
        if self.eof:
            time.sleep(0.02)
            return
        if not select.select([self.master], [], [], 0.1)[0]:
            return
        try:
            chunk = os.read(self.master, 65536)
        except OSError as error:
            if error.errno != errno.EIO:
                raise
            chunk = b''
        if not chunk:
            self.eof = True
            return
        self.output.extend(chunk)
        self.observations.append((len(self.output), time.monotonic() - self.started))

    def expect(self, predicate, description):
        while not predicate(bytes(self.output)):
            if time.monotonic() >= self.deadline:
                raise TimeoutError('Timed out waiting for ' + description)
            if self.eof and self.process.poll() is not None:
                raise AssertionError('Process ended before ' + description)
            self.read()

    def send(self, data):
        while data:
            written = os.write(self.master, data)
            data = data[written:]

    def finish(self):
        while self.process.poll() is None or not self.eof:
            if time.monotonic() >= self.deadline:
                raise TimeoutError('Timed out waiting for process exit')
            self.read()
        if self.process.returncode != 0:
            raise AssertionError(f'ATC exit code {self.process.returncode}')
        if SANITIZER_ERROR.search(self.text):
            raise AssertionError('Sanitizer or thread-suspension diagnostic')

    def __exit__(self, *exception):
        try:
            if self.process is not None and self.process.poll() is None:
                os.killpg(self.process.pid, signal.SIGTERM)
                try:
                    self.process.wait(timeout=2)
                except subprocess.TimeoutExpired:
                    os.killpg(self.process.pid, signal.SIGKILL)
                    self.process.wait(timeout=2)
        finally:
            if self.master is not None:
                os.close(self.master)
            if self.directory is not None:
                self.directory.cleanup()
