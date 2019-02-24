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
	
	int rev[400010],revt,revf;
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

int n,m;
ll F[400010],G[400010],A[400010],B[400010];

void Solve(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	Solve(l,mid);
	
	ll len=1; while (len<(r-l+1)*2) len<<=1;
	for (int i=0;i<len;i++) A[i]=B[i]=0;
	for (int i=l;i<=mid;i++) A[i-l]=F[i];
	for (int i=0;i<(r-l+1);i++) B[i]=G[i];
	
	FFT::NTT(A,len,1); FFT::NTT(B,len,1);
	for (int i=0;i<len;i++) A[i]=A[i]*B[i]%mod;
	FFT::NTT(A,len,-1);
	for (int i=mid+1;i<=r;i++) F[i]=(F[i]+A[i-l])%mod;
	
	Solve(mid+1,r);
}

int main()
{
	readx(n);
	for (int i=1;i<n;i++) readx(G[i]);
	F[0]=1; Solve(0,n-1);
	
	for (int i=0;i<n;i++) printf("%lld%c",F[i]," \n"[i==n-1]);
	
}
/*
10
2 456 32 13524543 998244352 0 1231 634544 51
*/

/*
1 2 460 1864 13738095 55389979 617768468 234028967 673827961 708520894
*/