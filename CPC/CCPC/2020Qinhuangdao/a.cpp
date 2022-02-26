#include <bits/stdc++.h>
typedef long long ll;
using namespace std;


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll gcd(ll a, ll b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

int main()
{
	int T; readx(T);
	for (int ti=1;ti<=T;ti++)
	{
		ll r, b;
		readx(r); readx(b);
		if (b==0)
		{
			if (r>=2)
				printf("Case #%d: 1/1\n", ti);
			else
				printf("Case #%d: 0/1\n", ti);
		}
		else if (r<2)
		{
			printf("Case #%d: 0/1\n", ti);
		}
		else
		{
			printf("Case #%d: %lld/%lld\n", ti, r*(r-1)/gcd((r+b)*(r+b-1), r*(r-1)), (r+b)*(r+b-1)/gcd((r+b)*(r+b-1), r*(r-1)));
		}
	}
	
	
}