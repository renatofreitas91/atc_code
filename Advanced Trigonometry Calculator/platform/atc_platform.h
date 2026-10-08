#pragma once

#include <cstddef>
#include <cstdint>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>
#endif

inline bool atcStringsEqualIgnoreCase(const char* left, const char* right) {
    if (left == nullptr || right == nullptr) return false;
#ifdef _WIN32
    return _stricmp(left, right) == 0;
#else
    return strcasecmp(left, right) == 0;
#endif
}

inline bool atcGetCurrentDirectory(char* output, std::size_t capacity) {
    if (output == nullptr || capacity == 0) return false;
#ifdef _WIN32
    const DWORD length = GetCurrentDirectoryA(static_cast<DWORD>(capacity), output);
    return length > 0 && length < capacity;
#else
    return getcwd(output, capacity) != nullptr;
#endif
}

inline bool atcIsInteractiveInput() {
#ifdef _WIN32
    return _isatty(_fileno(stdin)) != 0;
#else
    return isatty(fileno(stdin)) != 0;
#endif
}

inline bool atcEnterKeyPressed() {
#ifdef _WIN32
    return GetKeyState(VK_RETURN) < 0;
#else
    fd_set input;
    FD_ZERO(&input);
    FD_SET(STDIN_FILENO, &input);
    timeval timeout = { 0, 0 };
    return select(STDIN_FILENO + 1, &input, nullptr, nullptr, &timeout) > 0;
#endif
}

inline void atcClearKeyboardInput() {
#ifdef _WIN32
    while (_kbhit()) (void)_getche();
#else
    if (isatty(STDIN_FILENO)) tcflush(STDIN_FILENO, TCIFLUSH);
#endif
}

inline void atcFlushOutputStreams() {
#ifdef _WIN32
    _flushall();
#else
    std::fflush(nullptr);
#endif
}

inline bool atcOpenDesktopResource(const char* resource) {
    if (resource == nullptr || resource[0] == '\0') {
        return false;
    }
#ifdef _WIN32
    return reinterpret_cast<std::intptr_t>(
        ShellExecuteA(nullptr, "open", resource, nullptr, nullptr, SW_SHOW)) > 32;
#else
    const pid_t firstChild = fork();
    if (firstChild < 0) {
        return false;
    }
    if (firstChild == 0) {
        const pid_t detachedChild = fork();
        if (detachedChild < 0) _exit(127);
        if (detachedChild == 0) {
            execlp("xdg-open", "xdg-open", resource, static_cast<char*>(nullptr));
            _exit(127);
        }
        _exit(0);
    }
    int status = 0;
    return waitpid(firstChild, &status, 0) == firstChild &&
        WIFEXITED(status) && WEXITSTATUS(status) == 0;
#endif
}

inline bool atcOpenUrl(const char* url) {
    return atcOpenDesktopResource(url);
}

inline bool atcOpenFile(const char* path) {
    return atcOpenDesktopResource(path);
}

inline bool atcOpenDirectory(const char* path) {
    return atcOpenDesktopResource(path);
}

inline const char* atcExecutableFileName() {
#ifdef _WIN32
    return "atc.exe";
#else
    return "atc";
#endif
}

inline bool atcLaunchExecutable(const char* path) {
    if (path == nullptr || path[0] == '\0') {
        return false;
    }
#ifdef _WIN32
    return reinterpret_cast<std::intptr_t>(
        ShellExecuteA(nullptr, "open", path, nullptr, nullptr, SW_SHOW)) > 32;
#else
    const pid_t firstChild = fork();
    if (firstChild < 0) return false;
    if (firstChild == 0) {
        const pid_t detachedChild = fork();
        if (detachedChild < 0) _exit(127);
        if (detachedChild == 0) {
            execl(path, path, static_cast<char*>(nullptr));
            _exit(127);
        }
        _exit(0);
    }
    int status = 0;
    if (waitpid(firstChild, &status, 0) != firstChild) {
        return false;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        return false;
    }
    return true;
#endif
}

inline bool atcDirectoryExists(const char* path) {
    if (path == nullptr || path[0] == '\0') {
        return false;
    }
#ifdef _WIN32
    const DWORD attributes = GetFileAttributesA(path);
    return attributes != INVALID_FILE_ATTRIBUTES &&
        (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    struct stat info = {};
    return stat(path, &info) == 0 && S_ISDIR(info.st_mode);
#endif
}

inline bool atcCreateOneDirectory(const char* path) {
    if (atcDirectoryExists(path)) {
        return true;
    }
#ifdef _WIN32
    if (CreateDirectoryA(path, nullptr) != 0) {
        return true;
    }
    return GetLastError() == ERROR_ALREADY_EXISTS && atcDirectoryExists(path);
#else
    if (mkdir(path, 0777) == 0) {
        return true;
    }
    return errno == EEXIST && atcDirectoryExists(path);
#endif
}

inline bool atcCreateDirectories(const char* path) {
    if (path == nullptr || path[0] == '\0') {
        return false;
    }
    std::string current(path);
#ifndef _WIN32
    for (char& value : current) {
        if (value == '\\') value = '/';
    }
#endif
    for (std::size_t index = 1; index < current.size(); ++index) {
        if (current[index] != '/' && current[index] != '\\') continue;
#ifdef _WIN32
        if (index == 2 && current[1] == ':') continue;
#endif
        const char saved = current[index];
        current[index] = '\0';
        if (!atcCreateOneDirectory(current.c_str())) return false;
        current[index] = saved;
    }
    return atcCreateOneDirectory(current.c_str());
}

inline bool atcJoinPath(char* output, std::size_t capacity,
    const char* directory, const char* child) {
    if (output == nullptr || capacity == 0 || directory == nullptr || child == nullptr) {
        return false;
    }
#ifdef _WIN32
    const char separator = '\\';
#else
    const char separator = '/';
#endif
    const std::size_t length = std::strlen(directory);
    const bool hasSeparator = length > 0 &&
        (directory[length - 1] == '/' || directory[length - 1] == '\\');
    const int written = hasSeparator
        ? std::snprintf(output, capacity, "%s%s", directory, child)
        : std::snprintf(output, capacity, "%s%c%s", directory, separator, child);
    return written >= 0 && static_cast<std::size_t>(written) < capacity;
}

inline bool atcCopyString(char* output, std::size_t capacity, const char* value) {
    if (output == nullptr || capacity == 0 || value == nullptr) {
        return false;
    }
    const std::size_t sourceLength = std::strlen(value);
    const std::size_t copyLength = sourceLength < capacity - 1
        ? sourceLength : capacity - 1;
    std::memcpy(output, value, copyLength);
    output[copyLength] = '\0';
    return copyLength == sourceLength;
}

inline std::vector<std::string> atcListRegularFileNames(const char* directory) {
    std::vector<std::string> names;
    if (directory == nullptr || directory[0] == '\0') {
        return names;
    }
#ifdef _WIN32
    std::string pattern(directory);
    if (!pattern.empty() && pattern.back() != '/' && pattern.back() != '\\') {
        pattern += '\\';
    }
    pattern += '*';
    WIN32_FIND_DATAA data = {};
    HANDLE handle = FindFirstFileA(pattern.c_str(), &data);
    if (handle == INVALID_HANDLE_VALUE) {
        return names;
    }
    do {
        if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
            names.emplace_back(data.cFileName);
        }
    } while (FindNextFileA(handle, &data));
    FindClose(handle);
#else
    DIR* handle = opendir(directory);
    if (handle == nullptr) {
        return names;
    }
    while (dirent* entry = readdir(handle)) {
        if (entry->d_name[0] == '.' &&
            (entry->d_name[1] == '\0' ||
             (entry->d_name[1] == '.' && entry->d_name[2] == '\0'))) {
            continue;
        }
        std::string path(directory);
        if (!path.empty() && path.back() != '/') path += '/';
        path += entry->d_name;
        struct stat info = {};
        if (stat(path.c_str(), &info) == 0 && S_ISREG(info.st_mode)) {
            names.emplace_back(entry->d_name);
        }
    }
    closedir(handle);
#endif
    return names;
}

inline bool atcRemoveRegularFiles(const char* directory) {
    bool removedAll = true;
    const std::vector<std::string> names = atcListRegularFileNames(directory);
    for (const std::string& name : names) {
        std::vector<char> path(std::strlen(directory) + name.size() + 2);
        if (!atcJoinPath(path.data(), path.size(), directory, name.c_str()) ||
            std::remove(path.data()) != 0) {
            removedAll = false;
        }
    }
    return removedAll;
}

inline bool atcRemoveFileInDirectory(const char* directory, const char* fileName) {
    if (directory == nullptr || fileName == nullptr) return false;
    std::vector<char> path(std::strlen(directory) + std::strlen(fileName) + 2);
    if (!atcJoinPath(path.data(), path.size(), directory, fileName)) return false;
    if (std::remove(path.data()) == 0) return true;
    return errno == ENOENT;
}

inline int atcGetChar() {
#ifdef _WIN32
    return _getch();
#else
    static int pendingSpecialKey = -1;
    if (pendingSpecialKey >= 0) {
        const int value = pendingSpecialKey;
        pendingSpecialKey = -1;
        return value;
    }

    termios previous = {};
    const bool terminal = isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &previous) == 0;
    if (terminal) {
        termios raw = previous;
        raw.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }
    const int value = std::getchar();
    if (terminal) tcsetattr(STDIN_FILENO, TCSANOW, &previous);

    if (value == 27) {
        const int bracket = std::getchar();
        const int code = bracket == '[' ? std::getchar() : EOF;
        if (code == 'D') pendingSpecialKey = 75;
        else if (code == 'C') pendingSpecialKey = 77;
        else if (code == 'A') pendingSpecialKey = 72;
        else if (code == 'B') pendingSpecialKey = 80;
        if (pendingSpecialKey >= 0) return 224;
    }
    return value;
#endif
}

inline void atcBeep(unsigned int frequency, unsigned int durationMilliseconds) {
#ifdef _WIN32
    Beep(frequency, durationMilliseconds);
#else
    (void)frequency;
    (void)durationMilliseconds;
    std::fputc('\a', stdout);
    std::fflush(stdout);
#endif
}

inline void atcSetConsoleTitle(const char* title) {
    if (title == nullptr) return;
#ifdef _WIN32
    SetConsoleTitleA(title);
#else
    std::fputs("\033]0;", stdout);
    std::fputs(title, stdout);
    std::fputc('\a', stdout);
    std::fflush(stdout);
#endif
}

#ifndef _WIN32

#include <chrono>
#include <thread>

inline void atcSleepMilliseconds(unsigned long milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

inline char* atcGetsSecure(char* buffer, std::size_t capacity) {
    if (buffer == nullptr || capacity == 0) {
        return nullptr;
    }

    char* result = std::fgets(buffer, static_cast<int>(capacity), stdin);
    if (result != nullptr) {
        buffer[std::strcspn(buffer, "\r\n")] = '\0';
    }
    return result;
}

#define Sleep(milliseconds) atcSleepMilliseconds(milliseconds)
#define gets_s(buffer, capacity) atcGetsSecure((buffer), (capacity))

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

#endif
