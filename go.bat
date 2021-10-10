@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
	05.exe <in.in >05.ans 2>05.out
	bf.exe <in.in >bf.ans 2>bf.out
	
	fc 05.ans bf.ans

if not errorlevel 1 goto loop
pause