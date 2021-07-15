@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe 
	std.exe <in.in >std.out
	K.exe <in.in >K.out
	
	fc K.out std.out

if not errorlevel 1 goto loop
pause