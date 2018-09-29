#include<bits/stdc++.h>
using namespace std;

int n,opt;

bool nnum[10000010]={0};
int ctr1=0,pnum[8000010]={0};


inline void Eular_Shake()
{
	nnum[0]=nnum[1]=true;
	for (int i=2;i<=n;i++)
	{
		if (!nnum[i]) pnum[++ctr1]=i;
		for (int j=1;j<=ctr1 && pnum[j]*i<=n;j++)
		{
			nnum[i*pnum[j]]=true;
			if (!(i%pnum[j])) break;
		}
	}
}

int main()
{
	scanf("%d%d",&n,&opt);
	Eular_Shake();
	for (int i=1;i<=opt;i++)
	{
		scanf("%d",&n);
		if (!nnum[n]) printf("Yes\n");
		else printf("No\n");
	}
}
