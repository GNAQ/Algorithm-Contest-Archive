#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const double eps = 1e-10;
const double PI = 3.14159265358979323846;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int sgn(double x)
{
	if (x < eps) return 0;
	if (x < 0) return -1;
	return 1;
}

double sqr(double x)
{
	return x*x;
}

struct Point
{
	int x, y;
	Point() {}
	Point(int _x, int _y)
		: x(_x), y(_y) {}
	
	bool operator == (Point b)
	{
		return (x == b.x) && (y == b.y);
	}
	
	bool operator < (Point b)
	{
		return (x < b.x) && (y < b.y);
	}
	
	Point operator + (Point b)
	{
		return Point(x+b.x, y+b.y);
	}
	
	Point operator - (Point b)
	{
		return Point(x-b.x, y-b.y);
	}
	
	double operator * (Point b)
	{
		return x*b.x + y*b.y;
	}
	
	double operator ^ (Point b)
	{
		return x*b.y - y*b.x;
	}
	
	void output()
	{
		printf("%.2lf %.2lf\n", x, y);
	}
};

struct Line
{
	Point s, e;
	Line() {}
	Line(Point _s, Point _e)
		: s(_s), e(_e) {}
	
	// 1 -> Left
	// 2 -> Right
	// 3 -> On
	int relation(Point v)
	{
		int rslt = sgn((e-s)^(v-s));
		if (rslt == 1) return 1;
		if (rslt == -1) return 2;
		return 3;
	}
	
};


void Solve()
{
	
}

void Clear()
{
	
}

int main()
{
	int T; readx(T);
	for (int t=1;t<=T;t++)
	{
		Solve();
		Clear();
	}
}