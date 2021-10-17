@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	py gen.py >in.in 
	I1.exe <in.in >I1.out
	bf.exe <in.in >bf.out
	
	fc I1.out bf.out

if not errorlevel 1 goto loop
pause