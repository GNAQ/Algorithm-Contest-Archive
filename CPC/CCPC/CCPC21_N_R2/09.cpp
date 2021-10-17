#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// nodes: n + m
// edges: 5m [2m(black) + 3m(red)]
struct _Ed
{
	int t, a, b, id;
	_Ed(int _t, int _a, int _b, int _id)
		: t(_t), a(_a), b(_b), id(_id)
	{}
	bool operator < (const _Ed &b) const
	{
		return this->a < b.a;
	}
};
vector<_Ed> ed1[300010];
vector<_Ed> ed2[300010];
int rcnt, n, m;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; } 
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

struct _Node
{
	ll dis; 
	int id;
	bool operator < (const _Node b) const
	{
		return this->dis > b.dis;
	}
};
priority_queue<_Node> que;
ll dis[300010]; bool vis[300010];

void Dijkstra()
{
	_Node cac1, cac2;
	for (int i=0;i<=rcnt;i++)
	{
		dis[i] = 10000000000000LL; 
		vis[i] = 0;
	}
	dis[1] = cac1.dis = 0; cac1.id = 1;
	que.push(cac1);
	while (!que.empty())
	{
		cac1 = que.top(); que.pop();
		if (vis[cac1.id]) 
			continue;
		vis[cac1.id] = 1;
		for (int i=0;i<ed2[cac1.id].size();i++)
		{
			int v = ed2[cac1.id][i].t;
			if (dis[v] > dis[cac1.id] + ed2[cac1.id][i].a)
			{
				dis[v] = dis[cac1.id] + ed2[cac1.id][i].a;
				cac2.id = v; cac2.dis = dis[v]; que.push(cac2);
			}
		}
	}
}

void Solve()
{
	readx(n); readx(m); int u, v, ai, bi;
	rcnt = n;
	for (int i=1;i<=m;i++) // (m initial)
	{
		readx(u); readx(v); readx(ai); readx(bi);
		ed1[u].push_back(_Ed(v, ai, bi, ++rcnt));
		ed2[u].push_back(_Ed(v, ai, bi, rcnt));
	}
	
	for (int i=1;i<=n;i++)
	{
		sort(ed2[i].begin(), ed2[i].end());
		sort(ed1[i].begin(), ed1[i].end());
	}
	
	// Build Red - Red Prefix Edges (m)
	for (int i=1;i<=n;i++) if (ed1[i].size() > 1)
	{
		for (int j=0;j<ed1[i].size()-1;j++)
		{
			u = ed1[i][j].id; 
			v = ed1[i][j+1].id;
			ed2[u].push_back(_Ed(v, 0, 0, -1));
		}
	}
	
	// Build Black-Red Edges (m)
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<ed1[i].size();j++)
		{
			u = i; v = ed1[i][j].t;
			vector<_Ed>::iterator targ = 
				upper_bound(ed1[v].begin(), ed1[v].end(), ed1[i][j]);
			if (targ != ed1[v].end())
				ed2[u].push_back(_Ed(targ->id, ed1[i][j].a, 0, -2));
			
		}
	}
	
	// Build Red-Black Edges (m)
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<ed1[i].size();j++)
		{
			u = ed1[i][j].id; // red node
			v = ed1[i][j].t;
			ed2[u].push_back(_Ed(v, ed1[i][j].a - ed1[i][j].b, 0, -3));
		}
	}
	
	// Build Red-Red Edges(m)
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<ed1[i].size();j++)
		{
			u = ed1[i][j].t;
			vector<_Ed>::iterator targ = 
				upper_bound(ed1[u].begin(), ed1[u].end(), ed1[i][j]);
			if (targ != ed1[u].end())
				ed2[ed1[i][j].id].push_back(_Ed(targ->id, ed1[i][j].a - ed1[i][j].b, 0, -4));
		}
	}
	
	Dijkstra();
	
	for (int i=1;i<=n;i++) 
		if (dis[i]==dis[0]) dis[i] = -1;
	
	for (int i=1;i<=n;i++) 
		printf("%lld%c", dis[i], " \n"[i==n]);
}

void Clear()
{
	for (int i=1;i<=rcnt;i++) 
	{
		ed1[i].clear();
		ed2[i].clear();
	}
	while (!que.empty()) que.pop();
	rcnt = 0;
}

int main()
{
	int T; readx(T);
	for (int i=1;i<=T;i++)
	{
		Solve();
		Clear();
	}
	return 0;
}