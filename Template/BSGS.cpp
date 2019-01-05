#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<set>
#include<map>
#define ll long long
using namespace std;

map<ll,int> vals;
ll A,B,P;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
}

ll fastpow(ll an,ll p,ll mod)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret%mod;
}

void Solve()
{
	readx(P); readx(A); readx(B); vals.clear();
	if (!(A%P)) { printf("Couldn't Produce!\n"); return; }
	ll upat=sqrt(P),nowval=1,mulval=fastpow(A,upat,P);
	
	for (int i=0;i<upat;i++) 
	{
		if (nowval==B) { printf("%d\n",i); return; }
		if (vals[nowval]) continue;
		vals[nowval]=i+1;
		nowval=nowval*A%P;
	}
	
	nowval=mulval; // A^{Ksqrt(M)}
	for (int k=1;k<=upat+1;k++)
	{
		ll inv=fastpow(nowval,P-2,P);
		ll tmp=inv*B%P;
		if (vals[tmp]!=0) { printf("%d\n",vals[tmp]-1+k*upat); return; }
		nowval=nowval*mulval%P;
	}
	printf("Couldn't Produce!\n");
}

int main()
{
	int T; readx(T);
	while (T--) Solve();
}