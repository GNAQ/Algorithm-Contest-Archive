#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n;
char ss[200010];

int main()
{
	scanf("%lld%s", &n, ss + 1);
	
	n /= 2;
	ll v1 = 0, k1 = 0, v2 = 0, k2 = 0;
	for (int i=1;i<=n;i++)
	{
		if (ss[i] == '?') k1++;
		else v1 += ss[i] - '0';
	}
	for (int i=n+1;i<=2*n;i++)
	{
		if (ss[i] == '?') k2++;
		else v2 += ss[i] - '0';
	}
	if (v1 > v2)
	{
		swap(v1, v2);
		swap(k1, k2);
	}
	if (v1 == v2)
	{
		if (k1 == k2)
			puts("Bicarp");
		else
			puts("Monocarp");
	}
	else // v1 < v2
	{
		if (k1 <= k2)
			puts("Monocarp");
		else // k1 > k2
		{
			if (v2 - v1 == 9 * (k1 - k2) / 2) // 这是个混合策略 Nim 的 SG，很自然
				puts("Bicarp");
			else
				puts("Monocarp");
		}
	}
	return 0;
}