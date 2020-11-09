#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=1e3+100;
struct node{
	int x;
	int y;
}st;
queue<node>line;
int d[MAXN][MAXN][4],vis[MAXN][MAXN],n,m;
char ch[MAXN];
bool check(int x,int y)
{
	if(x<0||x>n+1) return 0;
	if(y<0||y>m+1) return 0;
	if(vis[x][y]) return 0;
	return 1;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch+1);
		for(int j=1;j<=m;j++)
		{
			if(ch[j]=='W')
				d[i-1][j][0]=1;
			if(ch[j]=='A')
				d[i][j-1][1]=1;
			if(ch[j]=='S')
				d[i+1][j][2]=1;
			if(ch[j]=='D')
				d[i][j+1][3]=1;
		}
	}
	for(int i=0;i<=m+1;i++)
	{
		st.x=0;st.y=i;
		line.push(st);
		vis[st.x][st.y]=1;
		st.x=n+1;st.y=i;
		vis[st.x][st.y]=1;
		line.push(st);
	}
	for(int i=1;i<=n;i++)
	{
		st.x=i;st.y=0;
		line.push(st);
		vis[st.x][st.y]=1;
		st.x=i;st.y=m+1;
		line.push(st);
		vis[st.x][st.y]=1;
	}
	while(!line.empty())
	{
		node now=line.front(),to;
		line.pop();
		if(d[now.x][now.y][0])
		{
			to.x=now.x+1;
			to.y=now.y;
			if(check(to.x,to.y))
			{
				vis[to.x][to.y]=1;
				line.push(to);
			}
		}
		if(d[now.x][now.y][1])
		{
			to.x=now.x;
			to.y=now.y+1;
			if(check(to.x,to.y))
			{
				vis[to.x][to.y]=1;
				line.push(to);
			}
		}
		if(d[now.x][now.y][2])
		{
			to.x=now.x-1;
			to.y=now.y;
			if(check(to.x,to.y))
			{
				vis[to.x][to.y]=1;
				line.push(to);
			}
		}
		if(d[now.x][now.y][3])
		{
			to.x=now.x;
			to.y=now.y-1;
			if(check(to.x,to.y))
			{
				vis[to.x][to.y]=1;
				line.push(to);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(vis[i][j])
				ans++;
		}
	cout<<ans;
}