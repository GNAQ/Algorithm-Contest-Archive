#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<sstream>
typedef long long ll;
using namespace std;

// 3 ^ 19 = 1e9 + 1e8

ll pref[21];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an) if (p&1) ret=ret*an;
	return ret;
}

void Get(ll n, ll dig)
{
	// cerr << "Get " << n << " " << dig << endl;
	for (int i=dig-1;i>=0;i--)
	{
		// cerr << "!!" << fastpow(3, i) << endl;
		if (n >= fastpow(3, i)*2)
		{
			printf("6");
			n -= fastpow(3, i) * 2;
		}
		else if (n >= fastpow(3, i))
		{
			printf("3");
			n -= fastpow(3, i);
		}
		else 
		{
			printf("2");
		}
	}
}

int main()
{
	for (int i=1;i<=19;i++) pref[i]=fastpow(3, i);
	for (int i=1;i<=19;i++) pref[i]+=pref[i-1];
	
	ll n; readx(n);
	
	ll dig = 0;
	for (int i=1;i<=19;i++)
	{
		if (n<=pref[i] && n>pref[i-1])
		{
			dig = i;
		}
	}
	Get(n-pref[dig-1]-1, dig);
}