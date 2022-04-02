#include <bits/stdc++.h>
typedef long long ll;
using namespace std;


int main()
{
	ll a1, a2, k1, k2, n, mina = 0, maxa = 0;
	scanf("%lld%lld%lld%lld%lld", &a1, &a2, &k1, &k2, &n);
	
	ll n1 = max(0LL, n - a1 * (k1 - 1) - a2 * (k2 - 1));
	mina += n1;
	
	if (k1 < k2)
	{
		swap(k1, k2); swap(a1, a2);
	}
	if (a2 * k2 >= n)
	{
		maxa = n / k2;
	}
	else
	{
		maxa = a2 + (n - a2*k2) / k1;
	}
	
	printf("%lld %lld\n", mina, maxa);
	return 0;
}