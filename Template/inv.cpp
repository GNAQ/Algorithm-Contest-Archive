#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

ll n,inv[1000010],mod;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n); readx(mod);
	inv[1]=1;
	for (int i=2;i<=n;i++) inv[i]=(inv[mod%i]*(-(mod/i))%mod+mod)%mod;
	for (int i=1;i<=n;i++) printf("%d\n",inv[i]);
}
