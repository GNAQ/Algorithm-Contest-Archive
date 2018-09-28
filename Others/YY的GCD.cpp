#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

int G[10000100],mu[10000100],pnum[10000010],ptr; bool nnum[10000100];
ll smu[10000100];

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
void readx(ll& x)
{
	x=0; ll k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Eular_Shake(int upat)
{
	mu[1]=1;
	for (int i=2;i<=upat;i++)
	{
		if (!nnum[i]) { mu[i]=-1; pnum[++ptr]=i; }
		for (int j=1;j<=ptr && pnum[j]*i<=upat;j++)
		{
			nnum[i*pnum[j]]=1;
			if (!(i%pnum[j])) { mu[i*pnum[j]]=0; break; }
			mu[i*pnum[j]]=-mu[i];
		}
	}
	
	for (int i=1;i<=upat;i++) 
		for (int j=1;j<=ptr && i*pnum[j]<=upat;j++) G[i*pnum[j]]+=mu[i];
	for (int i=1;i<=upat;i++) smu[i]=smu[i-1]+(ll)G[i];
}

int main()
{
	Eular_Shake(10000000);
	int _T,A,B; readx(_T);
	while (_T--)
	{
		readx(A); readx(B);
		int x=min(A,B); ll ans=0;
		for (ll l=1,r;l<=x;l=r+1)
		{
			r=min(A/(A/l),B/(B/l));
			ans+=(smu[r]-smu[l-1])*(A/l)*(B/l);
		}
		printf("%lld\n",ans);
	}
}
