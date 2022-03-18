@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
    std.exe <in.in >std.out
    H.exe <in.in >H.out
	
    fc H.out std.out

if not errorlevel 1 goto loop
pause
