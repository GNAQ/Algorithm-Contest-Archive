@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
    stdF.exe <in.in >std.out
    6.exe <in.in >6.out
	checker.exe
	
    fc ok.out ck.out

if not errorlevel 1 goto loop
pause
