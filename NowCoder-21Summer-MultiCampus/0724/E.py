from math import *

T: int = int(input())
EPS: float = 1e-3

for tt in range(1, T+1):
	input()
	n: int = int(input())
	ans = int( floor((n ** (1. / 3.) + EPS)) )
	
	# print(n, ans)
	
	for i in range(2, n):
		if ( (i**3) > n): 
			break
		k = i**2
		y = i**3
		while y <= n:
			
			x = k*y + int( (4*k+(k*k-4)*y*y) ** (1./2.) )
			x /= 2
			if (x > n):
				 break
			ans += 1
			# print("!!", x, y)
			(x, y) = (y, x)
	print(ans)