@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
	M.exe <in.in >M.out
	std.exe <in.in >std.out
	
	fc M.out std.out

if not errorlevel 1 goto loop
pause