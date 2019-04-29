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
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

// 万年没写 NTT 了
const ll mod=998244353;
ll n,a[500010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

namespace FFT
{
	const ll G=3;
	const ll iG=fastpow(3,mod-2);
	
	ll revf,revt,rev[500010];
	void BtFl(ll* y,ll len)
	{
		if (len!=revf)
		{
			revf=len; revt=-1; ll tmp=1;
			while (tmp<len) { tmp<<=1; revt++; }
			for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt);
		}
		for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
	}
	
	void NTT(ll* y,ll len,ll mode)
	{
		BtFl(y,len);
		for (int i=1;i<len;i<<=1)
		{
			const ll wn=fastpow((mode==1?G:iG),(i<<1)/(len-1));
			for (int j=0;j<len;j+=(i<<1))
			{
				ll w=1;
				for (int k=0;k<i;k++,w=w*wn%mod)
				{
					ll t1=y[j+k],t2=y[i+j+k];
					y[j+k]=(t1+t2)%mod;
					y[i+j+k]=(t1-t2+mod)%mod;
				}
			}
		}
	}
}

ll tmppoly[500010];
ll PolyInv(ll* A,ll* B,ll* C,ll _n)
{
	if (_n==1) { B[0]=fastpow(A[0],mod-2); return; }
	PolyInv(A,B,C,(_n+1)>>1);
	
	ll len=1; while (len<(_n<<1)) len<<=1;
	for (int i=0;i<len;i++) C[i]=A[i];
	for (int i=_n;i<len;i++) C[i]=0;
	
	FFT::NTT(C,len,1); FFT::NTT(B,len,1);
	for (int i=0;i<len;i++) B[i]=(2-B[i]*C[i]%mod+mod)%mod*B[i]%mod;
	FFT::NTT(B,len,-1);
	
	for (int i=_n;i<len;i++) B[i]=0;
}

ll t1[500010],t2[500010],t3[500010],dr;
ll l1[500010],l2[500010],r1[500010],r2[500010];

void Solve(ll l,ll r)
{
	if (l==r)
	{
		t1[0]=1; t1[1]=(mod-a[l]%mod)%mod; dr=1;
		t2[0]=1; return;
	}
	ll mid=(l+r)>>1,drl,drr;
	Solve(l,mid); drl=dr;
	for (int i=0;i<=drl;i++) l1[i]=t1[i];
	for (int i=0;i<drl;i++) l2[i]=t2[i];
	Solve(mid+1,r); drr=dr;
	for (int i=0;i<=drr;i++) r1[i]=t1[i];
	for (int i=0;i<drr;i++) r2[i]=t2[i];
	
	dr=drr+drl;
	ll len=1; while (len<=dr) len<<=1;
	for (int i=drl+1;i<len;i++) l1[i]=0;
	for (int i=drr+1;i<len;i++) r1[i]=0;
	
	FFT::NTT(l1,len,1); FFT::NTT(r1,len,1);
	for (int i=0;i<len;i++) t1[i]=l1[i]*r1[i]%mod;
	FFT::NTT(t1,len,-1); FFT::NTT(l1,len,-1); FFT::NTT(r1,len,-1);
	
	for (int i=dr+1;i<len;i++) t1[i]=0;
	
	len=1; while (len<dr) len<<=1;
	for (int i=drl;i<len;i++) l2[i]=0;
	for (int i=drr;i<len;i++) r2[i]=0;
	
	FFT::NTT(l1,len,1); FFT::NTT(r1,len,1);
	FFT::NTT(l2,len,1); FFT::NTT(r2,len,1);
	for (int i=0;i<len;i++)
	{
		t2[i]=l1[i]*r2[i]%mod;
		t3[i]=r1[i]*l2[i]%mod;
	}
	FFT::NTT(t2,len,-1); FFT::NTT(t3,len,-1);
	
	for (int i=0;i<len;i++) t2[i]=(t2[i]+t3[i])%mod;
	for (int i=dr;i<len;i++) t2[i]=0;
}

ll t2i[500010];

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) readx(a[i]);
	Solve(1,n);
	
	PolyInv(t2,t2i,tmppoly,n-1);
	
	int len=1; while (len<n*2) len<<=1;
	FFT::NTT(t2i,len,1); FFT::NTT(t1,len,1);
	for (int i=0;i<len;i++) t1[i]=t1[i]*t2i[i]%mod;
	FFT::NTT(t1,len,-1);
	
	ll ans=0;
	for (int i=1;i<=n;i++) ans^=t1[i];
	printf("%lld\n",ans);
}