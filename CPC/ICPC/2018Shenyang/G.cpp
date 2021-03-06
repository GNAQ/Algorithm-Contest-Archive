#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<set>
typedef long long ll;
using namespace std;

vector< pair<int,int> > inx[10000005];
int n,m;
ll lans;
int G[6004][6004];


int wei[4][2]={1,1,1,-1,-1,1,-1,-1};

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Clear()
{
	lans=inx[0].size();
	for (int i=0;i<lans;i++)
		G[inx[0][i].first][inx[0][i].second]=0;
	inx[0].clear();
}

int main()
{
	for (register int x=0;x<=6000;x++)
		for (register int y=0;y<=6000;y++)
		{
			register ll tmp=x*x+y*y;
			if (tmp>10000000) break;
			
			inx[tmp].push_back( make_pair(x,y) );
		}
	
	int tt=0,T; readx(T);
	while (tt<T)
	{
		tt++; printf("Case #%d:\n",tt);
		readx(n); readx(m); 
		lans=0;
		
		int op,x0,y0,k,w;
		
		for (int i=1;i<=n;i++)
		{
			readx(x0); readx(y0); readx(w);
			G[x0][y0]+=w;
			inx[0].push_back( make_pair(x0,y0) );
		}
		
		for (int i=1;i<=m;i++)
		{
			set< pair<int,int> > pts;
			readx(op); readx(x0); readx(y0);
			x0=(x0+lans)%6000+1;
			y0=(y0+lans)%6000+1;
			
			if (op==1) 
			{
				readx(w);
				inx[0].push_back( make_pair(x0,y0) );
				G[x0][y0]+=w;
			}
			if (op==2)
			{
				G[x0][y0]=0;
			}
			if (op==3)
			{
				readx(k); readx(w); pts.clear(); 
				
				if (!k)
				{
					if (G[x0][y0]) G[x0][y0]+=w;
				}
				else
				{
					int siz=inx[k].size(), x1, y1;
					for (int i=0;i<siz;i++)
					{
						for (int z=0;z<4;z++)
						{
							x1=x0+wei[z][0]*inx[k][i].first;
							y1=y0+wei[z][1]*inx[k][i].second;
							if (x1<1 || y1<1 || x1>6000 || y1>6000) continue;
							pts.insert(make_pair(x1,y1));
						}
					}
					
					set< pair<int,int> >::iterator iter;
					iter=pts.begin();
					while (iter!=pts.end())
					{
						pair<int,int> tmp=*iter;
						if (G[tmp.first][tmp.second])
							G[tmp.first][tmp.second]+=w;
						iter++;
					}
				}
			}
			if (op==4)
			{
				readx(k);
				lans=0;
				
				if (!k) lans=G[x0][y0];
				else
				{
					int siz=inx[k].size(), x1, y1;
					
					for (int i=0;i<siz;i++)
					{
						for (int z=0;z<4;z++)
						{
							x1=x0+wei[z][0]*inx[k][i].first;
							y1=y0+wei[z][1]*inx[k][i].second;
							if (x1<1 || y1<1 || x1>6000 || y1>6000) continue;
							pts.insert(make_pair(x1,y1));
						}
					}
					
					set< pair<int,int> >::iterator iter;
					iter=pts.begin();
					while (iter!=pts.end())
					{
						pair<int,int> tmp=*iter;
						lans+=G[tmp.first][tmp.second];
						iter++;
					}
				}
				printf("%lld\n",lans);
			}
		}
		
		Clear();
	}
	
}