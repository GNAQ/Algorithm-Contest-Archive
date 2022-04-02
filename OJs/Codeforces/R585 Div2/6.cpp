#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int maxE = 800010 * 12;
const int maxN = 800010 * 2;

struct ed
{
	int pre, to;
} edge[maxE];
int at, ptr[maxN];

int dfn[maxN], low[maxN], pcnt;
bool in_s[maxN]; stack<int> stk;

int scc[maxN], totscc, disw[maxN];

int varcnt, n, M, m, C;
int Li[maxN], Ri[maxN], sol[maxN];

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
	edge[++at].pre = ptr[u];
	edge[at].to = v;
	ptr[u] = at;
}

void AddCond(int a, int b) // a or b
{
	Is(a > varcnt ? a - varcnt : a + varcnt, b);
	Is(b > varcnt ? b - varcnt : b + varcnt, a);
}

void Tarjan(int u)
{
	dfn[u] = low[u] = ++pcnt;
	in_s[u] = 1; stk.push(u);
	for (int v = ptr[u]; v; v = edge[v].pre)
	{
		if (!dfn[edge[v].to])
		{
			Tarjan(edge[v].to);
			low[u] = min(low[u], low[edge[v].to]);
		}
		else if (in_s[edge[v].to])
			low[u] = min(low[u], dfn[edge[v].to]);
	}
	if (dfn[u] == low[u])
	{
		++totscc;
		int cac;
		while (1)
		{
			cac = stk.top(); stk.pop();
			scc[cac] = totscc;
			in_s[cac] = 0;
			for (int v = ptr[cac]; v; v = edge[v].pre)
				if (scc[edge[v].to] != totscc)
					disw[totscc] = max(disw[totscc], disw[scc[edge[v].to]] + 1);
			if (cac == u) break;
		}
	}
}

int main()
{
	int u, v;
	readx(m); readx(n); readx(C); readx(M);
	varcnt = n + C + 1;
	for (int i = 1; i <= m; i++)
	{
		readx(u); readx(v);
		AddCond(u, v);
	}
	for (int i = 1; i <= C; i++)
		AddCond(i + n + varcnt, i + n + 1);
	for (int i = 1; i <= n; i++)
	{
		readx(Li[i]); readx(Ri[i]);
		AddCond(i + varcnt, Li[i] + n + varcnt); 
		AddCond(i + varcnt, Ri[i] + 1 + n);
	}
	for (int i = 1; i <= M; i++)
	{
		readx(u); readx(v);
		AddCond(u + varcnt, v + varcnt);
	}
	
	for (int i = 1; i <= 2 * varcnt; i++) 
		if (!dfn[i]) Tarjan(i);
	
	for (int i = 1; i <= varcnt; i++)
		if (scc[i] == scc[i + varcnt])
		{
			puts("-1");
			return 0;
		}
	
	for (int i = 1; i <= n; i++)
	{
		if (disw[scc[i]] >= disw[scc[i + varcnt]])
			sol[i] = 0;
		else // 拓扑逆序小于
			sol[i] = 1;
	}
	
	int ansL = -2e9;
	vector<int> ansv;
	for (int i = 1; i <= n; i++)
		if (sol[i]) 
		{
			ansL = max(ansL, Li[i]);
			ansv.push_back(i);
		}
	
	printf("%d %d\n", ansv.size(), ansL);
	for (auto i: ansv)
		printf("%d ", i);
	puts("");
	return 0;
}

/*
Solution:

	先来思考两个问题：
	1) 我不去考虑区间交的限制，先做 2-SAT 行不行？
		答案是不行。这就好像计数问题不能直接把条件分别限制住，
		然后把答案“取个交”一样。这需要容斥原理。
	2) 我如何把区间交非空的限制转化成 2-SAT 的规范式？
		考虑区间交非空 = 一定存在一个点 p 使得 p \in [L, R]
		我们把 1 ~ n 的区间对应为 n + 1 个点（n 条边），则
		根据 2-SAT 的性质，这个链是从左到右 0 -> 1 递增的。
		我们考虑点值从 0 突变为 1 的某条边，以其为 p，则对于所有
		x[i] = T 的 i，L[i] 对应的点值都取 0，R 都取 1
		（L[i] 对应的点是对应点值的边的左侧点，R 是右侧，也就是 R 要 +1，这样处理则没有问题）
		然后跑一个 2-SAT 即可满足条件：x[i] 取 1 时 L[i] 必取 0，R[i] 必取 1
		注意实际上我们是建一个双向的链
*/