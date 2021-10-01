#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
int xa, xb, ya, yb;
int xi[100010], yi[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool IsIn(int x, int y)
{
	if (x>=1 && y>=1 && x<=n && y<=n)
		return true;
	return false;
}

void Solve()
{
	set<pair<int, int>> stx;
	
	for (int i=1;i<=n;i++)
	{
		int x = xa + xi[i], y = ya + yi[i];
		if (IsIn(x, y))
		{
			stx.insert(make_pair(x, y));
		}
	}
	
	for (int i=0;i<=n;i++)
	{
		int x = xb - xi[i], y = yb - yi[i];
		if (IsIn(x, y))
		{
			if (stx.count(make_pair(x, y))!=0)
			{
				puts("Alice wins");
				return;
			}
		}
	}
	
	stx.clear();
	for (int i=1;i<=n;i++)
	{
		int x = xb + xi[i], y = yb + yi[i];
		if (IsIn(x, y))
		{
			stx.insert(make_pair(x, y));
		}
	}
	
	int x, y;
	mt19937 mtgen(time(NULL));
	uniform_int_distribution<int> distrib(1, n);
	while (1)
	{
		x = distrib(mtgen), y = distrib(mtgen);
		
		if (x==xb && y==yb) continue;
		// if (x==xa && y==ya) continue;
		
		bool ok = 1;
		for (int i=0;i<=n;i++)
		{
			int xx = x - xi[i], yy = y - yi[i];
			if (IsIn(xx, yy) && stx.count(make_pair(xx, yy))!=0)
				ok = 0;
		}
		if (ok)
		{
			cout << "tie " << x << "  " << y << endl;
			return;
		}
	}
}

bool vis[10][10];

int main()
{
	readx(n);
	readx(xa); readx(ya); readx(xb); readx(yb);
	for (int i=1;i<=n;i++)
	{
		readx(xi[i]);
		readx(yi[i]);
	}
	if (xa==xb && ya==yb)
	{
		puts("Alice wins");
		return 0;
	}
	
	if (n <= 3)
	{
		set<pair<int, int>> stx;
		for (int i=1;i<=n;i++)
			for (int j=0;j<=n;j++)
				if (IsIn(xa+xi[i]+xi[j], ya+yi[i]+yi[j]) && IsIn(xa+xi[i], ya+yi[i]))
					stx.insert(make_pair(xa+xi[i]+xi[j], ya+yi[i]+yi[j]));
		
		if (stx.count(make_pair(xb, yb))!=0)
		{
			puts("Alice wins");
			return 0;
		}
		
		stx.clear();
		for (int i=1;i<=n;i++)
			for (int j=0;j<=n;j++)
				if (IsIn(xb+xi[i]+xi[j], yb+yi[i]+yi[j]) && IsIn(xb+xi[i], yb+yi[i]))
					vis[xb+xi[i]+xi[j]][yb+yi[i]+yi[j]]=1;
		vis[xb][yb]=1;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (!vis[i][j])
				{
					cout << "tie " << i << " " << j << endl;
					return 0;
				}
		puts("Bob wins");
	}
	else
	{
		Solve();
	}
}