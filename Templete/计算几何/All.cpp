#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<cmath>
#include<set>
#include<cstdlib>
#define ll long long
#define PAUSE system("pause")
#define eps 1e-8
using namespace std;

inline int Dcmp(double x) { if (fabs(x)<eps) return 0; return x>0 ? 1 : -1; }
struct Point
{
	double _x,_y,ag;
	Point (double inx=0,double iny=0) { _x=inx; _y=iny; }
	void GetAngle(Point src) { ag=atan2(_y-src._y,_x-src._x); }
};
Point operator + (const Point& a,const Point& b) { return Point(a._x+b._x,a._y+b._y); }
Point operator - (const Point& a,const Point& b) { return Point(a._x-b._x,a._y-b._y); }
Point operator * (const Point& a,const double& p) { return Point(a._x*p,a._y*p); }
Point operator / (const Point& a,const double& p) { return Point(a._x/p,a._y/p); }
bool operator < (const Point& a,const Point& b) { return a.ag<b.ag; }
bool operator == (const Point& a,const Point& b) { return ( (!Dcmp(a._x-b._x)) && (!Dcmp(a._y-b._y)) ); }

inline double DotProd(const Point& a,const Point& b) { return a._x*b._x+a._y*b._y; }
inline double CrossProd(const Point& a,const Point& b) { return a._x*b._y-a._y*b._x; }
inline double _Distance(const Point& a,const Point& b) { return sqrt(pow(a._x-b._x,2)+pow(a._y-b._y,2)); }
inline double PolyArea(vector<Point> poly)
{
	int num=poly.size(); double ret=0;
	for (int i=1;i<num-1;i++) ret+=CrossProd(poly[i]-poly[0],poly[i+1]-poly[0]);
	return fabs(ret)/2.000000;
}
inline double PolyPeri(vector<Point> poly)
{
	double ret=0; int num=poly.size();
	for (int i=0;i<num-1;i++) ret+=_Distance(poly[i],poly[i+1]);
	return ret;
}

struct Line
{
	Point p,v; double ag,A,B,C;
	Line(){}
	Line(Point p,Point v) : p(p),v(v) { ag=atan2(v._y,v._x); }
	void Get_General_Eqution() { A=-v._y; B=v._x; C=CrossProd(p,p+v); }
	bool operator < (const Line& a) const { return ag<a.ag; }
};

inline bool OnLeft(const Line& L,const Point& p) { return CrossProd(L.v,p-L.p)>0; }
inline Point GetLineIntersection(Line& a,Line& b)
{
	a.Get_General_Eqution(); b.Get_General_Eqution();
	double D=CrossProd(Point(a.A,a.B),Point(b.A,b.B));
	return Point(CrossProd(Point(a.B,a.C),Point(b.B,b.C))/D,CrossProd(Point(b.A,b.C),Point(a.A,a.C))/D);
}

inline vector<Point> ConvexHull(vector<Point> poly)
{
	register int num=poly.size(),h;
	vector<Point> sta(num+2),que;
	
	for (int i=1;i<num;i++) if (poly[i]._y<poly[0]._y) swap(poly[i],poly[0]);
	poly[0].ag=0.0; for (int i=1;i<num;i++) poly[i].GetAngle(poly[0]); 
	sort(poly.begin()+1,poly.end());
	
	for (int i=0;i<=2;i++) sta[i]=poly[i]; h=2;
	for (int i=3;i<num;i++)
	{
		while (h && Dcmp(CrossProd(sta[h-1]-sta[h],poly[i]-sta[h]))>0) h--;
		sta[++h]=poly[i];
	}
	sta[++h]=poly[0];
	for (int i=0;i<=h;i++) que.push_back(sta[i]);
	return que;
}

inline vector<Point> HalfPlaneIntersection(vector<Line> L)
{
	register int num=L.size();
	sort(L.begin(),L.end());
	
	register int h=0,t=0;
	vector<Point> poly(num),ans;
	vector<Line> que(num);
	que[0]=L[0];
	
	for (int i=1;i<num;i++)
	{
		while (h<t && (!OnLeft(L[i],poly[t-1]))) t--;
		while (h<t && (!OnLeft(L[i],poly[h]))) h++;
		
		que[++t]=L[i];
		if (!Dcmp(CrossProd(que[t].v,que[t-1].v)))
		{
			t--;
			if (OnLeft(que[t],L[i].p)) que[t]=L[i];
		}
		if (h<t) poly[t-1]=GetLineIntersection(que[t-1],que[t]);
	}
	
	while (h<t && (!OnLeft(que[h],poly[t-1]))) t--;
	if (t-h<=1) return ans;
	poly[t]=GetLineIntersection(que[t],que[h]);
	for (int i=h;i<=t;i++) ans.push_back(poly[i]);
	return ans;
}
