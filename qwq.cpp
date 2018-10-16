#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
#define fst first
#define snd second
using namespace std;

int N,M,Q,s_x,s_y,t_x,t_y,e_x,e_y;
bool mapx[50][50];
const int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};

int dist[50][50];
queue<pair<int,int>> qu;
queue<int> que;
bool vis[30010];
int cod[50][50][4],dis[30010];
vector<pair<int,int>> edge[30010];

//Funcs
template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
void Is(int fx,int tx,int wx) { edge[fx].push_back({tx,wx}); }

bool Get_Dist(int sx,int sy,int ex,int ey,int d)
{
	pair<int,int> c1,c2;
	memset(dist,-1,sizeof dist);
	
	qu.push({ex,ey}); dist[ex][ey]=0; dist[sx][sy]=1;
	while (!qu.empty())
	{
		c1=qu.front(); qu.pop();
		for (int w=0;w<=3;w++) 
		{
			c2.fst=c1.fst+dx[w]; c2.snd=c1.snd+dy[w];
			if (mapx[c2.fst][c2.snd] && dist[c2.fst][c2.snd]==-1)
			{
				qu.push(c2);
				dist[c2.fst][c2.snd]=dist[c1.fst][c1.snd]+1;
			}
		}
	}
	if (d==-1) return;
	
	int tmpx,tmpy;
	for (int i=0;i<=3;i++)
	{
		tmpx=sx+dx[i]; tmpy=sy+dy[i];
		if (!mapx[tmpx][tmpy] || dist[tmpx][tmpy]<=0) continue;
		Is(cod[sx][sy][d],cod[sx][sy][i],dist[tmpx][tmpy]);
	}
	Is(cod[sx][sy][d],cod[ex][ey][(d+2)%4],1);
}

void Build_Graph()
{
	int tmp_code=0;
	for (int i=1;i<=N;i++) for (int j=1;j<=M;j++) for (int k=0;k<=3;k++) cod[i][j][k]=++tmp_code;
	
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++) if (mapx[i][j])
			for (int w=0;w<=3;w++) if (mapx[i+dx[w]][j+dy[w]])
				Get_Dist(i,j,i+dx[w],j+dy[w],w);
}

void SPFA()
{
	int cac=0;
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	for (int i=0;i<=3;i++) if (mapx[s_x+dx[i]][s_y+dy[i]])
	{
		dis[cod[s_x][s_y][i]]=dist[s_x+dx[i]][s_y+dy[i]];
		que.push(cod[s_x][s_y][i]);
	}
	while (!(que.empty()))
	{
		cac=que.front(); que.pop();
		for (auto v:(edge[cac]))
			if (dis[v.fst]>dis[cac]+v.snd)
			{
				dis[v.fst]=dis[cac]+v.snd;
				if (!vis[v.fst])
				{
					vis[v.fst]=1;
					que.push(v.fst);
				}
			}
	}
}


int main()
{
	freopen("dat.in","r",stdin);
	freopen("dat.out","w",stdout);
	
	readx(N); readx(M); readx(Q);
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++) readx(mapx[i][j]);
	Build_Graph();
	
	int tmpx,tmpy;
	while (Q--)
	{
		readx(e_x); readx(e_y);
		readx(s_x); readx(s_y); readx(t_x); readx(t_y);
		
		if (!mapx[e_x][e_y] || !mapx[s_x][s_y] || !mapx[t_x][t_y]) { printf("-1\n");  continue; }
		if (s_x==t_x && s_y==t_y) { printf("0\n"); continue; }
		
		int ans=2*1e9;
		
		
		
	}
	// system("pause");
	return 0;
}