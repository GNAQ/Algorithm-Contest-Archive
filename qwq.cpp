#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

const ll mod=1000000007LL;
int n,m;
ll g[4000010],f[4000010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int pnum[3000010],ptr; ll phi[4000010],inv[4000010];
bool nnum[4000010];
void PhiShake(int lim)
{
	nnum[0]=nnum[1]=1;
	phi[1]=1;
	for (int i=2;i<=lim;i++)
	{
		if (!nnum[i]) { phi[i]=i-1; pnum[++ptr]=i; }
		for (int j=1;j<=ptr && pnum[j]*i<=lim;j++)
		{
			nnum[i*pnum[j]]=1;
			if (!(i%pnum[j]))
				{ phi[i*pnum[j]]=phi[i]*pnum[j]; break; }
			phi[i*pnum[j]]=phi[i]*phi[pnum[j]];
		}
	}
}

void Init(int lim)
{
	PhiShake(lim); inv[1]=1;
	for (int i=2;i<=lim;i++) inv[i]=(-1LL*(mod/i)*inv[mod%i]%mod+mod)%mod;
	for (int i=1;i<=lim;i++) 
	{
		f[i]=1LL*i*i%mod;
		g[i]=(g[i-1]+1LL*phi[i]*i%mod*i)%mod;
	}
}

namespace DS
{
	int BLKSIZ;
	ll blk[3010],blkid[4000010],blksum[4000010];

	void BlkInit()
	{
		BLKSIZ = ceil(sqrt(n+1));
		for (int i=1;i<=n;i++) blksum[i]=(blksum[i-1]+f[i])%mod;
		for (int i=0;i<=n;i++) blkid[i]=i/BLKSIZ;
	}
	
	void Upd(int pos,ll val)
	{
		int id=blkid[pos],rb=min(n+1,(id+1)*BLKSIZ);
		
		for (int i=pos;i<rb;i++) blksum[i]=(blksum[i]+val)%mod;
		for (int i=id+1;i<=blkid[n];i++) blk[i]=(blk[i]+val)%mod;
	}
	
	ll Qry(int pos)
	{
		return (blksum[pos]+blk[blkid[pos]])%mod;
	}
};

ll gcd(ll a1,ll a2)
{
	if (!a2) return a1;
	return gcd(a2,a1%a2);
}

ll Get(int lim)
{
	ll ret=0;
	for (int l=1,r;l<=lim;l=r+1)
	{
		r=lim/(lim/l); 
		ret=(ret+(DS::Qry(r)-DS::Qry(l-1)+mod)%mod*g[lim/l]%mod)%mod;
	}
	return (ret%mod+mod)%mod;
}

int main()
{
	freopen("dat.in","r",stdin);
	freopen("dat.out","w",stdout);
	
	readx(m); readx(n);
	Init(n);
	DS::BlkInit();
	
	int ai,bi,ki; ll val;
	while (m--)
	{
		readx(ai); readx(bi); ll d=gcd(ai,bi); readx(val); 
		
		val=val%mod*inv[ai/d]%mod*inv[bi/d]%mod;
		DS::Upd(d,val-f[d]); f[d]=val;
		
		readx(ki);
		printf("%lld\n",Get(ki));
	}
}