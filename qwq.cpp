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
#include<map>
#define ll long long
#define p_b push_back
#define fst first
#define snd second
using namespace std;

vector<pair<int,double>> edge[100010];
int node; double dis[100010];
bool vis[100010];
struct _Node
{
	int cod; double dis;
	bool operator < (const _Node& B) const { return dis>B.dis; }
};
priority_queue<_Node> que;

int ss,tt,prc1,prc2[110],n;

double Get_Dist(double x_1,double y_1,double x_2,double y_2) { return sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)); }
double CrossProd(double x_,double y_,double vx_1,double vy_1,double vx_2,double vy_2)
{
	vx_1-=x_; vy_1-=y_; vx_2-=x_; vy_2-=y_;
	return vx_1*vy_2-vy_1*vx_2;
}
struct _Square
{
	int x[5],y[5];
	void Make_Total()
	{
		if (CrossProd(x[0],y[0],x[1],y[1],x[2],y[2]))
		{
			x[4]=x[1]+(x[2]-x[0]);
			y[4]=y[1]+(y[2]-y[0]);
		}
		else if (CrossProd(x[1],y[1],x[0],y[0],x[2],y[2]))
		{
			x[4]=x[0]+(x[2]-x[1]);
			y[4]=y[0]+(y[2]-y[1]);
		}
		else
		{
			x[4]=x[1]+(x[0]-x[2]);
			y[4]=y[1]+(y[0]-y[2]);
		}
	}
	void Print() { for (int i=1;i<=4;i++) printf("(%d %d)%c",x[i],y[i]," \n"[i==4]); }
}Squ[120];

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
	edge[fx].p_b({tx,wx});
	edge[tx].p_b({fx,wx});
}

void Dijkstra(int source)
{
	memset(dis,0x43,sizeof dis); memset(vis,0,sizeof vis);
	_Node cac1,cac2;
	dis[source]=0; cac1.cod=source; cac1.dis=0; que.push(cac1);
	while (!que.empty())
	{
		cac1=que.top(); que.pop();
		if (vis[cac1.cod]) continue;
		for (auto v:edge[cac1.cod]) if (dis[v.fst]>dis[cac1.cod]+v.snd)
		{
			dis[v.fst]=dis[cac1.cod]+v.snd;
			cac2.cod=v.fst; cac2.dis=dis[v.fst];
			que.push(cac2);
		}
	}
}

void BuildGraph()
{
	for (int i=1;i<=n;i++) Squ[i].Make_Total();

	// for (int i=1;i<=n;i++) Squ[i].Print();

	//Insides
	int cnt=0;
	for (int w=1;w<=4*n;w+=4)
	{
		cnt++;
		for (int i=1;i<=3;i++) for (int j=i+1;j<=4;j++)
			Is(w+i-1,w+j-1,prc2[cnt]*Get_Dist(Squ[cnt].x[i],Squ[cnt].y[i],Squ[cnt].x[j],Squ[cnt].y[j]));
	}
	//Between
	for (int i=1;i<n;i++)
		for (int j=i+1;j<=n;j++)
			for (int w=1;w<=4;w++)
				for (int q=1;q<=4;q++)
					Is(4*(i-1)+w,4*(j-1)+q,prc1*Get_Dist(Squ[i].x[w],Squ[i].y[w],Squ[j].x[q],Squ[j].y[q]));
}


void Clear_All()
{
	memset(Squ,0,sizeof Squ);
	for (int i=1;i<=n;i++) vector<pair<int,double>> ().swap(edge[i]);
	memset(prc2,0,sizeof prc2);
	prc1=node=n=ss=tt=0;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		//Input
		readx(n); readx(prc1); readx(ss); readx(tt);
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=3;j++) { readx(Squ[i].x[j]); readx(Squ[i].y[j]); }
			readx(prc2[i]);
		}
		BuildGraph();
		
		double ans=1e12;
		for (int i=4*(ss-1)+1;i<=4*ss;i++)
		{
			Dijkstra(i);
			for (int j=4*(tt-1)+1;j<=4*tt;j++) ans=min(ans,dis[j]);
		}
		printf("%.2lf\n",ans);
		Clear_All();
	}
	return 0;
}
