@echo off

set timer=0

:loop

set /a timer+=1
echo %timer%

maker1.exe
b1.exe
t1.exe

fc b1.out t1.out

if not errorlevel 1 goto loop
pause
goto loop
