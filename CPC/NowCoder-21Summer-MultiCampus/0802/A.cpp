#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

ll n, m;
pair<ll, ll> ti[100010];
vector< pair<ll, ll> > ans[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool cmp(pair<ll, ll> a, pair<ll, ll> b)
{
	return a.first > b.first;
}

bool cmp2(pair<ll, ll> a, pair<ll, ll> b)
{
	return a.second < b.second;
}

struct _Node
{
	ll first, second;
	bool operator < (_Node b) const
	{ 
		return this->first > b.first;
	}
	_Node(ll f, ll s)
	{
		first = f;
		second = s;
	}
};

int main()
{
	readx(n); readx(m); ll sum = 0, tans = 0;
	for (int i=1;i<=n;i++)
	{
		readx(ti[i].first);
		ti[i].second = i;
		sum += ti[i].first;
		tans = max(tans, ti[i].second);
	}
	
	tans = max(tans, sum/m + (sum%m>0));
	
	ll cnt = 0, id = 1;
	for (int i=1;i<=n;i++)
	{
		if (cnt + ti[i].first <= tans)
		{
			ans[i].push_back(make_pair(id, cnt));
			cnt += ti[i].first;
		}
		else
		{
			ans[i].push_back(make_pair(id, cnt));
			ans[i].push_back(make_pair(id+1, 0));
			cnt = cnt + ti[i].first - tans;
			id++;
		}
		if (cnt==tans) 
		{
			cnt=0; id++;
		}
	}
	
	for (int i=1;i<=n;i++)
	{
		printf("%lld ", ans[i].size());
		if (ans[i].size()==2) 
			printf("%lld %lld %lld %lld %lld %lld\n", ans[i][1].first, ans[i][1].second, ti[i].first - (tans - ans[i][0].second),
				ans[i][0].first, ans[i][0].second, tans);
		else
			printf("%lld %lld %lld\n", ans[i][0].first, ans[i][0].second, ans[i][0].second + ti[i].first);
	}
}