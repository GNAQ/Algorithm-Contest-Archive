#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<cstdlib>
#include<map>
#include<set>
#define ll long long
#define eps 1e-8
using namespace std;
 
inline int Dcmp(double x) { if (fabs(x)<eps) return 0; return x>0 ? 1 : -1; }
struct Point
{
    double _x,_y,ag;
    Point (double inx=0,double iny=0) { _x=inx; _y=iny; }
    void GetAngle(Point src) { ag=atan2(_y-src._y,_x-src._x); }
    bool operator < (const Point& a) const { return ag<a.ag; }
};
 
Point operator + (const Point& a,const Point& b) { return Point(a._x+b._x,a._y+b._y); }
Point operator - (const Point& a,const Point& b) { return Point(a._x-b._x,a._y-b._y); }
inline double CrossProd(const Point& a,const Point& b) { return a._x*b._y-a._y*b._x; }
 
struct Line
{
    Point p,v;
    double ag,A,B,C;
     
    Line(){}
    Line(Point p,Point v) : p(p),v(v) { ag=atan2(v._y,v._x); }
    void Get_General_Eqution() { A=-v._y; B=v._x; C=CrossProd(p,p+v); }
    bool operator < (const Line& a) const { return ag<a.ag; }
    double operator [] (double x) { Get_General_Eqution(); return -(A*x+C)/B; }
};
 
inline bool OnLeft(const Line& L,const Point& p) { return CrossProd(L.v,p-L.p)>0; }
inline Point GetLineIntersection(Line& a,Line& b)
{
    a.Get_General_Eqution(); b.Get_General_Eqution();
    double D=CrossProd(Point(a.A,a.B),Point(b.A,b.B));
    return Point(CrossProd(Point(a.B,a.C),Point(b.B,b.C))/D,CrossProd(Point(b.A,b.C),Point(a.A,a.C))/D);
}
 
Point _poly[150];
Line que[150];
int h=0,t=0;
 
inline void HalfPlaneIntersection(vector<Line> L)
{
    register int num=L.size();
    sort(L.begin(),L.end());
     
    que[0]=L[0];
    for (int i=1;i<num;i++)
    {
        while (h<t && OnLeft(L[i],_poly[t])) t--;
         
        que[++t]=L[i];
        if (!Dcmp(CrossProd(que[t].v,que[t-1].v)))
        {
            t--;
            if (OnLeft(que[t],L[i].p)) que[t]=L[i];
        }
        _poly[t]=GetLineIntersection(que[t-1],que[t]);
    }
}
 
vector<double> v1(120),v2(120);
vector<Line> L;
double s;
int n,k;
 
int main()
{
    scanf("%lf%d",&s,&n);
    for (int i=0;i<n-1;i++)
    {
        scanf("%lf%lf",&v1[i],&v2[i]);
        L.push_back(Line(Point(0,s/v2[i]),Point(1,(v2[i]-v1[i])/(v1[i]*v2[i]))));
    }
     
    HalfPlaneIntersection(L);
    scanf("%lf%lf",&v1[n-1],&v2[n-1]);
    L.push_back(Line(Point(0,s/v2[n-1]),Point(1,(v2[n-1]-v1[n-1])/(v1[n-1]*v2[n-1]))));
     
    k=lower_bound(que+h,que+t+1,L[n-1])-que;
    _poly[k]._x=min(s,max(0.000,_poly[k]._x));
     
    double ans=1e17;
    for (int i=0;i<n-1;i++) ans=min(ans,L[i][_poly[k]._x]-L[n-1][_poly[k]._x]);
    if (ans>=0.0) printf("%.2lf %.2lf %.0lf\n",_poly[k]._x,s-_poly[k]._x,ans*3600);
    else printf("NO\n");
     
    return 0;
}