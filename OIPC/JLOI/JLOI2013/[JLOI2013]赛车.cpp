#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstdlib>
#define ll long long
#define eps 1e-8
using namespace std;

inline int DCmp(double x) { if (fabs(x)<eps) return 0; return x>0? 1 : -1; }
struct Point
{
    double _x,_y,ag;
    Point (double inx=0,double iny=0) { _x=inx; _y=iny; }
};
Point operator + (const Point& a,const Point& b) { return Point(a._x+b._x,a._y+b._y); }
Point operator - (const Point& a,const Point& b) { return Point(a._x-b._x,a._y-b._y); }
Point operator * (const Point& a,const double& p) { return Point(a._x*p,a._y*p); }
inline double CrossProd(const Point& a,const Point& b) { return a._x*b._y-a._y*b._x; }

struct Line
{
    Point p,v; double ag; int A,B,C,cod;
    Line(){}
    Line(Point p,Point v) : p(p),v(v) { ag=atan2(v._y,v._x); }
    void Get_General_Eqution() { A=-v._y; B=v._x; C=CrossProd(p,p+v); }
    bool operator < (const Line& a) const { if (A==a.A) return C<a.C; return A<a.A; }
};

inline double GetLineIntersection(Line& a,Line& b)
{
    double ret=(double)(a.C-b.C)/(double)(b.A-a.A);
    return ret;
}
inline bool Judgex(Line a,Line b,Line c)
{
    double x_1=GetLineIntersection(a,b);
    double x_2=GetLineIntersection(a,c);
    return x_1>x_2;
}
inline bool cmp1(Line a,Line b) { return a.cod<b.cod; }

inline void HalfPlaneIntersection(vector<Line> L)
{
    register int num=L.size(),t=0;
    sort(L.begin(),L.end());
    
    vector<Line> que(num);
    for (int i=0;i<num;i++)
    {
        while (t>0 && GetLineIntersection(que[t],L[i])<0) t--;
        while (t>1 && Judgex(que[t-1],que[t],L[i])) t--;
        que[++t]=L[i];
    }
    
    sort(que.begin()+1,que.begin()+t+1,cmp1);
    cout<<t<<endl;
    for (int i=1;i<=t;i++) printf("%d%c",que[i].cod," \n"[i==t]);
}

int N,K[100010]={0},V[100010]={0};
vector<Line> Ln;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

int main()
{
    readx(N);
    for (int i=1;i<=N;i++) readx(K[i]); for (int i=1;i<=N;i++) readx(V[i]);
    
    Line qwq;
    for (int i=1;i<=N;i++)
    {
        qwq.A=V[i]; qwq.B=-1; qwq.C=K[i]; qwq.cod=i;
        Ln.push_back(qwq);
    }
    HalfPlaneIntersection(Ln);
    return 0;
}