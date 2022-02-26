#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Ve
{
	ll x, y;
	Ve(ll _x, ll _y)
		: x(_x), y(_y) {}
	Ve() {}
	Ve operator *(ll q)
		{ return Ve(x*q, y*q); }
	Ve operator +(Ve a)
		{ return Ve(x+a.x, y+a.y); }
	Ve operator -(Ve a)
		{ return Ve(x-a.x, y-a.y); }
};

Ve gcd(Ve a, Ve b)
{
	if (b.y > a.y) swap(a, b);
	if (b.y == 0) return a;
	ll mu = a.y / b.y;
	return gcd(b, Ve(a.x-b.x*mu, a.y%b.y));
}

ll gcd(ll a, ll b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

bool OK(Ve lf, Ve ld, Ve q)
{
	if (q.y!=0)
	{
		if ((lf.y == 0 || q.y%lf.y != 0))
			return false;
		q = q - lf*(q.y/lf.y);
	}
	if (!q.x) return true;
	if (ld.x && (q.x % ld.x == 0))
		return true;
	return false;
}

int main()
{
	int T; scanf("%d", &T);
	for (int ti=1;ti<=T;ti++)
	{
		Ve lf(0, 0), ld(0, 0);
		int q; ll ans = 0;
		
		scanf("%d", &q);
		while (q--)
		{
			ll x, y, w;
			int op;
			scanf("%d%lld%lld", &op, &x, &y);
			if (op == 1)
			{
				if (!y)
					ld.x = gcd(ld.x, x);
				else
				{
					ll d = abs(lf.y * x - lf.x * y);
					d /= gcd(lf.y, y);
					Ve tmp = gcd(Ve(x, y), lf);
					lf = tmp;
					ld.x = gcd(ld.x, d);
					if (ld.x) lf.x = lf.x % ld.x;
				}
			}
			else
			{
				scanf("%lld", &w);
				if (OK(lf, ld, Ve(x, y)))
					ans += w;
			}
		}
		printf("Case #%d: %lld\n", ti, ans);
	}
	return 0;
}

/*
    --- Problem Solution ---
	
	略去特殊情况，
	
	
	
	
	
	
*/