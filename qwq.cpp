#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

ll fac2[520], fac5[1953130];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p,ll mo)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mo) if (p&1) ret=ret*an%mo;
	return ret;
}

ll gcd(ll a1,ll a2)
{
	if (!a2) return a1;
	return gcd(a2,a1%a2);
}

void exgcd(ll a,ll b,ll& x,ll& y)
{
	if (!b) { x=1; y=0; return; }
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}

ll exCRT(ll* ai,ll* pi,ll len)
{
	ll P=pi[1],A=ai[1];
	for (int i=2;i<=len;i++)
	{
		ll x,y,G=gcd(P,pi[i]);
		// if ((A-ai)%G) return -1;
		
		exgcd(P,pi[i],x,y);
		x=x*((A-ai[i])/G)%pi[i];
		
		A-=x*P; P=P*(pi[i]/G);
		A=(A%P+P)%P;
	}
	return A;
}

ll Ginv(ll i,ll mo)
{
	ll x,y;
	exgcd(i,mo,x,y);
	return (x%mo+mo)%mo;
}

ll GetFac(ll _n,ll pk,ll pi)
{
	if (!_n) return 1;
	ll ret;
	if (pi == 2)
		ret = fac2[pk];
	else
		ret = fac5[pk];
	ret = fastpow(ret, _n / pk, pk);
	if (pi == 2)
		ret = ret * fac2[_n % pk] % pk;
	else
		ret = ret * fac5[_n % pk] % pk;
	return ret * GetFac(_n / pi, pk, pi) % pk;
}

ll GetExp(ll _n,ll _m,ll pi)
{
	ll tim=0;
	for (ll i=_n;i>=1;i/=pi) tim+=i/pi;
	for (ll i=_m;i>=1;i/=pi) tim-=i/pi;
	for (ll i=_n-_m;i>=1;i/=pi) tim-=i/pi;
	return tim;
}

ll exC(ll _n,ll _m,ll pk,ll pi)
{
	if (_m>_n) return 0;
	ll up=GetFac(_n,pk,pi),d1=GetFac(_m,pk,pi),d2=GetFac(_n-_m,pk,pi);
	ll c2=GetExp(_n,_m,2),c5=GetExp(_n,_m,5);
	
	ll ret=0;
	if (pi==2)
	{
		if (c5>=c2) 
			ret=up*Ginv(d1,pk)%pk*Ginv(d2,pk)%pk*fastpow(Ginv(5,pk),c2,pk)%pk;
		else 
			ret=up*Ginv(d1,pk)%pk*Ginv(d2,pk)%pk
					 *fastpow(Ginv(5,pk),c5,pk)%pk*fastpow(2,c2-c5,pk)%pk;
	}
	if (pi==5)
	{
		if (c2>=c5)
			ret=up*Ginv(d1,pk)%pk*Ginv(d2,pk)%pk*fastpow(Ginv(2,pk),c5,pk)%pk;
		else
			ret=up*Ginv(d1,pk)%pk*Ginv(d2,pk)%pk
					 *fastpow(Ginv(2,pk),c2,pk)%pk*fastpow(5,c5-c2,pk)%pk;
	}
	return ret;
}

ll exLucas(ll _n,ll _m,ll p)
{
	ll* pi=new ll[10010];
	ll* ai=new ll[10010];
	
	ll pk=0,pp=p,siz=0;
	for (int i=2;i<=5;i++) if (!(pp%i))
	{
		pk=1; siz++;
		while (!(pp%i)) { pp/=i; pk*=i; }
		pi[siz]=pk; ai[siz]=exC(_n,_m,pk,i);
	}
	if (pp>1)
	{
		siz++; 
		pi[siz]=pp; ai[siz]=exC(_n,_m,pp,pp);
	}
	
	ll ret=exCRT(ai,pi,siz);
	delete[] pi; delete[] ai;
	return ret;
}

ll p,n,m,K;

int main()
{
	fac2[0] = fac5[0] = 1;
	for (ll i = 1; i <= 512; i++)
		if (i % 2)
			fac2[i] = fac2[i - 1] * i % 512LL;
		else
			fac2[i] = fac2[i - 1];
	for (ll i = 1; i <= 1953125; i++)
		if (i % 5)
			fac5[i] = fac5[i - 1] * i % 1953125LL;
		else
			fac5[i] = fac5[i - 1];
	
	readx(m); readx(n); readx(K); p=1;
	for (int i=1;i<=K;i++) p*=10;
	n+=m;
	
	ll ans=exLucas(n,m,1000000000LL)%p;
	
	ll bits=0,tmp=ans;
	while (tmp) { tmp/=10; bits++; }
	for (int i=K;i>bits;i--) printf("0");
	printf("%lld\n",ans);
}