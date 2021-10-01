@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
	F.exe <in.in >F.ans 2>F.out
	bf.exe <in.in >bf.ans 2>bf.out
	
	fc F.ans bf.ans

if not errorlevel 1 goto loop
pause