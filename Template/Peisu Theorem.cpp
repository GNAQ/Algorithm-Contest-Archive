#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

ll n,seq[100010],ans;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll gcd(ll a1,ll a2)
{
	if (!a2) return a1;
	return gcd(a2,a1%a2);
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) readx(seq[i]);
	ans=abs(seq[1]); for (int i=2;i<=n;i++) ans=gcd(ans,abs(seq[i]));
	cout<<ans<<endl;
}
