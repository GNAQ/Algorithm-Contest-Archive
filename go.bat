@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
    5std.exe <in.in >5std.out
    5.exe <in.in >5.out
	
    fc 5.out 5std.out

if not errorlevel 1 goto loop
pause
