#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace CG
{
	const double eps = 1e-8;
	const double inf = 1e20;
	const double pi = acos(-1.0);
	const int maxp = 1010;
	
	int sgn(double x)
	{
		if (fabs(x) < eps) return 0;
		if (x<0) return -1;
		else return 1;
	}
	
	inline double sqr(double x) { return x*x; }
	
	struct Point
	{
		double x,y, id;
		Point() {}
		Point(double _x, double _y) { x=_x; y=_y; }
		void input()
		{
			scanf("%lf%lf", &x, &y);
		}
		void output()
		{
			printf("%.2lf %.2lf\n", x, y);
		}
		
		bool operator == (Point b) const 
		{
			return sgn(x-b.x)==0 && sgn(y-b.y)==0;
		}
		
		bool operator < (Point b) const
		{
			return sgn(x-b.x)==0 ? sgn(y-b.y)<0 : x<b.x;
		}
		
		Point operator - (const Point &b) const
		{
			return Point(x-b.x, y-b.y);
		}
		
		double operator ^ (const Point &b) const
		{
			return x*b.y-y*b.x;
		}
		
		double operator * (const Point &b) const
		{
			return x*b.x+y*b.y;
		}
		
		double len() { return hypot(x,y); }
		double len2() { return x*x+y*y; }
		
		double distance(Point p)
		{
			return hypot(x-p.x, y-p.y);
		}
		
		Point operator + (const Point &b) const
		{
			return Point(x+b.x, y+b.y);
		}
		Point operator * (const double &k) const
		{
			return Point(x*k, y*k);
		}
		Point operator / (const double &k) const 
		{
			return Point(x/k, y/k);
		}
		
		double rad(Point a, Point b)
		{
			Point p = *this;
			return fabs(atan2( fabs((a-p)^(b-p)), (a-p)*(b-p) ));
		}
		
		Point trunc(double r)
		{
			double l = len();
			if (!sgn(l)) return *this;
			r/=l;
			return Point(x*r, y*r);
		}
		
		Point rotleft() { return Point(-y, x); }
		Point retright() { return Point(y, -x); }
		
		Point rotate(Point p, double angle)
		{
			Point v = (*this) - p;
			double c = cos(angle), s=sin(angle);
			return Point(p.x + v.x*c - v.y*s,  p.y + v.x*s + v.y*c);
		}
	};
	
	struct Line
	{
		Point s, e;
		Line() {}
		Line(Point _s, Point _e)
		{
			s = _s;
			e = _e;
		}
		
		bool operator == (Line v)
		{
			return (s==v.s) && (e==v.e);
		}
		
		Line(Point p, double angle)
		{
			s=p;
			if (sgn(angle-pi/2)==0)
			{
				e=(s+Point(0,1));
			}
			else
			{
				e = (s + Point(1, tan(angle)));
			}
		}
		
		// ax+by+c=0
		Line(double a, double b, double c)
		{
			if (sgn(a)==0)
			{
				s=Point(0,-c/b);
				e=Point(1,-c/b);
			}
			else if (sgn(b)==0)
			{
				s=Point(-c/a, 0);
				e=Point(-c/a, 1);
			}
			else
			{
				s=Point(0, -c/b);
				e=Point(1, (-c-a)/b);
			}
		}
		
		void input()
		{
			s.input();
			e.input();
		}
		
		void adjust()
		{
			if (e<s) swap(s,e);
		}
		
		double length() { return s.distance(e); }
		double angle()
		{
			double k = atan2(e.y-s.y, e.x-s.x);
			if (sgn(k) < 0) k+=pi;
			if (sgn(k-pi) == 0) k-=pi;
			return k;
		}
		
		int relation(Point p)
		{
			int c = sgn((p-s)^(e-s));
			if (c<0) return 1;
			else if (c>0) return 2;
			else return 3;
		}
		
		bool pointonseg(Point p)
		{
			return sgn((p-s)^(e-s))==0 && sgn((p-s)*(p-e))<=0;
		}
		
		bool parallel(Line v)
		{
			return sgn((e-s)^(v.e-v.s))==0;
		}
		
		int segcrossseg(Line v)
		{
			int d1=sgn((e-s)^(v.s-s));
			int d2=sgn((e-s)^(v.e-s));
			int d3=sgn((v.e-v.s)^(s-v.s));
			int d4=sgn((v.e-v.s)^(e-v.s));
			if ( (d1^d2) ==-2 && (d3^d4) ==-2 ) return 2;
			return (d1==0 && sgn((v.s-s)*(v.s-e))<=0) || 
				(d2==0 && sgn((v.e-s)*(v.e-e))<=0) || 
				(d3==0 && sgn((s-v.s)*(s-v.e))<=0) || 
				(d4==0 && sgn((e-v.s)*(e-v.e))<=0);
		}
		
		int linecrossseg(Line v)
		{
			int d1 = sgn((e-s)^(v.s-s));
			int d2 = sgn((e-s)^(v.e-s));
			if ((d1^d2)==-2) return 2;
			return (d1==0 || d2==0);
		}
		
		int linecrossline(Line v)
		{
			if ((*this).parallel(v))
				return v.relation(s)==3;
			return 2;
		}
		
		Point crosspoint(Line v)
		{
			double a1 = (v.e-v.s)^(s-v.s);
			double a2 = (v.e-v.s)^(e-v.s);
			return Point((s.x*a2 - e.x*a1)/(a2-a1), (s.y*a2 - e.y*a1)/(a2-a1));
		}
		
		double dispointtoline(Point p)
		{
			return fabs((p-s)^(e-s))/length();
		}
		
		double dispointtoseg(Point p)
		{
			if (sgn((p-s)*(e-s))<0 || sgn((p-e)*(s-e))<0)
				return min(p.distance(s), p.distance(e));
			return dispointtoline(p);
		}
		
		double dissegtoseg(Line v)
		{
			return min(min(dispointtoseg(v.s), dispointtoseg(v.e)), 
					   min(v.dispointtoseg(s), v.dispointtoseg(e)));
		}
		
		Point lineprog(Point p)
		{
			return s + ( ((e-s)*((e-s)*(p-s)))/((e-s).len2()) );
		}
		
		Point symmertypoint(Point p)
		{
			Point q = lineprog(p);
			return Point(2*q.x-p.x, 2*q.y-p.y);
		}
	};
}

int n,m, vy1;
double vy;

CG::Line l1[110];
vector<int> sp,ep;
CG::Point pts[410];
vector<int> dgo[410];
double dp[410];

bool cmp(CG::Point a, CG::Point b)
{
	return a.y<b.y;
}

int main()
{
	readx(n); readx(m); readx(vy1); vy=vy1;
	
	double ys,yl; int siz;
	
	for (int i=1;i<=n;i++)
	{
		l1[i].input();
		pts[i]=l1[i].s;
		pts[i+n]=l1[i].e;
		pts[i].id=pts[i+n].id=i;
	}
	
	for (int i=1;i<=n;i++)
	{
		// spj
		if ( ( min(pts[i].x, pts[i+n].x)<=(-m) ) && ( max(pts[i].x, pts[i+n].x) >= m ) )
		{	
			puts("-1");
			return 0;
		}
	}
	// spj
	if (n==1)
	{
		puts("0.00000000000");
		return 0;
	}
	
	// build y increase order
	sort(pts+1,pts+2*n+1, cmp);
	ys=pts[1].y-10; yl=pts[2*n].y+10;

	// build start point and end point
	for (int i=1;i<=2*n;i++) if (pts[i].x>-m && pts[i].x<m)
	{
		// start_point
		bool ok = true;
		CG::Line tmp = CG::Line(pts[i], CG::Point(pts[i].x, ys));
		for (int j=1;j<=n;j++) if (pts[i].id!=j) // Èç¹ûÃ»ÓÐ½»µ½,ÄÇÃ´¾ÍÊÇÒ»¸öÆðµã. 
		{
			if (tmp.segcrossseg(l1[j])!=0)
			{
				ok = false;
				break;
			}
		}
		if (ok) 
		{
			sp.push_back(i);
		}
		
		// end_point
		ok = true;
		tmp = CG::Line(pts[i], CG::Point(pts[i].x, yl));
		for (int j=1;j<=n;j++) if (pts[i].id!=j) // Èç¹ûÃ»ÓÐ½»µ½,
		{
			if (tmp.segcrossseg(l1[j])!=0)
			{
				ok = false;
				break;
			}
		}
		if (ok) 
		{
			ep.push_back(i);
		}
	}
	
	// find distinct reachable point for each point
	for (int i=1;i<=2*n;i++) if (pts[i].x>-m && pts[i].x<m)
	{
		for (int j=i+1;j<=2*n;j++) if (pts[j].x>-m && pts[j].x<m)
		{
			if (pts[i].id == pts[j].id) continue;
			
			CG::Line tmp= CG::Line(pts[i], pts[j]);
			bool ok = true;
			for (int ii=1;ii<=n;ii++) 
			{
				if (tmp.segcrossseg(l1[ii])==2)
				{
					ok = false;
				}
			}
			if (ok)
			{
				dgo[i].push_back(j);
			}
		}
		
	//	cout<<"Rec ";
	//	pts[i].output();
	//	siz = dgo[i].size()-1;
	//	for (int j=0;j<=siz;j++) pts[ dgo[i][j] ].output();
	}
	
	for (int i=1;i<=2*n;i++) dp[i]=10000*m;
	siz = sp.size();
	for (int i=0;i<siz;i++) dp[sp[i]]=0;
	
	for (int i=1;i<=2*n;i++)
	{
		siz = dgo[i].size()-1;
		for (int j=0;j<=siz;j++)
		{
			int id = dgo[i][j];
			if (pts[i].y-pts[id].y==0)
				;
			else
				dp[id] = min( dp[id], max(dp[i], vy1*abs(pts[i].x-pts[id].x)/(double)abs(pts[i].y-pts[id].y) ) );
		}
	}
	
	siz = ep.size()-1; double ans = m*10000;
	for (int i=0;i<=siz;i++) ans=min(ans, dp[ep[i]]);
	 if (ans>=m*9999) printf("-1\n");
	 else printf("%.10lf\n", ans);
    //printf("%.10lf\n", ans);
	return 0;
}