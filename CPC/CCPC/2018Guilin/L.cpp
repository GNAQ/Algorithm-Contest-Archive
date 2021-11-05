#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const double eps = 1e-12;
const double inf = 1e20;

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
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}

inline double sqr(double x)
{
	return x * x;
}

struct Point
{
	double x, y;
	Point() {}
	Point (double _x, double _y)
		: x(_x), y(_y) {}
	
	void output()
	{
		printf("%.2lf %.2lf\n", x, y);
	}
	
	bool operator == (const Point &b) const
	{
		return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
	}
	
	Point operator + (Point b)
	{
		return Point(x+b.x, y+b.y);
	}
	
	Point operator - (Point b)
	{
		return Point(x-b.x, y-b.y);
	}
	
	double diszero()
	{
		return hypot(x, y);
	}
	
	double operator ^ (Point b)
	{
		return x*b.y - y*b.x;
	}
	
	double operator * (Point b)
	{
		return x*b.x + y*b.y;
	}
	
	double rad(Point a, Point b)
	{
		Point p = *this;
		return fabs(atan2( fabs((a-p)^(b-p)), (a-p)*(b-p) ));
	}
	
	double dist(Point b)
	{
		return sqrt(sqr(x-b.x) + sqr(y-b.y));
	}
};

struct Line
{
	Point s, e;
	Line() {}
	Line(Point _s, Point _e)
		: s(_s), e(_e) {}
	
	bool operator == (Line v)
	{
		return (s == v.s) && (e == v.e);
	}
	
	// 1 -> Left
	// 2 -> Right
	// 3 -> In
	int relation(Point p)
	{
		int c = sgn((p-s)^(e-s));
		if (c<0) return 1;
		if (c>0) return 2;
		return 3;
	}
	
	bool PointOnSeg(Point p)
	{
		return sgn((p-s)^(e-s)) == 0 && sgn((p-s)*(p-e)) <= 0;
	}
	
	int SegCrossSeg(Line v)
	{
		int d1 = sgn((e-s)^(v.s-s));
		int d2 = sgn((e-s)^(v.e-s));
		int d3 = sgn((v.e-v.s)^(s-v.s));
		int d4 = sgn((v.e-v.s)^(e-v.s));
		if ( (d1^d2)==-2 && (d3^d4)==-2 ) return 2;
		return (d1==0 && sgn((v.s-s)*(v.s-e)) <= 0) || 
			(d2==0 && sgn((v.e-s)*(v.e-e)) <= 0) || 
			(d3==0 && sgn((s-v.s)*(s-v.e)) <= 0) || 
			(d4==0 && sgn((e-v.s)*(e-v.e)) <= 0);
	}
	
	Point CrossPoint(Line v)
	{
		double a1 = (v.e-v.s)^(s-v.s);
		double a2 = (v.e-v.s)^(e-v.s);
		return Point((s.x*a2-e.x*a1)/(a2-a1), (s.y*a2-e.y*a1)/(a2-a1));
	}
	
	bool parallel(Line v)
	{
		return sgn((e-s)^(v.e-v.s)) == 0;
	}
};

void Solve()
{
	Line W, B;
	
	scanf("%lf%lf%lf%lf", &W.s.x, &W.s.y, &W.e.x, &W.e.y);
	scanf("%lf%lf%lf%lf", &B.s.x, &B.s.y, &B.e.x, &B.e.y);
	
	if (W.s.x == W.e.x)
	{
		if (W.s.y > W.e.y)
			swap(W.s, W.e);
	}
	else if (W.s.x > W.e.x)
		swap(W.s, W.e);
	if (B.s.x == B.e.x)
	{
		if (B.s.y > B.e.y)
			swap(B.s, B.e);
	}
	else if (B.s.x > B.e.x)
		swap(B.s, B.e);
	
	// spj!!
	if (W.parallel(B) && W.relation(B.e) == 3)
	{
		printf("0.000\n");
		return;
	}
	
	int cas1 = W.SegCrossSeg(B);
	
	// cerr << "!!Cas = " << cas1 << endl;
	
	if (cas1==2)
	{
		printf("0.000\n");
		return;
	}
	if (cas1==1)
	{
		if (W.relation(B.s) == 3 || W.relation(B.e) == 3)
			printf("inf\n");
		else
			printf("0.000\n");
		return;
	}
	
	int LineSide = W.relation(B.s);
	Point p1, p2, p3, p4;
	Line Y1, Y2, O1, O2;
	int s1, s2, s3, s4;
	
	Y1.s = W.s; Y1.e = B.s;
	Y2.s = W.s; Y2.e = B.e;
	O1.s = W.e; O1.e = B.s;
	O2.s = W.e; O2.e = B.e;
	
	if (Y1.parallel(O1)) 
		s1 = -1;
	else
	{
		p1 = Y1.CrossPoint(O1);
		s1 = W.relation(p1); 
	}
	
	if (Y1.parallel(O2))
		s2 = -1;
	else
	{
		p2 = Y1.CrossPoint(O2);
		s2 = W.relation(p2);
	}
	
	if (Y2.parallel(O1))
		s3 = -1;
	else
	{
		p3 = Y2.CrossPoint(O1);
		s3 = W.relation(p3);
	}
	
	if (Y2.parallel(O2))
		s4 = -1;
	else
	{
		p4 = Y2.CrossPoint(O2);
		s4 = W.relation(p4);
	}
	
	// p1.output(); p2.output(); p3.output(); p4.output();
	// cerr << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
	
	bool flag = 0; Point apnt;
	if (s1 != -1 && s1 != LineSide)
	{
		flag = 1;
		apnt = p1;
	}
	if (s2 != -1 && s2 != LineSide)
	{
		flag = 1;
		apnt = p2;
	}
	if (s3 != -1 && s3 != LineSide)
	{
		flag = 1;
		apnt = p3;
	}
	if (s4 != -1 && s4 != LineSide)
	{
		flag = 1;
		apnt = p4;
	}
	
	if (flag)
	{
		double ang = apnt.rad(B.s, B.e);
		double ans = 0.5 * sin(ang) * apnt.dist(W.s) * apnt.dist(W.e);
		if (ans < eps)
			printf("0.000\n");
		else
			printf("%.12lf\n", 0.5 * sin(ang) * apnt.dist(W.s) * apnt.dist(W.e));
	}
	else
		printf("inf\n");
}

void Clear()
{
	
}

int main()
{
	int T; readx(T);
	for (int t=1;t<=T;t++)
	{
		printf("Case %d: ", t);
		Solve();
		Clear();
	}
	
	
}