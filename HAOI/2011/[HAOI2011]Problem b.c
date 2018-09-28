#include<math.h>
#include<stdio.h>
#define ll long long

int mu[50010],smu[50010],pnum[50010],ptr; char nnum[50010];
int T,N;

void readx(int* x)
{
	(*x)=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { (*x)=(*x)*10+ch-'0'; ch=getchar(); }
	(*x)*=k;
}

void Eular_Shake(int upat)
{
	mu[1]=1;
	for (int i=2;i<=upat;i++)
	{
		if (!nnum[i]) { pnum[++ptr]=i; mu[i]=-1; }
		for (int j=1;j<=ptr && pnum[j]*i<=upat;j++)
		{
			nnum[pnum[j]*i]=1;
			if (!(i%pnum[j])) { mu[i*pnum[j]]=0; break; }
			mu[i*pnum[j]]=-mu[i];
		}
	}
	for (int i=1;i<=upat;i++) smu[i]=smu[i-1]+mu[i];
}

int min(int a,int b) { if (a<b) b=a; return b; }

int Get_Ans(int A,int B)
{
	if ((!A) || (!B)) return 0;
	
	int x=min(A/N,B/N),ret=0;
	for (int l=1,r;l<=x;l=r+1)
	{
		r=min(A/(A/l),B/(B/l));
		ret+=(smu[r]-smu[l-1])*(A/(N*l))*(B/(N*l));
	}
	return ret;
}

int main()
{
	readx(&T); Eular_Shake(50000);
	while (T--)
	{
		int a,b,c,d;
		readx(&a); readx(&b); readx(&c); readx(&d); readx(&N);
		printf("%d\n",Get_Ans(b,d)-Get_Ans(b,c-1)-Get_Ans(a-1,d)+Get_Ans(a-1,c-1));
	}
}
