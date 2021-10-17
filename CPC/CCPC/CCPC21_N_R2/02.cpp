#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const double eps = 1e-8;

void Solve()
{
	double a, b, c, xz, xo, yz, yo, yt;
	scanf("%lf%lf%lf", &a, &b, &c);
	scanf("%lf%lf%lf%lf%lf", &xz, &xo, &yz, &yo, &yt);
	
	double delt = b * b - 4 * a * (c - yz);
	
	if (delt<=0)
	{
		puts("No");
		return;
	}
	
	double xm = (b - sqrt(delt)) / (-2 * a), xM = (b + sqrt(delt)) / (-2 * a);
	
	if (xm>=xz && xm<=xo) 
	{
		puts("No");
		return;
	}
	
	if (xM>xz+eps && xM<xo-eps)
	{
		puts("Yes");
		return;
	}
	
	double yp = a * xo * xo + b * xo + c;
	if (yp>yt || yp<yo)
	{
		puts("No");
		return;
	}
	if (yp<=yt && yp>=yo)
	{
		double p = 2 * xo - xM;
		if (p>xz+eps && p<xo-eps)
		{
			puts("Yes");
			return;
		}
	}
	
	puts("No");
	return;
}


int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		Solve();
	}
	
	
	
}