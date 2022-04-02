#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
struct node
{
	ll m, p;
	int sel;
};
node per[100010];

bool cmp1(const node &a, const node &b)
{
	return a.p < b.p;
}
bool cmp2(const node &a, const node &b)
{
	return a.m < b.m;
}

bool check(int val)
{
	if (val * 2 > n)
		return false;
	ll sump = 0, summ = 0;
	sort(per + 1, per + n + 1, cmp1);
	
	return false;
}

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld", &per[i].m);
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%lld", &per[i].p);
	}
	
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
		{
			R = mid - 1;
		}
	}
	printf("%d\n", ans);
	
}