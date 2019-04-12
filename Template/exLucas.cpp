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
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void exgcd(ll a,ll b,ll& xx,ll& yy)
{
	if (!b) { xx=1; yy=0; return; }
	exgcd(b,a%b,yy,xx);
	yy-=(a/b)*xx;
}

ll gcd(ll a,ll b)
{
	if (!b) return a;
	return gcd(b,a%b);
}

ll fastpow(ll an,ll p,ll mod)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

ll exCRT(ll* pi,ll* ai,int siz)
{
	ll P=pi[1],A=ai[1];
	for (int i=2;i<=siz;i++)
	{
		ll x,y,G=gcd(P,pi[i]);
		
		exgcd(P,pi[i],x,y); 
		x=((A-ai[i])/G)*x%pi[i];
		
		A-=x*P; P=P*pi[i]/G;
		A=(A%P+P)%P;
	}
	return A;
}

ll inv(ll n,ll mod)
{
	ll xi,yi;
	exgcd(n,mod,xi,yi);
	return (xi%mod+mod)%mod;
}

ll GetFac(ll n,ll pk,ll pi)
{
	if (!n) return 1;
	ll ret=1;
	for (int i=2;i<=pk;i++)
		if (i%pi) ret=(ret*i)%pk;
	ret=fastpow(ret,n/pk,pk);
	for (int i=2;i<=n%pk;i++)
		if (i%pi) ret=(ret*i)%pk;
	return ret*GetFac(n/pi,pk,pi)%pk;
}

ll C(ll n,ll m,ll pk,ll pi)
{
	// cerr<<"C"<<n<<" "<<m<<" "<<pi<<" "<<pk<<endl;
	
	ll up=GetFac(n,pk,pi),d1=GetFac(m,pk,pi),d2=GetFac(n-m,pk,pi);
	ll tim=0;
	for (ll i=n;i>=1;i/=pi) tim+=i/pi;
	for (ll i=m;i>=1;i/=pi) tim-=i/pi;
	for (ll i=n-m;i>=1;i/=pi) tim-=i/pi;
	
	return up*inv(d1,pk)%pk*inv(d2,pk)%pk*fastpow(pi,tim,pk)%pk;
}

ll exLucas(ll n,ll m,ll p)
{
	ll* pi=new ll[10010];
	ll* ai=new ll[10010];
	ll pk=0,upat=sqrt(p)+1,pp=p,siz=0;
	for (int i=2;i<=upat;i++) if (!(pp%i))
	{
		pk=1; siz++;
		while (!(pp%i)) { pp/=i; pk*=i; }
		pi[siz]=pk; ai[siz]=C(n,m,pk,i);
	}
	if (pp>1) 
	{
		siz++;
		pi[siz]=pp; ai[siz]=C(n,m,pp,pp);
	}
	
	ll ret=exCRT(pi,ai,siz);
	delete[] pi; delete[] ai;
	return ret;
}

int main()
{
	ll n,m,p;
	readx(n); readx(m); readx(p);
	
	ll ret=exLucas(n,m,p);
	
	cout<<ret<<endl;
}