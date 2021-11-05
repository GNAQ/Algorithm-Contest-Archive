@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
	bf.exe <in.in >bf.out
	H.exe <in.in >H.out
	
	fc bf.out H.out

if not errorlevel 1 goto loop
pause