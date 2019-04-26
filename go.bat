@echo off

set timer=0

:loop

set /a timer+=1
echo %timer%

maker.exe
bf.exe < dat.in > bf.out
qwq2.exe < dat.in > dat.out

spj_cpp.exe
pause
goto loop
