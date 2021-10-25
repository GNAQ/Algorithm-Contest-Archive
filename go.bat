@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
	L.exe <in.in >L.out
	std.exe <in.in >std.out
	
	fc L.out std.out

if not errorlevel 1 goto loop
pause