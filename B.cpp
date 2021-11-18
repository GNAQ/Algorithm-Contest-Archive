#include <bits/stdc++.h>
typedef long long ll;
using namespace std;


struct TNode
{
	int l, r, fa;
	int ori_maxdep, rdep_need;
	int cur_deep; // this is the max depth of this entire subtree
	bool vis;
}nd[1000010];

int n, K, rt;

int DFS_init(int u)
{
	if (!u) return 0;
	nd[u].ori_maxdep = 1 + max(DFS_init(nd[u].l), DFS_init(nd[u].r));
	return nd[u].ori_maxdep;
}

void GetNode(int u)
{
	
}

bool Check(int u, int fa, int depneed, int curK)
{
	
}

void Mark(int u, int &curK)
{
	
}

int main()
{
	int u, v;
	scanf("%d%d", &n, &K);
	for (int i=1;i<=n;i++)
	{
		scanf("%d", &u);
		if (u == -1)
		{
			rt = i;
			continue;
		}
		nd[i].fa = u;
		if (u < i) nd[u].r = i;
		else nd[u].l = i;
	}
	
	DFS_init(rt);
	
	
}