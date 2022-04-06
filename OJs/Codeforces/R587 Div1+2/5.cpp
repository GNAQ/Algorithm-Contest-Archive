#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

pair<int, int> valC[2010];
int n, m, ai[14][2020], m2;
int q[14][14];
int dp[14][5000];
int cw[14][5000];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int rnd(int val)
{
	if (val & (1 << (n-1)))
		val = (((val ^ (1<<(n-1))) << 1) | 1);
	else
		val = val << 1;
	return val;
}

void Solve()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			readx(ai[i][j]);
	
	m2 = (m > n ? n : m);
	for (int j=1;j<=m;j++)
	{
		valC[j].first = ai[1][j];
		valC[j].second = j;
		for (int i=1;i<=n;i++)
			valC[j].first = max(ai[i][j], valC[j].first);
	}
	sort(valC + 1, valC + m + 1, 
		[](const pair<int, int> &a, const pair<int, int> &b)
		{ return a.first > b.first; });
	for (int i=1;i<=m2;i++) // only first m2 <= n columns
		for (int j=1;j<=n;j++)
			q[j][i] = ai[j][valC[i].second];

	// init cw & dp
	for (int i=0;i<=m2;i++)
		for (int j=0;j<(1<<n);j++)
		{
			dp[i][j] = -1e12;
			cw[i][j] = 0;
			int st = j;
			for (int rn = 0; rn < n; rn++)
			{
				int tmp = 0;
				for (int k=1;k<=n;k++)
					if (st & (1<<(k-1))) 
						tmp += q[k][i];
				cw[i][j] = max(cw[i][j], tmp);
				st = rnd(st);
			}
		}
		
	dp[0][0]=0;
	for (int j=1;j<=m2;j++)
	{
		for (int st = 0; st < (1 << n); st++)
		{
			dp[j][st] = dp[j-1][st];
			for (int base = st; base > 0; base = (base - 1) & st)
				dp[j][st] = max(dp[j][st], dp[j-1][st^base]+cw[j][base]);
		}
	}
	int ans = 0;
	for (int i=1;i<=m2;i++)
		ans = max(ans, dp[i][(1<<n)-1]);
	printf("%d\n", ans);
}


int main()
{
	int T; readx(T);
	for (int t=1;t<=T;t++)
		Solve();
}