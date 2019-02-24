#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<set>
#include<map>
typedef long long ll;
using namespace std;

const ll mod=998244353;
ll ans[100010];

template<typename inp_typ>
void readx(inp_typ& x)
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
	const ll iG=fastpow(G,mod-2);
	
	int rev[200010],revt,revf;
	template<typename poly_arr>
	void BtFl(poly_arr* y,int len)
	{
		if (len!=revf) 
		{
			revf=len; revt=-1; int tmp=1;
			while (tmp<len) { tmp<<=1; revt++; }
			for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt);
		}
		for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]);
	}
	
	void NTT(ll* y,int len,int mode)
	{
		BtFl(y,len);
		for (int i=1;i<len;i<<=1)
		{
			ll wn=fastpow((mode==1)?G:iG,(mod-1)/(i<<1));
			for (int j=0;j<len;j+=(i<<1))
			{
				ll w=1;
				for (int k=0;k<i;k++,w=w*wn%mod)
				{
					ll t1=y[j+k],t2=y[i+j+k]*w%mod;
					y[j+k]=(t1+t2)%mod;
					y[i+j+k]=(t1-t2+mod)%mod;
				}
			}
		}
		if (mode==-1)
		{
			ll inv=fastpow(len,mod-2);
			for (int i=0;i<len;i++) y[i]=y[i]*inv%mod;
		}
	}
};

namespace PCAL
{
	ll tmp_poly[1000010];
	
	void PolyInv(ll* A,ll* B,ll* C,int _n)
	{
		if (_n==1) { B[0]=fastpow(A[0],mod-2); return; }
		PolyInv(A,B,C,(_n+1)>>1);
		
		ll len=1;
		while (len<(_n<<1)) len<<=1;
		for (int i=0;i<len;i++) C[i]=A[i];
		for (int i=_n;i<len;i++) C[i]=0;
		
		FFT::NTT(B,len,1); FFT::NTT(C,len,1);
		for (int i=0;i<len;i++) B[i]=(2-C[i]*B[i]%mod+mod)%mod*B[i]%mod;
		FFT::NTT(B,len,-1);
		
		for (int i=_n;i<len;i++) B[i]=0;
	}

	void PolyDiv(ll* F,ll* G,ll* Ginv,ll* Q,ll* R,ll _n,ll _m) // n 次 || m 次
	{
		reverse(F,F+_n); reverse(G,G+_m);
		PolyInv(G,Ginv,tmp_poly,_n-_m+1);
		
		ll len=1; while (len<(_n + _n-_m+1)) len<<=1;
		for (int i=0;i<len;i++) Q[i]=F[i];
		FFT::NTT(Q,len,1); FFT::NTT(Ginv,len,1);
		for (int i=0;i<len;i++) Q[i]=Q[i]*Ginv[i]%mod;
		FFT::NTT(Q,len,-1);
		reverse(Q,Q+(_n-_m+1)); reverse(F,F+_n); reverse(G,G+_m);
		
		for (int i=0;i<(_n-_m+1);i++) R[i]=Q[i];
		len=1; while (len<(_m + _n-_m+1)) len<<=1;
		FFT::NTT(G,len,1); FFT::NTT(R,len,1);
		for (int i=0;i<len;i++) R[i]=R[i]*G[i]%mod;
		FFT::NTT(R,len,-1);
		for (int i=0;i<_m-1;i++) R[i]=(F[i]-R[i]+mod)%mod;
	}
}

namespace FEV
{
	using namespace FFT;
	
	// we must use vector (No!!!)
	vector<ll> P[64000*8];
	int deg[64000*8];
	ll tA[64000*8],tB[64000*8];
	void Init_FEPoly(int inx,int lx,int rx,ll* poly)
	{
		if (lx==rx)
		{
			P[inx].resize(2); deg[inx]=1;
			P[inx][0]=(mod-(poly[lx]%mod))%mod; P[inx][1]=1;
			return;
		}
		int mid=(lx+rx)>>1;
		Init_FEPoly(inx<<1,lx,mid,poly); Init_FEPoly(inx<<1|1,mid+1,rx,poly);
		
		// init size
		deg[inx]=deg[inx<<1]+deg[inx<<1|1]; P[inx].resize(deg[inx]+1);
		int len=1; while (len<=deg[inx]) len<<=1;
		// construct
		for (int i=0;i<deg[inx<<1];i++) tA[i]=P[inx<<1][i];
		for (int i=deg[inx<<1];i<len;i++) tA[i]=0;
		for (int i=0;i<deg[inx<<1|1];i++) tB[i]=P[inx<<1|1][i];
		for (int i=deg[inx<<1|1];i++) tB[i]=0;
		// mul
		NTT(tA,len,1); NTT(tB,len,1);
		for (int i=0;i<len;i++) tA[i]=tA[i]*tB[i]%mod;
		NTT(tA,len,-1);
		
		for (int i=0;i<deg[inx];i++) P[inx][i]=tA[i];
	}

	void FastEva()
	{
		
	}

};



int main()
{
	
	
	
}