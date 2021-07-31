@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
	B.exe <in.in >B.out
	bf.exe <in.in >bf.out
	
	fc B.out bf.out

if not errorlevel 1 goto loop
pause