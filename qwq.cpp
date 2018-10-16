#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<string>
#include<cmath>
#include<iterator>
#include<vector>
#include<set>
#include<map>
#define ll long long
#define fst first
#define snd second
using namespace std;

int N,M,Q,s_x,s_y,t_x,t_y,e_x,e_y;
bool mapx[100][100];
const int wayx[4]={0,-1,0,1},wayy[4]={-1,0,1,0};

int dist[100][100],dp[100][100][4],cod[100][100][4];
bool vis[100][100];
queue<pair<int,int>> que;

vector<pair<int,int>> edge[100010];

//Funcs
template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
void Is(int fx,int tx,int wx)
{
	edge[fx].push_back({tx,wx});
	edge[tx].push_back({fx,wx});
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


void Build_Graph()
{
	int x_1,x_2,y_1,y_2;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++)
			for (int k=0;k<=3;k++)
			{
				for (int l=k+1;l<=3;l++)
				{
					x_1=i+wayx[k]; y_1=j+wayy[k]; x_2=i+wayx[l]; y_2=j+wayy[l];
					if (Ok(x_1,y_1) && Ok(x_2,y_2) && Get_Dist(x_1,y_1))
					{
						if (dist[x_2][y_2]) Is(cod[i][j][k],cod[i][j][l],dist[x_2][y_2]);
					}
				}
			}
}


int main()
{
	readx(N); readx(M); readx(Q);
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++) readx(mapx[i][j]);
	
	int tmp_code=0;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++)
			for (int k=0;k<=3;k++) cod[i][j][k]=++tmp_code;
	Build_Graph();
	
	while (Q--)
	{
		readx(e_x); readx(e_y);
		readx(s_x); readx(s_y); readx(t_x); readx(t_y);
		Get_Dist(e_x,e_y);
		// cout<<Get_Dist(e_x,e_y)<<endl;
		// for (int i=1;i<=N;i++) for (int j=1;j<=M;j++) printf("%d%c",dist[i][j]," \n"[j==M]);
		
		for (int i=0;i<=3;i++) dp[s_x][s_y][i]=0;
		
	}
	
	
}