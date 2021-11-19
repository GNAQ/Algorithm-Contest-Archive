#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<pair<int, ll>> ed[10010];

ll dis[4010][4010];
int n, m;
ll c;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v, ll w)
{
	ed[u].push_back(make_pair(v, w));
}

struct _Nd
{
	ll dis;
	int id;
	_Nd(ll _dis, int _id)
		: dis(_dis), id(_id) {}
	bool operator < (const _Nd &b) const
	{
		return dis > b.dis;
	}
};
priority_queue<_Nd> que;
bool vis[4010];

void Dijkstra(int s)
{
	memset(vis, 0, sizeof(vis));
	while (!que.empty()) que.pop();
	dis[s][s] = 0;
	_Nd cac = _Nd(0, s);
	que.push(cac);
	while (!que.empty())
	{
		cac = que.top(); que.pop();
		if (vis[cac.id]) continue;
		vis[cac.id] = 1;
		for (auto v : ed[cac.id])
		{
			if (dis[s][v.first] > dis[s][cac.id] + v.second)
			{
				dis[s][v.first] = dis[s][cac.id] + v.second;
				que.push(_Nd(dis[s][v.first], v.first));
			}
		}
	}
}

void Solve()
{
	for (int i=0;i<4010;i++)
		for (int j=0;j<4010;j++)
			dis[i][j] = 10000000000LL;
	int u, v, w; bool ok = 0;
	readx(n); readx(m); readx(c);
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v); readx(w);
		if (w <= c)
		{
			Is(u, v, w);
			ok = 1;
		}
	}
	
	if (!ok)
	{
		puts("0");
		return;
	}
	
	for (int i=1;i<=n;i++)
		Dijkstra(i);
	
	ll ans = 1000000000000LL;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) if (i!=j)
		{
			ans = min(ans, dis[i][j] + dis[j][i]);
		}
	
	if (ans > c)
	{
		puts("1");
	}
	else
	{
		puts("2");
	}
	return;
}


int main()
{
	Solve();
}