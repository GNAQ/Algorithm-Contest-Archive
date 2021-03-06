#include<stdio.h>
#include<math.h>
#include<string.h>
#define ll long long

int pnum[50010],ptr=0,smu[50010],mu[50010];
ll S[50010];
char nnum[50010];

void readx(ll* x)
{
	(*x)=0; ll k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { (*x)=(*x)*10+ch-'0'; ch=getchar(); }
	(*x)*=k;
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
	for (int i=1;i<=upat;i++) smu[i]=smu[i-1]+mu[i];
}
void Init_Divs(int upat)
{
	for (int i=1;i<=upat;i++)
		for (int l=1,r;l<=i;l=r+1)
		{
			r=(i/(i/l));
			S[i]+=1LL*(i/l)*(r-l+1);
		}
}

int min(int a1,int a2) { return a1<a2?a1:a2; }

int main()
{
	Eular_Shake(50000); Init_Divs(50000);
	ll A,B,_T; readx(&_T);
	while (_T--)
	{
		readx(&A); readx(&B);
		int chi=min(A,B); ll ans=0;
		
		for (int l=1,r;l<=chi;l=r+1)
		{
			r=min(A/(A/l),B/(B/l));
			ans+=(smu[r]-smu[l-1])*S[A/l]*S[B/l];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
