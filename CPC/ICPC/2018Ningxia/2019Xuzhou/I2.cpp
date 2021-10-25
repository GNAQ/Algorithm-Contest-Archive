#include <bits/stdc++.h>
typedef long long ll;
using namespace std;


set<vector<int>> sx;

int n, k;
pair<int, int> fx[20];
ll qmod;
ll ans;

void DFS(int lv, vector<int> &now)
{
	if (lv < 1)
	{
		ans++;
		return;
	}
	
	if (now[fx[lv].first] < now[fx[lv].second])
	{
		DFS(lv-1, now);
		swap(now[fx[lv].first], now[fx[lv].second]);
		DFS(lv-1, now);
		swap(now[fx[lv].first], now[fx[lv].second]);
	}
}

void Solve()
{
	cin>>n>>k>>qmod;
	ans = 0;
	sx.clear();
	
	for (int i=1;i<=k;i++)
		cin>>fx[i].first>>fx[i].second;
	
	{
		vector<int> bas, now;
		bas.resize(n+1, 0);
		for (int i=1;i<=n;i++)
			bas[i] = i;
		
		for (int i=1;i<=n;i++)
		{
			now = bas;
			for (int j=i-1;j>=1;j--)
			{
				swap(now[j], now[j+1]);
				sx.insert(now);
			}
			now = bas;
			for (int j=i+1;j<=n;j++)
			{
				swap(now[j], now[j-1]);
				sx.insert(now);
			}
		}
		sx.insert(bas);
	}
	
	for (auto v: sx)
	{
		vector<int> now = v;
		DFS(k, now);
	}
	
	cout << ans % qmod << endl;
}

int main()
{
	int T; cin>>T;
	while (T--)
		Solve();
}