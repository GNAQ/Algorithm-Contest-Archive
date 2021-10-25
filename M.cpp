#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const double eps = 1e-10;

inline int sgn(ll x)
{
	if (x < 0) return -1;
	if (x > 0) return 1;
	return 0;
}

struct Point
{
	int x, y;
	Point() {}
	Point(int _x, int _y)
		: x(_x), y(_y) {}
	
	bool operator == (const Point b)
		{ return (x == b.x) && (y == b.y); }
	Point operator + (const Point b)
		{ return Point(x + b.x, y + b.y); }
	Point operator - (const Point b)
		{ return Point(x - b.x, y - b.y); }
	ll operator ^ (const Point b)
		{ return 1LL * x * b.y - 1LL * y * b.x; }
};

struct Line
{
	Point s, e;
	Line() {}
	Line(Point _s, Point _e)
		: s(_s), e(_e) {}
	
	// 1 -> Left   2 -> Right   3 -> On
	int relation(Point v)
	{
		int rslt = sgn((e-s)^(v-s));
		if (rslt == 1) return 1;
		if (rslt == -1) return 2;
		return 3;
	}
};

int n, m;
Point conv[1010], li[1010];

struct _Node
{
	int l, r, id;
	_Node() {}
	_Node(int _l, int _r, int _id)
		: l(_l), r(_r), id(_id) {}
		
	bool operator < (const _Node &b) const
	{
		if (l == b.l)
			return r > b.r;
		return l < b.l;
	}
}v[1010], zr[1010];
int vans[1010], rec[1010];

void Solve()
{
	scanf("%d%d", &n, &m);
	for (int i=1;i<=n;i++)
		scanf("%d%d", &conv[i].x, &conv[i].y);
	conv[n+1] = conv[1];
	conv[0] = conv[n];
	for (int i=1;i<=m;i++)
		scanf("%d%d", &li[i].x, &li[i].y);
	
	// Convex Hull Cuts
	// T: 右切线; B: 左切线
	for (int i=1;i<=m;i++)
	{
		int T = -1, B = -1;
		for (int j=1;j<=n;j++)
		{
			Line e1(conv[j-1], conv[j]), e2(conv[j], conv[j+1]);
			if (e1.relation(li[i])==2 && e2.relation(li[i])==1)
				T = j;
			if (e1.relation(li[i])==1 && e2.relation(li[i])==2)
				B = j;
		}
		zr[i].id = i;
		zr[i].l = B; zr[i].r = T;
		if (zr[i].r < zr[i].l) zr[i].r += n;
	}
	sort(zr + 1 , zr + m + 1);
	
	// Greedy Zone Covers
	int ans = 1e9;
	// vector<int> vans;
	for (int i=1;i<=m;i++)
	{
		// vector<_Node> v;
		int cnt = 0, j = i;
		while (1)
		{
			if (zr[j].l < zr[i].l)
				v[cnt] = _Node(zr[j].l + n, zr[j].r + n, zr[j].id);
			else
				v[cnt] = zr[j];
			cnt++;
			j++;
			if (j>m) j = 1;
			if (j == i) break;
		}
		
		int tans = 1, tr = v[0].r, pos = 1;
		bool ok = 1;
		rec[tans] = v[0].id;
		for (;pos<m;pos++)
		{
			if (v[pos].l > tr)
			{
				ok = 0;
				break;
			}
			int rmax = pos;
			while (pos+1<m && v[pos+1].l <= tr)
			{
				pos++;
				if (v[pos].r >= v[rmax].r)
					rmax = pos;
			}
			tr = v[rmax].r;
			tans++;
			rec[tans] = v[rmax].id;
			if (tr >= n + v[0].l)
				break;
		}
		if (tr < n + v[0].l)
			ok = 0;
		if (ok && tans < ans)
		{
			ans = tans;
			for (int t=1;t<=ans;t++)
				vans[t]=rec[t];
		}
	}
	
	if (ans == 1e9)
	{
		puts("-1");
		return;
	}
	printf("%d\n", ans);
	for (int i=1;i<=ans;i++)
		printf("%d%c", vans[i], " \n"[i==ans]);
}

int main()
{
	int T; scanf("%d", &T);
	for (int t=1;t<=T;t++)
		Solve();
}