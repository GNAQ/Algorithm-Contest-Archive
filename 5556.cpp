#include<cstdio> // HDU5556
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

int n,m;
char g[20][20];
int vis[20][20];
bool appear[12];
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
vector<int> nset;

int BFS(int x, int y)
{
	queue<pair<int, int>> que;
	que.push(make_pair(x, y));
	
	int c[2]={0, 0};
	while (!que.empty())
	{
		pair<int, int> u = que.front();
		int ix = u.first, iy=u.second;
		que.pop();
		vis[ix][iy] = 1;
		c[(ix+iy)%2]++;
		
		for (int w=0; w<4; w++)
			if (!vis[ix+dx[w]][iy+dy[w]])
			{
				
			}
	}
	return max(c[0], c[1]);
}

void Solve()
{
	scanf("%d%d", &n, &m);
	char ch = '\n';
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			ch=getchar();
			while (ch=='\n' || ch==' ') ch=getchar();
			g[i][j]=ch;
		}
	
	int old_cnt = 0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (g[i][j]>='0' && g[i][j]<='9')
			{
				if (!appear[g[i][j]-'0'])
				{
					appear[g[i][j]-'0'] = 1;
					old_cnt++;
					nset.push_back(g[i][j]-'0');
				}
				vis[i][j]=-1;
			}
	
	int ans = 0, tans;
	for (int i=0;i<(1<<old_cnt);i++)
	{
		tans = 0;
		for (int j=1;j<=n;j++)
			for (int k=1;k<=m;k++)
				if (vis[j][k]!=-1) vis[j][k]=0;
		for (int j=0;j<old_cnt;j++) if (i&(1<<j)) 
		{
			tans++;
			
			for (int k=1;k<=n;k++)
				for (int l=1;l<=m;l++) if (g[k][l]-'0' == nset[j])
				{
					for (int w=0; w<4; w++)
						if (g[k+dx[w]][l+dy[w]]=='.')
							vis[k+dx[w]][l+dy[w]]=1;
				}
		}
		
		for (int j=1;j<=n;j++)
			for (int k=1;k<=m;k++) if (vis[j][k]==0)
			{
				tans+=BFS(j,k);
			}
		
	}
	
}

void Clear()
{
	
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		Solve();
		Clear();
	}
}