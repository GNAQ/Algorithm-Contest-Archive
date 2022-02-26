#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct ed
{
	int pre, to;
}edge[2000010];
int at, ptr[100010];

int n;

ll ans = 0;
int bn, pn2, pn1;

void Is(int fx, int tx)
{
	edge[at].pre = ptr[fx];
	edge[++at].to = tx;
	ptr[fx] = at;
}

namespace NDiv
{
	int hr, subsiz, msiz;
	bool vis[1000010];
	
	void Solve()
	{
		
	}
	
	void GetHr(int u)
	{
		
	}
	
	void DFS(int u)
	{
		
	}
};

int main()
{
	scanf("%d", &n);
	int u, v;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d", &u, &v);
		Is(u, v);
	}
	
}