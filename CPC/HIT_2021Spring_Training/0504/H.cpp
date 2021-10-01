#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
typedef long long ll;
using namespace std;

int n;
double l[10010],p[10010],v[10010],H,S,V;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Solve()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lf%lf", &l[i], &p[i]);
		v[i]=pow(l[i], 3);
	}
	scanf("%lf%lf%lf", &S, &H, &V);
	
	double vd=0;
	
	for (int i=1;i<=n;i++)
	{
		if (p[i]>=1)
		{
			vd+=v[i];
		}
		else
		{
			vd+=p[i]*v[i];
		}
		
	}
	V+=vd;
	double h = V/S;
	h=min(h, H);
	printf("%.2lf\n", h);
}

void Clear()
{
	
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
	
	
}