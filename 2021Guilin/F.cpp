#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const double eps = 1e-9;

int sgn(double x)
{
	if (fabs(x) < eps) 
		return 0;
	if (x < 0) return -1;
	return 1;
}

struct Point
{
	double x, y;
	Point(double ix, double iy)
		: x(ix), y(iy) {}
	Point() {}
	
	Point operator + (Point b)
	{
		return Point(x+b.x, y+b.y);
	}
	Point operator - (Point b)
	{
		return Point(x-b.x, y-b.y);
	}
	bool operator == (Point b)
	{
		return (sgn(x-b.x)==0 && sgn(y-b.y)==0);
	}
	double operator * (Point b)
	{
		return x*b.x + y*b.y;
	}
	double operator ^ (Point b)
	{
		return x*b.y - y*b.x;
	}
	
	double dist(Point b)
	{
		return hypot(x-b.x, y-b.y);
	}
};

struct Line
{
	Point s, e;
	Line(Point _s, Point _e)
		: s(_s), e(_e) {}
	
	bool operator == (Line b)
	{
		return (s==b.s) && (e==b.e);
	}
	
	double length()
	{
		return s.dist(e);
	}
	
	int LineCrxSeg(Line v)
	{
		int d1 = sgn((e-s)^(v.s-s));
		int d2 = sgn((e-s)^(v.e-s));
		if ((d1^d2)==-2) return 2;
		return (d1==0 || d2==0);
	}
	
	Point CrxPoint(Line v)
	{
		double a1 = (v.e-v.s)^(s-v.s);
		double a2 = (v.e-v.s)^(e-v.s);
		return Point((s.x*a2-e.x*a1)/(a2-a1), (s.y*a2-e.y*a1)/(a2-a1));
	}
	
};

Point lr[600010], sm[600010];
int n, m;
double prelen[400010];

double LenSum(int b, int e)
{
	if (e==b) 
		return 0;
	if (e > b)
		return prelen[e] - prelen[b];
	else
		return prelen[n+1] - prelen[b] + prelen[e];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i=1;i<=n;i++)
		scanf("%lf%lf", &lr[i].x, &lr[i].y);
	for (int i=1;i<=m;i++)
		scanf("%lf%lf", &sm[i].x, &sm[i].y);
	lr[n+1] = lr[1];
	sm[m+1] = sm[1];
	
	for (int i=2;i<=n+1;i++)
		prelen[i] = prelen[i-1] + lr[i].dist(lr[i-1]);
	
	double ans = 0;
	Line li = Line(sm[1], sm[2]);
	int l = -1, r = -1;
	Point pl, pr;
	for (int i=1;i<=n;i++)
	{
		Line tmp = Line(lr[i], lr[i+1]);
		if (li.LineCrxSeg(tmp)!=0)
		{
			if (l == -1)
			{
				pl = li.CrxPoint(tmp);
				l = i;
			}
			else
			{
				pr = li.CrxPoint(tmp);
				r = i;
				if (!(pr == pl))
					break;
			}
		}
	}
	
	if ((li.s.dist(pl)) > (li.e.dist(pl)))
	{
		swap(l, r);
		swap(pl, pr);
	}
	
	double tans = pr.dist(lr[r]);
	tans += pl.dist(lr[l+1]);
	tans += LenSum(l+1, r);
	ans += (tans / prelen[n+1]) * li.length();
	
	for (int i=2;i<=m;i++)
	{
		li = Line(sm[i], sm[i+1]);
		
		Line tmp = Line(lr[l], lr[l+1]);
		while (li.LineCrxSeg(tmp)==0 
			|| li.s.dist(li.CrxPoint(tmp)) > li.e.dist(li.CrxPoint(tmp)))
		{
			l++;
			if (l == n + 1) l = 1;
			tmp = Line(lr[l], lr[l+1]);
		}
		pl = li.CrxPoint(tmp);
		
		tmp = Line(lr[r], lr[r+1]);
		
		while (li.LineCrxSeg(tmp)==0 
			|| li.e.dist(li.CrxPoint(tmp)) > li.s.dist(li.CrxPoint(tmp)))
		{
			r++;
			if (r == n + 1) r = 1;
			tmp = Line(lr[r], lr[r+1]);
		}
		pr = li.CrxPoint(tmp);
		
		tans = pr.dist(lr[r]);
		tans += pl.dist(lr[l+1]);
		tans += LenSum(l+1, r);
		ans += (tans / prelen[n+1]) * li.length();
	}
	
	printf("%.12lf\n", ans);
	return 0;
}