#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, ai[1000010];
vector<int> edge[1000010], ans;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v)
{
	edge[u].push_back(v);
}

stack<int> stk;
bool vis[1000010];
void DFS(int u)
{
	if (ans.size()) return;
	if (vis[u])
	{
		while (stk.top() != u)
		{
			ans.push_back(stk.top());
			stk.pop();
		}
		ans.push_back(u);
		return;
	}
	vis[u] = 1;
	stk.push(u);
	for (auto v: edge[u])
		DFS(v);
}

void Solve()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(ai[i]);
		Is(i, i - ai[i]);
	}
	
	for (int i=1;i<=n;i++)
		if (ai[i]==0)
		{
			printf("1\n%d\n", i);
			return;
		}
	
	for (int i=1;i<=n;i++) 
		DFS(i);
	
	printf("%d\n", ans.size());
	for (int i=0;i<ans.size();i++)
		printf("%d%c", ans[i], " \n"[i==ans.size()-1]);
}

void Clear()
{
	for (int i=1;i<=n;i++)
	{
		edge[i].clear();
		vis[i]=0;
	}
	while (!stk.empty()) stk.pop();
	ans.clear();
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
}