#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<iterator>
#include<ctime>
#define ll long long
using namespace std;

ll prime,opt;

template<typename int_t>
inline void readx(int_t& x)
{
	x=0; int_t k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
inline ll fastpow(ll a,ll p)
{
	ll ret=1;
	for (;p;p>>=1,a=(a*a)%prime) if (p&1) ret=(ret*a)%prime;
	return ret;
}
inline ll lowbit(ll xx) { return (xx&(-xx)); }

inline bool MillerRabin()
{
	ll prx=prime-1,u=prime-1,lim=0,pox,rec,a;
	
	lim=lowbit(u); u/=lim;
	for (int i=1;i<=50;i++)
	{
		a=rand()%prime; lim=lowbit(prx);
		while (!a) a=rand()%prime;
		pox=fastpow(a,u);
		for (;lim;lim>>=1)
		{
			rec=(pox*pox)%prime;
			if (rec==1 && pox!=prime-1 && pox!=1) return false;
			pox=rec; 
		}
		if (pox!=1) return false;
	}
	return true;
}

void Init()
{
	srand(time(0));
}

bool Qry(int p)
{
	prime=p;
	if (prime==2 || MillerRabin()) return 1;
	else return 0;
}

void Solve()
{
	ll n,ans=0;
	readx(n);
	if (n==1)
	{
		printf("1\n");
	}	
	else if (Qry(n))
	{
		printf("1\n");
	}
	else
	{
		printf("0\n");
	}
}
	
int main()
{
	Init();
	
	int T; readx(T);
	while (T--)
	{
		Solve();
	}
	
	return 0;
}
