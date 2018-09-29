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
using namespace std;

int n,phi[100010]={0}; long long ans;
int ctr1,pnum[100010]={0};
bool vis[100010]={0};

inline int readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='0') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void PhiShake()
{
	phi[1]=1;
	for (int i=2;i<=n;i++) phi[i]=i-1;
	
	for (int i=2;i<=n;i++)
	{
		if (!vis[i]) pnum[++ctr1]=i;
		for (int j=1;j<=ctr1 && i*pnum[j]<=n;j++)
		{
			vis[i*pnum[j]]=true;
			if (!(i%pnum[j]))
			{
				phi[i*pnum[j]]=phi[i]*pnum[j];
				break;
			}
			else phi[i*pnum[j]]=phi[i]*(pnum[j]-1);
		}
	}
}

int main()
{
	readx(n);
	PhiShake();
	
	for (int i=1;i<=n;i++) printf("%d ",phi[i]); cout<<endl;
	
	if (n==1) { printf("0\n"); return 0; }
	
	for (int i=1;i<n;i++) ans+=phi[i];
	printf("%lld\n",ans*2+1);
	return 0;
}
