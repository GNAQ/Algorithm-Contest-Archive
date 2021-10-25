#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

ll H, M, A;

ll gcd(ll a, ll b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

// Solve L % m <= ax % m <= R % m
ll Solve1(int L, int R, int a, int m)
{
	if (gcd(a, m) == 1)
		return R - L + 1;
	else
	{
		ll g = gcd(a, m);
		return Solve1(L / g + (L%g!=0), R / g, a / g, m / g) * g;
	}
}

// Solve L % m < ax % m <= R % m
ll Solve2(int L, int R, int a, int m)
{
	if (gcd(a, m) == 1)
		return R - L;
	else
	{
		ll g = gcd(a, m);
		return Solve2(L / g, R / g, a / g, m / g) * g;
	}
}

// How to find the minimum [x]?
// L <= ax + my <= R
// if (y eq 0) {SolveIt}
// else Solve -> ax - R <= my <= ax - L
// It is an recursive problem
// Solve (-R) % a <= (m%a)y <= (-L) % a
// Recursed.
// why minimum? consider exgcd.
// Problem: POJ3530
// ref to: https://www.cnblogs.com/tztqwq/p/14520688.html

int main()
{
	scanf("%lld%lld%lld", &H, &M, &A);
	
	ll ans = 0;
	ans += 2LL * M * (A / M) + M;
	
	ll alpha = Solve1(M-A%M, M-1, (H-1)%M, M);
	ll beta = Solve2(A%M, M-1, (H-1)%M, M);
	ans += alpha - beta;
	
	if (A == H*M/2) 
		ans = H*M;
	printf("%lld\n", ans);
}