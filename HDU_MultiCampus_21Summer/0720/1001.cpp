#include<bits/stdc++.h>
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


int main()
{
	ll T; readx(T);
	while (T--)
	{
		ll n; readx(n);
		if (n==1) printf("0\n");
		else
		{
			ll r = 1LL;
			while (r < n) r <<= 1LL;
			r>>=1LL;
			r--;
			printf("%lld\n", r);
		}
	}
	
	
	
}