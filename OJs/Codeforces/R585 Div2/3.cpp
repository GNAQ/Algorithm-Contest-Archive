#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n; 
char si[200010], ti[200010];
int cnta, cntb;

int main()
{
	scanf("%d", &n);
	scanf("%s%s", si+1, ti+1);
	
	for (int i=1;i<=n;i++)
	{
		if (si[i] == 'a')
			cnta++;
		else 
			cntb++;
		if (ti[i] == 'a')
			cnta++;
		else
			cntb++;
	}
	if ((cnta % 2) || (cntb % 2))
	{
		printf("-1\n");
		return 0;
	}
	
	vector<int> ab, ba;
	for (int i=1;i<=n;i++) if (si[i] != ti[i])
	{
		if (si[i] == 'a')
			ab.push_back(i);
		else
			ba.push_back(i);
	}
	
	ll ans = 0;
	vector<pair<int, int>> vans;
	while (ab.size() >= 2)
	{
		ans++;
		vans.push_back({ab[ab.size() - 1], ab[ab.size() - 2]});
		ab.pop_back(); ab.pop_back();
	}
	while (ba.size() >= 2)
	{
		ans++;
		vans.push_back({ba[ba.size() - 1], ba[ba.size() - 2]});
		ba.pop_back(); ba.pop_back();
	}
	if (ba.size() + ab.size() == 1)
	{
		puts("-1");
		return 0;
	}
	if (ba.size() + ab.size())
	{
		ans+=2;
		vans.push_back({ab[0], ab[0]});
		vans.push_back({ab[0], ba[0]});
	}
	
	printf("%lld\n", ans);
	for (auto i: vans)
		printf("%d %d\n", i.first, i.second);
	
	return 0;
}