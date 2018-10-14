@echo off

set tim=0

:loop

set /a tim+=1
echo %tim%

maker.exe
t1.exe
b1.exe

fc t1.out b1.out

if not errorlevel 1 goto loop
pause
goto loop
