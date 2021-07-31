#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

double r,h,a,b;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


double f(double x)
{
	if (x*x+b*b/4-r*r<0) return -1;
	double m = sqrt((h-x)*(h-x)+a*a/4-r*r) + sqrt(x*x+b*b/4-r*r);
	return m*m;
}

int main()
{
	scanf("%lf%lf%lf%lf", &r, &a, &b, &h);
	
	if (2*r<b) 
	{
		printf("Drop\n");
	}
	else
	{
		printf("Stuck\n");
		double l=0,r=h, mid;
		double lim = (a-b)*(a-b)/4+h*h;
		
		// for (double i=l;i<=r;i+=0.1)
		// 	printf("%.1lf\n", f(i));
		// cout << endl << endl;
		
		for (int ii=1;ii<=5000;ii++)
		{
			mid = (l+r)/2;
			double res = f(mid);
			if (res<=lim) l=mid;
			else r=mid;
		}
		printf("%.12lf\n", mid);
	}
	
	return 0;
}