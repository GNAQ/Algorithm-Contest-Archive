t = int(input())

for i in range(0, t):
	k = int(input())
	xr, yr, xls, yls, xrs, yrs = map(int, input().split())
	n = k-1
	h = abs(yr - yls)
	len = abs(xrs - xls)
	
	ans = h * ( 2 * len * (n-1) - 2 * len * (1.0-(0.5)**(n-1)) + len * (1.0 - (0.5)**n))
	print("%.3f" % ans)
