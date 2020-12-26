@echo off

set timer = 1

:loop
	
	echo %timer%
	set /a timer = timer + 1
	
	gen.exe 
	f.exe <in.in >f.out
	
fc f.out std.out
if not errorlevel 1 goto loop
pause