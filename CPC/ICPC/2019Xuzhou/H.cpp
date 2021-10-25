#include<algorithm>
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=2e5+100;
struct node{
	int id;
	int ID;
	int pos;
	bool friend operator <(node a,node b)
	{
		if(a.pos==b.pos) return a.id<b.id;
		else return a.pos<b.pos;
	}
}dat[MAXN<<1];
int col[MAXN],vis[MAXN];
queue<int>line;
queue<int>RES;
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,k,cnt=0,res;
		scanf("%d%d",&n,&k);res=k;
		while(!RES.empty())
			RES.pop();
		while(!line.empty())
			line.pop();
		for(int i=1;i<=k;i++)
			line.push(i);
		for(int i=1;i<=n;i++)
			vis[i]=col[i]=0;
		for(int i=1;i<=n;i++)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			dat[i].pos=l;
			dat[i].id=1;
			dat[i+n].pos=r;			
			dat[i+n].id=-1;
			dat[i].ID=dat[i+n].ID=i;
		}
		sort(dat+1,dat+n*2+1);
		int last=-1,ans=0;
		for(int i=1;i<=n*2;i++)
		{
			if(dat[i].id==1)
			{
				if(res==0) 
				{
					cnt++;
					RES.push(dat[i].ID);
				}
				else {
					int c=line.front();
					line.pop();res--;
					col[dat[i].ID]=c;
					if(res==0)
						last=dat[i].pos;
				}
			}
			else {
				if(!col[dat[i].ID])
				{
					cnt--;
					vis[dat[i].ID]=1;
					col[dat[i].ID]=1;
					continue;
				}
				if(res==0)
				{
					if(cnt) 
					{
						cnt--;
						int ID;
						while(!RES.empty())
						{
							ID=RES.front();
							RES.pop();
							if(!vis[ID])
								break;
						}
						col[ID]=col[dat[i].ID];
					}
					else {
						ans+=dat[i].pos-1-last+1;res++;
						line.push(col[dat[i].ID]);
					}
				}
				else {
					res++;
					line.push(col[dat[i].ID]);
				}
			}
		}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
		{
			if(i!=1) printf(" ");
			printf("%d",col[i]);
		}
		printf("\n");
	}
}