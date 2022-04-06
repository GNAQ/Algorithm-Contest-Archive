#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int mod = 1e9+7;

int f[3010][3010], f2[3010][3010];
int h[3010], n;
int r[3010], l[3010];

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=n;i++)
		scanf("%d", &h[i]);
	
	for (int i=1;i<=n;i++)
	{
		l[i] = r[i] = i;
		while (l[i] && h[l[i]-1] > h[i]) 
			l[i]--;
		while (r[i] < n && h[r[i]+1] > h[i])
			r[i]++;
	}
	
	f[0][0] = f2[0][0] = 1;
	for (int i=1;i<=n;i++) 
		f2[0][i] = 1;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) if (l[j] <= i && i <= r[j])
			f[i][j] = f2[i-1][j];
		for (int j=1;j<=n;j++)
			f2[i][j] = (f2[i][j-1]+f[i][j])%mod;
	}
	
	cout << f2[n][n];
}

/*

Solution

	复杂的题目转化为简单，来自于一个极其重要的观察：
	最后结果的形态，不同数值的段之间的先后顺序。
	一定是原序列中，最终结果对应的子序列的先后顺序。数字的先后顺序不会发生改变。
	
	那么我们就可以设 dp[i][j] 表示在 final[i] 处填充 h[j]
	则转移就会变得极其简单：dp[i][j] = sum(dp[i-1][0...j])
	用前缀和维护即可。
	但是我们还需要注意，h[j] 扩展到位置 i 不一定合法。
	所以我们与处理一下每个 h[j] 的扩展范围即可。

*/