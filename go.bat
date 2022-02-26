@echo off

set timer = 1

:loop

	echo %timer%
	set /a timer = timer + 1
	
	gen.exe
    Bstd.exe <in.in >Bstd.out
    B.exe <in.in >B.out
	
    fc B.out Bstd.out

if not errorlevel 1 goto loop
pause
