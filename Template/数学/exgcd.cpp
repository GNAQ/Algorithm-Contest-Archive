#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#define ll long long
using namespace std;

ll n,m,solx,soly;

inline void exgcd(ll a,ll b,ll& xx,ll& yy)
{
	if (!b) { xx=1; yy=0; }
	else
	{
		exgcd(b,a%b,yy,xx);
		yy-=xx*(a/b);
	}
}

int main()
{
	scanf("%lld%lld",&n,&m);
	exgcd(n,m,solx,soly);
	solx=((solx%m)+m)%m;
	cout<<solx<<endl;
	return 0;
}
