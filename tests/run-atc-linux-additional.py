#!/usr/bin/env python3
"""Run the 40 additional Linux regressions against the supplied ATC executable."""
import sys, importlib.util, re, tempfile, shutil, subprocess
from pathlib import Path
spec=importlib.util.spec_from_file_location('functional',Path(__file__).with_name('run-atc-linux-functional.py')); m=importlib.util.module_from_spec(spec);sys.modules['functional']=m;spec.loader.exec_module(m)
exe=Path(sys.argv[1]).resolve(); failures=0
cases=[m.Case('implicit','2pi','2pi',r'^#\d+=6\.28319$'),m.Case('implicit','parentheses','2(3+4)',r'^#\d+=14$'),m.Case('lists','minimum',r'min(3\_1\2)',r'^#\d+=-1$'),m.Case('lists','maximum',r'max(3\_1\2)',r'^#\d+=3$'),m.Case('precision','50 digit e','dp50dpmaxprece',r'^#\d+=2\.71828182845904523536028747135266249775724709369996$'),m.Case('precision','mp e','dp50dpe',r'^#\d+=2\.71828182845904523536028747135266249775724709369996$',files={'higherPrecision.txt':'1'})]
text=(Path(__file__).with_name('run-atc-regression.ps1')).read_text()
for name,expr,pattern,mode in re.findall(r'Name = "([^"]+)"; Expression = "([^"]+)"; Expected = "([^"]+)"; ModeValue = "([123])"',text):
 if expr.startswith('solver('): cases.append(m.Case('solver',name,expr,pattern,files={'mode.txt':mode}))
for c in cases:
 try: passed,rc,out=m.run_case(exe,c)
 except subprocess.TimeoutExpired: passed,rc,out=False,'timeout',''
 failures+=not passed; print('PASS' if passed else 'FAIL', c.name, 'input=',c.expression,'exit=',rc,'output=',repr(out),flush=True)
with tempfile.TemporaryDirectory() as d:
 p=Path(d); shutil.copy2(exe,p/'atc')
 for n,v in {'aboutDisabled.txt':'1','mode.txt':'1','numSystems.txt':'0','siPrefixes.txt':'0','verboseResolution.txt':'0','actualTime.txt':'0','higherPrecision.txt':'0','variables.txt':'x 1000 0'}.items(): (p/n).write_text(v)
 try:
  r=subprocess.run([str(p/'atc')],input=b'solver(x^2-12x-9)\nx=#0\nx^2-12x-9\nexit\n',cwd=p,capture_output=True,timeout=30)
  out=m.clean_output(r.stdout+r.stderr); vals=dict(re.findall(r'#(\d+)=([^\n]+)',out)); residual=float(vals.get('2','nan')); passed=r.returncode==0 and abs(residual)<=1e-8 and re.match(r'(-0\.708204|12\.7082)',vals.get('0','')) is not None
 except Exception as e: passed=False;out=str(e)
 failures+=not passed;print('PASS' if passed else 'FAIL','Newton residual <=1e-8',repr(out),flush=True)
print('SUMMARY',len(cases)+1,'failed=',failures);sys.exit(bool(failures))
