#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct TNd
{
	int maxdep, curdep;
	int dep_Rneed;
	bool chosen;
	int fa, lch, rch;
}t[1000010];

int n;
ll val;
ll f[1000010];

int DFS_Init(int u)
{
	t[u].maxdep = 1;
	if (t[u].lch) t[u].maxdep = max(t[u].maxdep, DFS_Init(t[u].lch) + 1);
	if (t[u].rch) t[u].maxdep = max(t[u].maxdep, DFS_Init(t[u].rch) + 1);
	return t[u].maxdep;
}

// 有一个深度 tag 和一个深度状态
// 每次深度 tag 更新状态的时机是：
// tag 在右子树上左偏下推（下面的 Build_depth 函数）
// 深度状态在每次选择结点的时候，对【所有访问到的结点更新当前深度】
// 任何关系在本题中都是中序 DFS 序上单调向右的，所以无序关心左儿子, 对于右儿子，上文已经保证。

// 对左子树推上去的深度 tag，在子树根节点做其右子树的左偏下推
// 在中序 DFS 序上，这些 tag 单调向右推，所以在【按DFS序枚举的过程中】，这些tag之后也会被扫到
void Build_Depth(int u, int depneed)
{
	if (depneed <= 0) return;
	if (t[t[u].lch].maxdep >= depneed - 1)
	{
		Build_Depth(t[u].lch, depneed - 1);
		if (depneed > 2)
			t[u].dep_Rneed = depneed - 2;
	}
	else // we use right subtree to balance the depth
	{
		t[u].dep_Rneed = depneed - 1;
		if (depneed > 2)
			Build_Depth(t[u].lch, depneed - 2);
	}
	t[u].curdep = depneed;
	t[u].chosen = 1;
}

// 往上走，检查如果推上去对应的深度 tag，可用节点数还够不够
bool Check_poss(int u, int ch, int dep, ll &avail)
{
	// 如果我们从左儿子来（往右上走），我们要把深度 tag 推上去
	// 因为此时我们要求未被【主动】选中的右子树要有对应的深度大小
	// 同时对于已经有若干 tag 的祖先，我们要更新 tag
	//
	// 如果我们从右儿子来（往左上走），我们要检查已经存在的深度 tag 够不够本次使用
	// 显然我们不能要求左子树选更多，因为贪心选择的性质，在最优答案下，该被选的都被选完了
	if (u<=0) return true;
	
	ll tmp = avail;
	if (ch < u) // from left child
	{
		if (!t[u].chosen)
		{
			if (!tmp) return false;
			tmp--;
		}
		int tmp_Rdep = t[u].dep_Rneed;
		
		if (tmp_Rdep < dep - 2)
		{
			tmp -= (f[dep-2] - f[tmp_Rdep]);
			if (tmp < 0) return false;
			tmp_Rdep = dep-2;
		}
		if (Check_poss(t[u].fa, u, dep+1, tmp))
		{
			avail = tmp;
			t[u].chosen = true;
			t[u].dep_Rneed = tmp_Rdep;
			t[u].curdep = max(t[u].curdep, dep);
			return true;
		}
		return false;
	}
	if (ch > u) // from right child
	{
		// an valid construction must assure an existing left child use this node
		// greedily selection strategy assures that whole tree is left-sided
		if ((!t[u].chosen) || t[t[u].lch].curdep < dep - 2)
			return false;
		
		if (Check_poss(t[u].fa, u, dep+1, tmp))
		{
			avail = tmp;
			t[u].chosen = true;
			t[u].curdep = max(t[u].curdep, dep); // 这句其实没有意义？
			return true;
		}
		return false;
	}
	return false;
}

void go(int u, ll &avail)
{
	if (t[u].chosen) // 要推 tag 了
	{
		if (t[u].dep_Rneed)
		{
			Build_Depth(t[u].rch, t[u].dep_Rneed);
			t[u].dep_Rneed = 0;
		}
		return;
	}
	
	if (!avail) return;
	
	ll tmp = avail - 1;
	if (Check_poss(t[u].fa, u, 2, tmp)) // OK to sel this node
	{
		t[u].chosen = true;
		t[u].curdep = max(t[u].curdep, 1); // 这句话也没有任何用啊。
		avail = tmp;
	}
}

int main()
{
	scanf("%d%lld", &n, &val);
	
	f[1] = 1;
	for (int i=2;i<=n;i++)
	{
		f[i] = f[i-1] + f[i-2] + 1;
		if (f[i] > n) break;
	}
	
	int rt = 0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d", &t[i].fa);
		if (t[i].fa == -1)
			rt = i;
		else if (t[i].fa > i)
			t[t[i].fa].lch = i;
		else
			t[t[i].fa].rch = i;
	}
	
	DFS_Init(rt);
	
	for (int i=1;i<=n;i++)
		go(i, val);
	
	for (int i=1;i<=n;i++)
		printf("%d", (int[2]){0, 1}[t[i].chosen]);
	puts("");
	return 0;
}