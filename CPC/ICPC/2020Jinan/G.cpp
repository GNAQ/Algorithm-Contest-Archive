#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long ll;


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	ll x,y;
	
	readx(x); readx(y);
	
	ll hix,hiy;
	for (ll i=61;i>=0;i--)
	{
		if ( (x&(1LL<<i)) != 0)
		{
			hix=i;
			break;
		}
	}
	for (ll i=61;i>=0;i--)
	{
		if ( (y&(1LL<<i)) != 0)
		{
			hiy=i;
			break;
		}
	}
	
	if (hix==hiy)
	{
		printf("1\n");
		printf("%lld\n", x^y);
	}
	else
	{
		printf("2\n");
		ll x2=x^(1LL<<hix);
		printf("%lld ", x2^y);
		printf("%lld\n", (1LL<<hix));
	}
	return 0;
}