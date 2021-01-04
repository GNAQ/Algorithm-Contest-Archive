#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
typedef long long ll;
typedef long double Ldb;
using namespace std;

ll n,m,p;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

Ldb fastpow(Ldb a, ll pw)
{
	Ldb ret=1.0;
	for (;pw;pw>>=1, a=a*a) if (pw&1) ret*=a;
	return ret;
}

Ldb MyMin(Ldb a, Ldb b)
{
	if (b>a) return a;
	return b;
}

void Clear()
{
	
}

Ldb Calc(ll x)
{
	Ldb aa=0.0001, bb=1.0;
	aa*=p;
	return bb*(n*x+m)/(1-fastpow(bb-aa, x));
}

void Solve()
{
	
	readx(n); readx(m); readx(p);
	
	ll L=1,R=1000000000LL; Ldb ans=0;
	while (R-L>2)
	{
		ll M1, M2;
		M1=(R-L)/3+L;
		M2=((R-L)/3)*2+L;
		
		Ldb a1=Calc(M1);
		Ldb a2=Calc(M2);
		if (a1>a2)
			L=M1;
		else
			R=M2;
	}
	if (R-L==2)
	{
		ans=MyMin(MyMin(Calc(L), Calc(L+1)), Calc(R));
	}
	else
	{
		ans=MyMin(Calc(L), Calc(R));
	}
	printf("%.10Lf\n", ans);
	return;
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