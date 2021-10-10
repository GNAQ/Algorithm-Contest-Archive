#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, maxh;
struct _Node
{
	int x, y, h;
}nd[100010];
int ansx, ansy;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool check(int v)
{
	int lx, rx, ly, ry;
	lx = nd[1].x - (v - nd[1].h);
	rx = nd[1].x + (v - nd[1].h);
	ly = nd[1].y - (v - nd[1].h);
	ry = nd[1].y + (v - nd[1].h);
	for (int i=2;i<=n;i++)
	{
		lx = max(lx, nd[i].x - (v - nd[i].h));
		rx = min(rx, nd[i].x + (v - nd[i].h));
		ly = max(ly, nd[i].y - (v - nd[i].h));
		ry = min(ry, nd[i].y + (v - nd[i].h));
	}
	if (lx<=rx && ly<=ry)
	{
		ansx = lx;
		ansy = ly;
		return true;
	}
	return false;
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(nd[i].x); readx(nd[i].y);
		readx(nd[i].h);
		maxh=max(maxh, nd[i].h);
	}
	
	int L = maxh, R = 320000000, ans = -1;
	while (L<=R)
	{
		int mid = (L+R)/2;
		
		if (check(mid))
		{
			ans = mid;
			R = mid-1;
		}
		else
		{
			L = mid+1;
		}
	}
	
	printf("%d %d %d\n", ansx, ansy, ans);
	return 0;
}