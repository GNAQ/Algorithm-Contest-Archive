#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll stu[200010];
ll n, Ai[200010], Bi[200010], p;
bool vis[200010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


void Solve(int ti)
{
	readx(n); readx(p);
	vector<pair<ll, int>> ve;
	for (int i=1;i<=n;i++)
	{
		readx(Ai[i]); readx(Bi[i]);
		stu[i]=vis[i]=0;
		Ai[i]*=100; Bi[i]*=100;
		ve.push_back({Ai[i], i});
		ve.push_back({Bi[i], i});
	}
	
	sort(ve.begin(), ve.end(), 
		[](const pair<ll, int> &a, const pair<ll, int> &b) { return a.first < b.first; });
	
	int ans = 0;
	int mans = 0, cnt = 0;
	int l = 0, r = -1;
	while (r<(int)ve.size() - 1)
	{
		r++;
		if (!stu[ve[r].second])
			ans++;
		
		if (!vis[ve[r].second]) cnt++;
		vis[ve[r].second] = 1;
		
		stu[ve[r].second]++;
		ll lim = ve[r].first / 100 * p;
		while (ve[l].first < lim)
		{
			stu[ve[l].second]--;
			if (!stu[ve[l].second]) 
				ans--;
			l++;
		}
		
		if (cnt == n)
			mans = max(mans, ans);
	}
	
	printf("Case #%d: %d\n", ti, mans);
}

void Clear()
{
	for (int i=1;i<=n;i++)
		stu[i]=vis[i]=0;
}

int main()
{
	int T; readx(T);
	for (int ti=1;ti<=T;ti++)
	{
		Solve(ti);
		Clear();
	}
	
}