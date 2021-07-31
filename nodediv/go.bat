@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
	std.exe <in.in >std.out
	t1.exe <in.in >t1.out
	
	fc t1.out std.out

if not errorlevel 1 goto loop
pause