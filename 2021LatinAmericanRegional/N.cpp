#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	scanf("%d\n", &n);
	int a, b, c;
	scanf("$%d.%1d%1d", &a, &b, &c);
	int sum = 0;
	sum += a * 100 + b * 10 + c;
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("$%d.%1d%1d", &a, &b, &c);
		sum += a * 100 + b * 10 + c;
		if (sum % 100)
			ans++;
	}
	cout << ans << '\n';
}
