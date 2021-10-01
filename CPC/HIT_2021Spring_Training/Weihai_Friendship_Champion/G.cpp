#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
typedef long long ll;
using namespace std;

#define GNAQ_DEBUG

const int dx[4]={-1, 1, 0, 0}, dy[4]={0, 0, -1, 1}; // U D L R
const int vv[4][4]={2,0,1,3, 0,2,3,1, 3,1,2,0, 1,3,0,2};

struct ed
{
	int pre,to;
	ll c, w;
} edge[200010];
int at=1,ptr[20010];

int n,m, k,l;
ll val[110][110];
char gr[110][110];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v, ll c, ll w)
{
	#ifdef GNAQ_DEBUG
	cerr << "NewEdge: [" << u << "->" << v << "] by " << c << " | "<< w << endl;
	#endif
	
	at++;
	edge[at].pre=ptr[u];
	edge[at].to=v;
	edge[at].c=c;
	edge[at].w=w;
	ptr[u]=at;
	at++;
	edge[at].pre=ptr[v];
	edge[at].to=u;
	edge[at].c=0;
	edge[at].w=-w;
	ptr[v]=at;
}

namespace SPFA_MCMF
{
	queue<int> que;
	ll argu[20010], pre[20010]; ll minc[20010];
	bool vis[20010];
	int S, T;
	ll ansc, ansf;
	
	void Init(int ss, int tt)
	{
		ansc=0, ansf=0;
		while (!que.empty()) que.pop();
		memset(vis, 0, sizeof(vis));
		memset(argu, 0, sizeof(argu));
		memset(pre, 0, sizeof(pre));
		S=ss; T=tt;
	}
	
	bool SPFAFlow()
	{
		int cac;
		memset(minc, 0xc0, sizeof(minc));
		minc[S]=0; argu[S]=1e9;
		que.push(S);
		
		while (!que.empty())
		{
			cac=que.front(); que.pop(); vis[cac]=false;
			
			// cerr<<"SPFA "<<cac<<endl;
			// for (int i=1;i<=T;i++)
			// 	printf("%lld ", max(-3000LL, minc[i]));
			// putchar('\n');
			
			for (int v=ptr[cac];v;v=edge[v].pre)
			{
				// // cerr<<"$$"<<" "<<edge[v].to<<" "<<edge[v].pre<<" "<<v<<endl;
				if (edge[v].c && (minc[edge[v].to] < minc[cac]+edge[v].w)) // 这样跑最长路应该问题不大
				{
					int ev = edge[v].to; // // cerr<<"("<<cac<<" "<<ev<<")"<<endl;
					minc[ev]=minc[cac]+edge[v].w;
					argu[ev]=min(argu[cac], edge[v].c);
					pre[ev]=v;
					
					if (!vis[ev])
					{
						vis[ev]=true;
						que.push(ev);
					}
				}
			}
		}
		if (minc[T]==minc[T+2]) return false;
		
		ansf+=argu[T]; ansc+=argu[T]*minc[T]; cac=pre[T];
		while (cac)
		{
			edge[cac].c-=argu[T];
			edge[cac^1].c+=argu[T];
			cac=pre[edge[cac^1].to];
		}
		return true;
	}
}

void BuildG()
{
	SPFA_MCMF::Init(n*m*2+1, n*m*2+2);
	const int S = n*m*2+1, T = n*m*2+2;
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			// cerr<<"!"<<i<<" "<<j<<endl;
			
			if (gr[i][j]>='A' && gr[i][j]<='Z') // Ray Source
			{
				// cerr<<"Ray"<<endl;
				
				Is(S, (i-1)*m+j, 1, 0);
				int w;
				if (gr[i][j]=='U')
					w = 0;
				if (gr[i][j]=='D')
					w = 1;
				if (gr[i][j]=='L')
					w = 2;
				if (gr[i][j]=='R')
					w = 3;
				
				int ex,ey;
				for (int q=1; true; q++)
				{
					ex = i + q*dx[w];
					ey = j + q*dy[w];
					
					// cerr<<"#"<<ex<<" "<<ey<<endl;
					
					if (ex<1 || ex>n || ey<1 || ey>m) break;
					
					if (gr[ex][ey]=='.' || (gr[ex][ey]>='A' && gr[ex][ey]<='Z'))
						continue;
					else
					{
						Is((i-1)*m+j, (ex-1)*m+ey, 1, 0);
						break;
					}
				}
				
				
			}
			else if (gr[i][j]=='x') // gem
			{
				Is((i-1)*m+j, T, 1, val[i][j]);
			}
			else if (gr[i][j]=='#') // Wall
			{
				// Is((i-1)*m+j, T, 100000, 0);
			}
			else if (gr[i][j]=='v' || gr[i][j]=='^' || gr[i][j]=='>' || gr[i][j]=='<') // T Stone
			{
				// cerr<<"TS"<<endl;
				
				Is((i-1)*m+j, (i-1)*m+j+n*m, 1, 0);
				// U D L R
				for (int w=0;w<=3;w++)
				{
					int ex,ey;
					for (int q=1; true; q++)
					{
						ex = i + q*dx[w];
						ey = j + q*dy[w];
						
						if (ex<1 || ex>n || ey<1 || ey>m) break;
						
						if (gr[ex][ey]=='.' || (gr[ex][ey]>='A' && gr[ex][ey]<='Z'))
							continue;
						else
						{
							int vvid;
							if (gr[i][j]=='v') // 2 0 1 3 [0]
								vvid=0;
							if (gr[i][j]=='^') // 0 2 3 1 [1]
								vvid=1;
							if (gr[i][j]=='>') // 3 1 2 0 [2] 
								vvid=2;
							if (gr[i][j]=='<') // 1 3 0 2 [3]
								vvid=3;
							Is((i-1)*m+j+n*m, (ex-1)*m+ey, 1, -1*val[i][j]*vv[vvid][w]);
							break;
						}
					}
				}
			}
		}
	// cerr<<"Build OK."<<endl;
}

void Solve()
{
	scanf("%d%d%d%d", &n, &m, &k, &l);
	for (int i=1;i<=n;i++)
		scanf("%s", gr[i]+1);
	int ix, iy;
	for (int i=1;i<=k;i++)
	{
		scanf("%d%d", &ix, &iy);
		scanf("%lld", &val[ix][iy]);
	}
	for (int i=1;i<=l;i++)
	{
		scanf("%d%d", &ix, &iy);
		scanf("%lld", &val[ix][iy]);
	}
	
	BuildG();
	
	while (SPFA_MCMF::SPFAFlow());
	
	printf("%lld\n", max(0LL, SPFA_MCMF::ansc));
}

void Clear()
{
	at=1;
	memset(ptr, 0, sizeof(ptr));
	memset(gr, 0, sizeof(gr));
	memset(val, 0, sizeof(val));
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	return 0;
}