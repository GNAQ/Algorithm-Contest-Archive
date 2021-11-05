#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int a[100010], n, b[100010];
pair<int, int> ids[100010];

string sst[2] = {"Bob", "Alice"};
ll ans;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool cmp(pair<int, int> &a, pair<int, int> &b)
{
	return a.first < b.first;
}

void Solve()
{
	readx(n);
	for (int i=0;i<=n+2;i++) b[i]=-1;
	for (int i=1;i<=n;i++)
	{
		readx(a[i]);
		ids[i].first = a[i];
		ids[i].second = i;
	}
	sort(ids+1, ids+n+1, cmp);
	
	for (int i=1;i<=n;i++)
	{
		int maxv = -1;
		if (b[ids[i].second - 1] != -1)
			maxv = max(maxv, b[ids[i].second - 1]);
		if (b[ids[i].second + 1] != -1)
			maxv = max(maxv, b[ids[i].second + 1]);
		b[ids[i].second] = maxv + 1;
	}
	
	for (int i=1;i<=n;i++) ans += a[i] - b[i];
	
	cout << sst[ans%2] << endl;
}

void Clear()
{
	ans = 0;
}


int main()
{
	int T; readx(T);
	for (int t=1;t<=T;t++)
	{
		printf("Case %d: ", t);
		Solve();
		Clear();
	}
	return 0;
}