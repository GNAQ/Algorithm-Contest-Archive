#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

double x_1,x_2,x_3,y_1,y_2,y_3,px,py,ex,ey;
const double eps = 1e-9;

bool dcmp(double x, double y)
{
	if (fabs(x - y) <= eps) return true;
	return false;
}

void Go()
{
	if (px==x_1 && py==y_1)
	{
		printf("%.12lf %.12lf\n", (x_2+x_3) / 2, (y_2+y_3) / 2);
		return;
	}
	if (px==x_2 && py==y_2)
	{
		printf("%.12lf %.12lf\n", (x_1+x_3) / 2, (y_1+y_3) / 2);
		return;
	}
	if (px==x_3 && py==y_3)
	{
		printf("%.12lf %.12lf\n", (x_2+x_1) / 2, (y_2+y_1) / 2);
		return;
	}
	
	bool ok = false;
	if (dcmp(0, (x_1-x_2)*(y_1-py) - (x_1-px)*(y_2-y_1)))
	{
		if (px>=min(x_1, x_2) && px<=max(x_1, x_2))
		{
			ok = true;
		}
	}
	else if (dcmp(0, (y_2-py)*(x_2-x_3)-(x_2-px)*(y_2-y_3)))
	{
		if (px>=min(x_3, x_2) && px<=max(x_3, x_2))
		{
			ok = true;
			swap(x_3,x_1); swap(y_3,y_1);
		}
	}
	else if (dcmp(0, (y_1-py)*(x_1-x_3)-(x_1-px)*(y_1-y_3)))
	{
		if (px>=min(x_3, x_1) && px<=max(x_3, x_1))
		{
			ok = true;
			swap(x_3,x_2); swap(y_3,y_2);
		}
	}
	if (!ok)
	{
		printf("-1\n");
		return;
	}
	
	double r;
	if (!dcmp(x_1, x_2)) r = (px - x_1) / (x_2 - x_1);
	else r = (py - y_1) / (y_2 - y_1);
	if (dcmp(r,0.5))
	{
		printf("%.12lf %.12lf\n", x_3,y_3);
	}
	else if (r > 0.5) // C 边
	{
		double q = 0.5 / r;
		ex = x_1 + q * (x_3-x_1);
		ey = y_1 + q * (y_3-y_1);
		printf("%.12lf %.12lf\n", ex, ey);
	}
	else
	{
		r = 1-r;
		double q = 0.5 / r;
		ex = x_2 + q * (x_3-x_2);
		ey = y_2 + q * (y_3-y_2);
		printf("%.12lf %.12lf\n", ex, ey);
	}
	return;
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x_1, &y_1, &x_2, &y_2,
		                                  &x_3, &y_3, &px, &py);
		Go();
	}
	return 0;
}