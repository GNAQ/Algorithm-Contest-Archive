#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

int n;
double coe[100],L,R;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

double f(double x)
{
	double sum=0;
	for (int i=n;i>=0;i--) sum=sum*x+coe[i];
	return sum;
}

double TriSearch(double l,double r)
{
	double ml,mr,tmp;
	for (int i=1;i<=40;i++)
	{
		tmp=(r-l)/3.0;
		ml=l+tmp; mr=r-tmp;
		if (f(ml)<f(mr)) l=ml;
		else r=mr;
	}
	return l;
}

int main()
{
	readx(n); scanf("%lf%lf",&L,&R);
	for (int i=n;i>=0;i--) scanf("%lf",&coe[i]);
	printf("%.5lf\n",TriSearch(L,R));
}
