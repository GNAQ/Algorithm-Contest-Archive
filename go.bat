@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
    Estd.exe <in.in >Estd.out
    5.exe <in.in >5.out
	
    fc 5.out Estd.out

if not errorlevel 1 goto loop
pause
