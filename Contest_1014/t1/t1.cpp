#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#define ll long long
#define fst first
#define snd second
using namespace std;

int n,m,K;
pair<int,int> pnt[100010];
const ll mod=1000000007;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=(an*an)%mod) if (p&1) ret=(ret*an)%mod;
	return ret;
}

ll fac[100010],ifac[100010];
void Init_Fac()
{
	fac[0]=fac[1]=ifac[0]=1;
	for (int i=2;i<=100000;i++) fac[i]=(fac[i-1]*i)%mod;
	ifac[100000]=fastpow(fac[100000],mod-2);
	for (int i=99999;i;i--) ifac[i]=(ifac[i+1]*(i+1))%mod;
}

ll C(ll _n,ll _m) { return ((fac[_n]*ifac[_m])%mod*ifac[_n-_m])%mod; }

bool cmp(const pair<int,int>& a1,const pair<int,int>& a2)
{
	if (a1.fst==a2.fst) return a1.snd<a2.snd;
	return a1.fst<a2.fst;
}

void Std_Solve()
{
	ll ans=1;
	sort(pnt+1,pnt+K+1,cmp);
	
	pnt[0].fst=pnt[0].snd=1;
	pnt[K+1].fst=n; pnt[K+1].snd=m;
	
	int tmp_x,tmp_y;
	for (int i=1;i<=K+1;i++)
	{
		tmp_x=pnt[i].fst-pnt[i-1].fst;
		tmp_y=pnt[i].snd-pnt[i-1].snd;
		
		//No Sol
		if (tmp_x<0 || tmp_y<0)
		{
			printf("0\n");
			exit(0);
		}
		
		ans=(ans* C(tmp_x+tmp_y,tmp_x) )%mod;
	}
	
	printf("%lld\n",ans);
}

int main()
{
	freopen("t1.in","r",stdin);
	freopen("t1.out","w",stdout);
	
	readx(n); readx(m); readx(K);
	for (int i=1;i<=K;i++)
	{
		readx(pnt[i].fst);
		readx(pnt[i].snd);
	}
	Init_Fac();
	Std_Solve();
	return 0;
}