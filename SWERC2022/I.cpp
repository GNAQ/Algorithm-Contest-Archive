#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m;
int pi[200010], lx[200010], rx[200010];
int loc[200010];
ll psum[200010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) 
		readx(pi[i]);
	for (int i=1;i<=m;i++)
		readx(loc[i]);
		
	sort(loc+1, loc+m+1);
	for (int i=1;i<=n;i++)
		psum[i] = psum[i - 1] + pi[i];
	
	loc[0] = loc[m + 1] = -1;  // NOTE
	int cur = 0;
	for (int i=1;i<=n;i++)
	{
		int pos = 100 * (i - 1);
		while (cur < m && loc[cur + 1] <= pos)
			cur++;
		lx[i] = loc[cur];
	}
	cur = m + 1;
	for (int i=n;i>=1;i--)
	{
		int pos = 100 * (i - 1);
		while (cur > 1 && loc[cur - 1] >= pos)
			cur--;
		rx[i] = loc[cur];
	}
	
	ll ans = 0;
	for (int i=1;i<=n;i++) 
	{
		if (lx[i] != 100 * (i - 1)) // if it can select as leftmost
		{
			ll ipos = 100 * (i - 1);
			if (rx[i] == -1)
			{
				ans = max(ans, psum[n] - psum[i - 1]);
				continue;
			}
			if (lx[i] == -1)
			{
				ans = max(ans, psum[i]);
				continue;
			}
			ll pos = min((ll)rx[i], (ipos - lx[i]) + ipos);
			ll jpos = (pos + rx[i]) / 2;
			bool flag = (pos + rx[i]) % 2;
			ll j;
			if (!flag)
				j = (jpos - 1) / 100    + 1;
			else
				j = jpos / 100    + 1;
			
			j = min(j, (ll)n);
			ans = max(ans, psum[j] - psum[i - 1]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}