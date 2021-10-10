#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=2e6+100;
int n,q,dat[MAXN],sum[MAXN],nxt[MAXN],ans[MAXN];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&dat[i]);
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+dat[i];
		for(int j=sum[i-1];j<=sum[i]-1;j++)
			nxt[j]=i-1;
	}
	for(int i=sum[n];i<=sum[n]+1e6;i++)
		nxt[i]=n;
	for(int delt=1;delt<=sum[n];delt++)
	{
		int pos=0;
		while(pos!=n)
		{
			if(pos==nxt[sum[pos]+delt])
			{
				ans[delt]=-1;
				break;
			}
			pos=nxt[sum[pos]+delt];
			ans[delt]++;
		}
	}
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		if(ans[tmp]==-1)
			printf("Impossible\n");
		else printf("%d\n",ans[tmp]);
	}
}

