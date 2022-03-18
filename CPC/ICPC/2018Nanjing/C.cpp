#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct ed
{
	int pre, to;
}edge[200010];
int at, ptr[100010];

int n, ans = 0;

int msiz[100010], hr, subsiz, tsiz[100010], siz2[100010];
bool vis[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx, int tx)
{
	edge[++at].pre = ptr[fx];
	edge[at].to = tx;
	ptr[fx] = at;
}

namespace NDiv
{
	void Solve(int u, int fa)
	{
		siz2[u] = 1;
		for (int v = ptr[u]; v; v = edge[v].pre)
			if (edge[v].to != fa)
			{
				Solve(edge[v].to, u);
				siz2[u] += siz2[edge[v].to];
			}
	}
	
	int GetBlack(int u, int fa, int t)
	{
		int ret = 1e8, mxsub = t - siz2[u]; // 上链子树
		for (int v = ptr[u]; v; v = edge[v].pre) 
			if (edge[v].to != fa)
			{
				ret = min(ret, GetBlack(edge[v].to, u, t));
				mxsub = max(mxsub, siz2[edge[v].to]);
			}
		return min(ret, mxsub);
	}
	
	void GetHRt(int u, int fa)
	{
		tsiz[u] = 1; msiz[u] = 0;
		for (int v = ptr[u]; v; v = edge[v].pre)
			if (!vis[edge[v].to] && edge[v].to != fa)
			{
				GetHRt(edge[v].to, u);
				tsiz[u] += tsiz[edge[v].to];
				msiz[u] = max(msiz[u], tsiz[edge[v].to]);
			}
		msiz[u] = max(msiz[u], subsiz - tsiz[u]);
		if (msiz[u] < msiz[hr]) hr = u;
	}
	
	void Div(int u)
	{
		vis[u] = 1; 
		
		int pos = 0, minans = 1e8;
		for (int v = ptr[u]; v; v = edge[v].pre)
		{
			Solve(edge[v].to, u);
			int blksiz = GetBlack(edge[v].to, u, siz2[edge[v].to]);
			if (minans > n - siz2[edge[v].to] + blksiz)
			{
				minans = n - siz2[edge[v].to] + blksiz;
				pos = edge[v].to;
			}
		}
		
		ans = max(ans, minans);
		if (!vis[pos])
		{
			subsiz = tsiz[pos];
			msiz[hr = 0] = 1e9;
			GetHRt(pos, 0);
			Div(hr);
		}
	}
};

int main()
{
	readx(n);
	int u, v;
	for (int i=1;i<n;i++)
	{
		readx(u); readx(v);
		Is(u, v);
		Is(v, u);
	}
	subsiz = n;
	msiz[hr = 0] = 1e9;
	NDiv::GetHRt(1, 0);
	NDiv::Div(hr);
	printf("%d\n", ans);
}

/*

Solution

Step. 1
如果已经确定第一个粉色点和第一个棕色点的位置，下一个粉色点会在哪里？
以棕色点为根，去掉第一个粉色点及其子树，然后在棕色点的儿子中选择一个子树大小最大的作为粉色点。

Step. 2
如果已经确定了第一个粉色点的位置，那么第一个棕色点会在哪里？
第一个粉色点会将树分成若干个连通块，然后在所有连通块的重心中选择儿子的子树大小最大值最小的那个作为棕色点。

Step. 3
第一个粉色点会在哪里？
假如我们任取一个点作为粉色点，并计算出了此时棕色点的位置，那么粉色点往非棕色点方向移动肯定不优。
那么考虑点分治，对每层分治重心求出答案后，向棕色点所在子树递归即可。

*/