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

const int UPLIM = 2000010;

ll phi2[UPLIM+10],mu2[UPLIM+10],phi[UPLIM+10],mu[UPLIM+10],mupfx[UPLIM+10];
ll phipfx[UPLIM+10];

ll n; bool vis[UPLIM+10];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int pnum[UPLIM+10],ptr;
bool nnum[UPLIM+10];
void PhiMuShake(int lim)
{
	phi[1]=1; nnum[1]=nnum[0]=1; mu[1]=1;
	for (int i=2;i<=lim;i++)
	{
		if (!nnum[i]) { mu[i]=-1; phi[i]=i-1; pnum[++ptr]=i; }
		for (int j=1;j<=ptr && pnum[j]*i<=lim;j++)
		{
			nnum[i*pnum[j]]=1; 
			if (!(i%pnum[j]))
			{
				phi[i*pnum[j]]=pnum[j]*phi[i];
				mu[i*pnum[j]]=0; break;
			}
			phi[i*pnum[j]]=phi[i]*phi[pnum[j]]; 
			mu[i*pnum[j]]=mu[i]*mu[pnum[j]];
		}
	}
	for (int i=1;i<=lim;i++) 
	{
		phipfx[i]=phipfx[i-1]+phi[i];
		mupfx[i]=mupfx[i-1]+mu[i];
	}
}

ll GetPhi(ll id)
{
	return (id<=UPLIM)?phipfx[id]:phi2[n/id];
}
ll GetMu(ll id)
{
	return (id<=UPLIM)?mupfx[id]:mu2[n/id];
}

void ApiaDu(ll now)
{
	ll t=n/now;
	if (now<UPLIM || vis[t]) return;
	vis[t]=1;
	
	phi2[t]=1LL*now*(now+1)/2; mu2[t]=1;
	for (ll l=2,r;l<=now;l=r+1)
	{
		r=now/(now/l); ApiaDu(now/l);
		phi2[t]-=1LL*(r-l+1)*GetPhi(now/l);
		mu2[t]-=1LL*(r-l+1)*GetMu(now/l);
	}
}

int main()
{
	PhiMuShake(UPLIM);
	int T; readx(T);
	
	while (T--)
	{
		readx(n); memset(vis,0,sizeof vis);
		if (n<=UPLIM) printf("%lld %lld\n",phipfx[n],mupfx[n]);
		else
		{
			ApiaDu(n); 
			printf("%lld %lld\n",GetPhi(n),GetMu(n));
		}
	}
}