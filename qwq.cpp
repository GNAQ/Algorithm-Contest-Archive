#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to;
}edge[200010];
int at=1,ptr[100010];

int mapx[110][110],Rid[110][110],Cid[110][110];
int n,m,MAX_RID,MAX_CID,empty_node;

template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
}

int mat[100010],vis[100010];
bool Hungary(int now,int src)
{
	for (int v=ptr[now];v;v=edge[v].pre) if (vis[now]!=src)
	{
		vis[now]=src;
		if (!mat[edge[v].to] || Hungary(mat[edge[v].to],src)) { mat[edge[v].to]=now; return true; }
	}
	return false;
}

void ProcessRC()
{
	// Process ROW -
	int Rid_tmp=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++) if (mapx[i][j]>0 && !Rid[i][j]) // unvisited
		{
			int pos=j; Rid[i][pos]=++Rid_tmp;
			while (mapx[i][pos+1]>0) 
			{
				pos++;
				Rid[i][pos]=Rid_tmp;
			}
		}
	}
	
	// Process COLUMN | 
	int Cid_tmp=MAX_RID=Rid_tmp;
	for (int i=1;i<=m;i++) 
	{
		for (int j=1;j<=n;j++) if (mapx[j][i]>0 && !Cid[j][i]) // unvisited
		{
			int pos=j; Cid[pos][i]=++Cid_tmp;
			while (mapx[pos+1][i]>0)
			{
				pos++;
				Cid[pos][i]=Cid_tmp;
			}
		}
	}
	MAX_CID=Cid_tmp;
}

void BuildGraph()
{
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			if (mapx[i][j]==1) // empty
			{
				Is(Rid[i][j],Cid[i][j]);
			}
		}
	}
}

int main()
{
	readx(n); readx(m); char ch=0; 
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			ch=0; while (ch!='#' && ch!='*' && ch!='x') ch=getchar();
			if (ch=='*')  // space
			{
				mapx[i][j]=1;
				empty_node++;
			}
			else if (ch=='#') mapx[i][j]=-1; // hard stone
			else mapx[i][j]=2; // soft stone
		}
	}
	
	ProcessRC();
	BuildGraph();
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			printf("%d%c",Rid[i][j]," \n"[j==m]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			printf("%d%c",Cid[i][j]," \n"[j==m]);
	
	int ans=0;
	for (int i=1;i<=MAX_RID;i++) ans+=Hungary(i,i);
	printf("%d\n",ans);
	printf("%d\n",MAX_CID-ans);
}
/*
4 4
#***
*#**
**#*
xxx#
*/