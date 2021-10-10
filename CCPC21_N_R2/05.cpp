#include <bits/stdc++.h>
typedef long long ll;
typedef std::vector<ll>::iterator vit;
using namespace std;

map<ll, int> mp;
map<ll, int> vid;
vector<ll> vc[100010];
int cnt;

int n, m;
ll ai[100010], pf[100010];

void Solve()
{
	scanf("%d%d", &n, &m);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld", &ai[i]);
		pf[i]=pf[i-1] + ai[i];
		
		if (vid.find(pf[i])==vid.end())
			vid[pf[i]]=i;
	}
	
	// init
	ll sum = pf[n];
	
	if (sum == 0)
	{
		for (int i=1;i<=m;i++)
		{
			ll k; scanf("%lld", &k);
			if (!k)
			{
				puts("0");
				continue;
			}
			if (vid.find(k) == vid.end())
				puts("-1");
			else
				printf("%d\n", vid[k]);
		}
		return;
	}
	
	for (int i=1;i<=n;i++)
	{
		ll tmp = pf[i] % sum;
		if (tmp<0) tmp+=abs(sum);
		if (mp.find(tmp) == mp.end())
			mp[tmp] = ++cnt;
		
		vc[mp[tmp]].push_back(pf[i]);
	}
	for (int i=1;i<=cnt;i++) 
		sort(vc[i].begin(), vc[i].end());
	
	// solve
	for (int i=1;i<=m;i++)
	{
		ll k;
		scanf("%lld", &k);
		
		if (!k)
		{
			puts("0");
			continue;
		}
		
		ll tmp = k % sum;
		if (tmp<0) tmp+=abs(sum);
		if (mp.find(tmp) == mp.end())
		{
			puts("-1");
			continue;
		}
		
		if (sum>0)
		{
			int u = mp[tmp];
			vit it = upper_bound(vc[u].begin(), vc[u].end(), k);
			if (it != vc[u].begin())
			{
				it--;
				ll ans = (k - (*it)) / sum;
				if (ans>=0)
					printf("%lld\n", ans * n + vid[*it]);
				else
					puts("-1");
			}
			else
			{
				puts("-1");
			}
		}
		if (sum<0)
		{
			int u = mp[tmp];
			vit it = lower_bound(vc[u].begin(), vc[u].end(), k);
			if (it != vc[u].end())
			{
				ll ans = (k - (*it)) / sum;
				if (ans>=0)
					printf("%lld\n", ans * n + vid[*it]);
				else
					puts("-1");
			}
			else
			{
				puts("-1");
			}
		}
	}
	
}

void Clear()
{
	mp.clear();
	vid.clear();
	for (int i=1;i<=cnt;i++)
		vc[i].clear();
	cnt = 0;
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		Solve();
		Clear();
	}
}