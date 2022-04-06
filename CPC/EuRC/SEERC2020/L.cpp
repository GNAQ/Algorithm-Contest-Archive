#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
struct node
{
	ll m, p, mp;
	int id;
};
node Ai[100010];

struct nodecmp1
{
	bool operator ()(const node &a, const node &b)
	{ 
		if (a.p == b.p) return a.id <= b.id;
		return a.p < b.p;
	}
};
struct nodecmp2
{
	bool operator ()(const node &a, const node &b)
	{
		if (a.mp == b.mp && a.m == b.m)
			return a.id <= b.id;
		if (a.mp == b.mp)
			return a.m > b.m;
		return a.mp > b.mp;
	}
};

bool check(int val)
{
	if (val * 2 > n)
		return false;
	
	set<node, nodecmp2> smp;
	set<node, nodecmp1> sp;
	ll sump = 0, summ = 0;
	
	for (int i=1;i<=val;i++)
	{
		smp.insert(Ai[i]);
		summ += Ai[i].m;
	}
	for (int i=val+1;i<=n;i++)
		sp.insert(Ai[i]);
	
	auto v = smp.end(); v--;
	auto w = sp.begin();
	for (int i=1;i<=val;i++)
	{
		sump += w->p;
		w++;
	}
	w--;
	
	for (int i=val+1;i<=2*val;i++)
	{
		if (summ >= sump) 
			return true;
		if (nodecmp1()(Ai[i], *w) == false)
		{
			sump -= w->p;
			w--;
		}
		else
		{
			sump -= Ai[i].p;
			sp.erase(Ai[i]);
		}
		if (nodecmp2()(Ai[i], *v) == true) // Ai is on large m+p
		{
			smp.insert(Ai[i]);
			summ += Ai[i].m - v->m;
			sump += v->p;
			v--;
		}
		else
		{
			smp.insert(Ai[i]);
			sump += Ai[i].p;
		}
	}
	return summ >= sump;
}

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=n;i++)
		scanf("%lld", &Ai[i].m);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld", &Ai[i].p);
		Ai[i].mp = Ai[i].m + Ai[i].p;
	}
	sort(Ai + 1, Ai + n + 1, [](const node &a ,const node &b) { return a.m > b.m; });
	for (int i=1;i<=n;i++)
		Ai[i].id = i;
	
	int L = 1, R = n / 2, mid;
	int ans = 0;
	while (L <= R)
	{
		mid = (L + R) / 2;
		if (check(mid))
		{
			L = mid + 1;
			ans = max(ans, mid);
		}
		else
			R = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}