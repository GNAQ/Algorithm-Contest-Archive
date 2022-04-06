#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;
const int maxN = 200010;
const int maxE = 400010;

struct ed
{
	int pre, to, w, id;
}edge[maxE * 2];
int at, ptr[maxN];
int dis[maxN];

int n, m, vcnt;
int digit[maxN];

bool vis[maxN * 8];
struct ed2 { int to, w; };
vector<ed2> e2[maxN * 8];
int sol[maxN * 8];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v, int w, int id)
{
	edge[++at].pre = ptr[u];
	edge[at].to = v;
	edge[at].w = w;
	edge[at].id = id;
	ptr[u] = at;
}

void Dijkstra(int s)
{
	struct node1
	{
		int id, val;
		bool operator < (const node1 &b) const
			{ return this->val > b.val; }
	} c1, c2;
	queue<node1> que;
	
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0;
	c1.id = s; c1.val = dis[s]; que.push(c1);
	
	while (!que.empty())
	{
		c1 = que.front(); que.pop();
		if (vis[c1.id]) continue;
		vis[c1.id] = 1;
		for (int v=ptr[c1.id]; v; v=edge[v].pre)
			if (dis[c1.id] + edge[v].w < dis[edge[v].to])
			{
				dis[edge[v].to] = dis[c1.id] + edge[v].w;
				que.push(node1({edge[v].to, dis[edge[v].to]}));
			}
	}
}

void AddE(int u, int v, int w, int id)
{
	vector<int> tmp;
	while (id)
	{
		tmp.push_back(id % 10);
		id /= 10;
	}
	reverse(tmp.begin(), tmp.end());
	for (int i=1;i<w;i++)
	{
		++vcnt;
		e2[u].push_back(ed2({vcnt, tmp[i - 1]}));
		u = vcnt;
	}
	e2[u].push_back(ed2({v, tmp[w - 1]}));
}

void BFS(int s)
{
	struct node2
	{
		int id, preid, preord, w;
		bool operator < (const node2 &b) const
		{
			if (this->preord == b.preord)
				return this->w < b.w;
			return this->preord < b.preord;
		}
		bool operator == (const node2 &b) const
		{
			return (this->preord == b.preord) && (this->w == b.w);
		}
	};
	
	for (int i=1;i<=vcnt;i++) 
		vis[i] = 0;
	int c1, c2;
	queue<pair<int, int>> que; 
	que.push({s, 1});
	while (!que.empty())
	{
		vector<node2> nds; // nodes ordering of next level
		while (!que.empty())
		{
			c1 = que.front().first; c2 = que.front().second;
			que.pop();
			for (int v=0; v<e2[c1].size(); v++)
				nds.push_back({e2[c1][v].to, c1, c2, e2[c1][v].w}); 
							// id, preid, preord, w
		}
		
		sort(nds.begin(), nds.end());
		node2 prend = (node2){-1, -1, -1, -1};
		int ordcnt = 0;
		for (auto v: nds) if (!vis[v.id])
		{
			vis[v.id] = 1;
			if (!(v == prend))
				ordcnt++;
			prend = v;
			que.push({v.id, ordcnt});
			sol[v.id] = (1LL * sol[v.preid] * 10 + v.w) % mod;
		}
	}
}

int main()
{
	for (int i=1;i<=100010;i++)
	{
			 if (i <     10) digit[i] = 1;
		else if (i <    100) digit[i] = 2;
		else if (i <   1000) digit[i] = 3;
		else if (i <  10000) digit[i] = 4;
		else if (i < 100000) digit[i] = 5;
		else digit[i] = 6;
	}
	int u, v;
	readx(n); readx(m); vcnt = n;
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v);
		Is(u, v, digit[i], i); 
		Is(v, u, digit[i], i);
	}
	
	Dijkstra(1);

	for (int i=1;i<=n;i++)
		for (int v=ptr[i]; v; v=edge[v].pre) 
			if (dis[edge[v].to] == dis[i] + edge[v].w)
				AddE(i, edge[v].to, edge[v].w, edge[v].id);
	
	BFS(1);
	
	for (int i=2;i<=n;i++)
		printf("%d\n", sol[i]);
}