#include<stdio.h>
#include<string.h>
#include<math.h>
#define ll long long

int phi[100010],pnum[100010],ptr=0; char nnum[100010];
ll sphi[100010];

int A,B;
void readx(int* x)
{
	(*x)=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { (*x)=(*x)*10+ch-'0'; ch=getchar(); }
	(*x)*=k;
}

void Phi_Shake(int upat)
{
	phi[1]=1;
	for (int i=2;i<=upat;i++)
	{
		if (!nnum[i]) { pnum[++ptr]=i; phi[i]=i-1; }
		for (int j=1;j<=ptr && i*pnum[j]<=upat;j++)
		{
			nnum[i*pnum[j]]=1;
			if (!(i%pnum[j])) { phi[i*pnum[j]]=phi[i]*pnum[j]; break; }
			phi[i*pnum[j]]=phi[i]*(pnum[j]-1);
		}
	}
	
	for (int i=1;i<=upat;i++) sphi[i]=sphi[i-1]+(ll)phi[i];
}

int min(int a,int b) { return a<b?a:b; }

int main()
{
	Phi_Shake(100000);
	readx(&A); readx(&B);
	ll ans=0; int x=min(A,B);
	
	for (int l=1,r;l<=x;l=r+1)
	{
		r=min(A/(A/l),B/(B/l));
		ans+=(sphi[r]-sphi[l-1])*(ll)(A/l)*(ll)(B/l);
	}
	printf("%lld\n",ans*2-(ll)A*B);
}
