#include<algorithm>
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const int maxn=2e5+100;
int num[maxn],l[maxn],r[maxn],dat[maxn],ans[maxn];
map<int,int >vis;
int main()
{
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&l[i],&r[i]);
	int pos=1;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&dat[i]);
		// cout<<pos<<endl;
		vis[dat[i]]=1;
		if(pos!=n+1&&dat[i]<=r[pos]&&dat[i]>=l[pos])
			num[pos]++;
		while(pos!=n+1&&dat[i]>=r[pos])
		{
			pos++;
			if(dat[i]<=r[pos]&&dat[i]>=l[pos])
				num[pos]++;
		}
	}
	for(int i=1;i<=n;i++)
		if(num[i]>2) 
		{
			printf("impossible");
			return 0;
		}
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",num[i]);
	// cout<<endl;
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		if(num[i]<2)
		{
			while(num[i]!=2)
			{
				if(num[i+1]<2&&r[i]==l[i+1]&&(!vis[r[i]]))
				{
					num[i]++;
					num[i+1]++;
					vis[r[i]]=1;
					ans[++tot]=r[i];
				}
				else {
					int now_pos=r[i]-1;
					while(vis[now_pos])
						now_pos--;
					num[i]++;
					vis[now_pos]=1;
					ans[++tot]=now_pos;
				}
			}
		}
	}
	sort(ans+1,ans+tot+1);
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++)
		printf("%d ",ans[i]);
}