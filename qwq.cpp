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
bool mapx[100][100];
const int wayx[4]={0,-1,0,1},wayy[4]={-1,0,1,0};

int dist[100][100];
bool vis[100][100];
queue<pair<int,int>> que;


//Funcs
template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool Ok(int x,int y)
{
	if (x<=0 || y<=0 || x>N || y>M) return false;
	return true;
}

bool Get_Dist(int sx,int sy)
{
	pair<int,int> cac1,cac2;
	if (!Ok(sx,sy) || !mapx[sx][sy]) return false;
	memset(dist,0x3f,sizeof dist);
	for (int i=1;i<=N;i++) for (int j=1;j<=M;j++) vis[i][j]=!mapx[i][j];
	
	que.push({sx,sy}); vis[sx][sy]=1; dist[sx][sy]=0;
	while (!que.empty())
	{
		cac1=que.front(); que.pop();
		
		for (int w=0;w<=3;w++) 
		{
			cac2.fst=cac1.fst+wayx[w]; cac2.snd=cac1.snd+wayy[w];
			if (Ok(cac2.fst,cac2.snd) && !vis[cac2.fst][cac2.snd])
			{
				que.push(cac2);
				vis[cac2.fst][cac2.snd]=1;
				dist[cac2.fst][cac2.snd]=dist[cac1.fst][cac1.snd]+1;
			}
		}
	}
	return true;
}

namespace SSSP
{
	queue<int> que;
	bool vis[100010];
	int cod[100][100][4],dis[100010];
	
	vector<pair<int,int>> edge[100010];
	void Is(int fx,int tx,int wx)
	{
		edge[fx].push_back({tx,wx});
		edge[tx].push_back({fx,wx});
	}
	void Build_Graph()
	{
		int x_1,x_2,y_1,y_2;
		for (int i=1;i<=N;i++)
			for (int j=1;j<=M;j++) if (mapx[i][j])
				for (int k=0;k<=3;k++)
				{
					for (int l=k+1;l<=3;l++)
					{
						x_1=i+wayx[k]; y_1=j+wayy[k]; x_2=i+wayx[l]; y_2=j+wayy[l];
						if (Ok(x_1,y_1) && Ok(x_2,y_2))
						{
							mapx[i][j]=0;
							if (Get_Dist(x_1,y_1) && dist[x_2][y_2]<=N+M+2) 
							{
							// 	cout<<"Is "<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<dist[x_2][y_2]<<endl;
								Is(cod[i][j][k],cod[i][j][l],dist[x_2][y_2]);
							}
							mapx[i][j]=1;
						}
					}
				}
		for (int i=1;i<=N;i++)
			for (int j=1;j<=M;j++) if (mapx[i][j])
				for (int k=0;k<=3;k++)
				{
					x_1=i+wayx[k]; y_1=j+wayy[k];
					if (Ok(x_1,y_1) && mapx[x_1][y_1]) 
					{
						// cout<<"Is "<<i<<" "<<j<<" "<<x_1<<" "<<y_1<<endl;
						Is(cod[i][j][k],cod[x_1][y_1][(k+2)%4],1);
					}
				}
	}
	
	void SPFA(int source)
	{
		int cac=0;
		memset(SSSP::dis,0x3f,sizeof(SSSP::dis)); SSSP::dis[source]=0;
		SSSP::que.push(source);
		while (!(SSSP::que.empty()))
		{
			cac=SSSP::que.front(); SSSP::que.pop();
			for (auto v:(SSSP::edge[cac]))
			{
				if (SSSP::dis[v.fst]>SSSP::dis[cac]+v.snd)
				{
					SSSP::dis[v.fst]=SSSP::dis[cac]+v.snd;
					if (!SSSP::vis[v.fst])
					{
						SSSP::vis[v.fst]=1;
						SSSP::que.push(v.fst);
					}
				}
			}
		}
	}
};

int main()
{
	readx(N); readx(M); readx(Q);
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++) readx(mapx[i][j]);
	
	int tmp_code=0;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++)
			for (int k=0;k<=3;k++) SSSP::cod[i][j][k]=++tmp_code;
	SSSP::Build_Graph();
	
	int tmpx,tmpy;
	while (Q--)
	{
		readx(e_x); readx(e_y);
		readx(s_x); readx(s_y); readx(t_x); readx(t_y);
		
		if (!mapx[e_x][e_y] || !mapx[s_x][s_y] || !mapx[t_x][t_y])
		{
			printf("-1\n"); 
			continue;
		}
		
		mapx[s_x][s_y]=0;
		Get_Dist(e_x,e_y);
		mapx[s_x][s_y]=1;
		// cout<<Get_Dist(e_x,e_y)<<endl;
		// for (int i=1;i<=N;i++) for (int j=1;j<=M;j++) printf("%d%c",dist[i][j]," \n"[j==M]);
		
		int ans=2*1e9,tans;
		for (int i=0;i<=3;i++) 
		{
			tmpx=s_x+wayx[i]; tmpy=s_y+wayy[i];
			if (!Ok(tmpx,tmpy) || !mapx[tmpx][tmpy]) continue;
			SSSP::SPFA(SSSP::cod[s_x][s_y][i]);
			
			tans=2*1e9;
			for (int j=0;j<=3;j++) 
				tans=min(tans,dist[tmpx][tmpy]+SSSP::dis[SSSP::cod[t_x][t_y][j]]);
			ans=min(ans,tans);
		}
		
		if (ans>=0x3f3f3f3f) printf("-1\n");
		else printf("%d\n",ans);
	}
	system("pause");
	return 0;
}