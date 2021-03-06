#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<string>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

const double eps=1e-8;
const double eps2=1e-5;

struct _Vec
{
	double x,y;
	_Vec(double _x=0,double _y=0) { x=_x; y=_y; }
};

_Vec pnt[10010],src[10010];
int n;
double ox=0,oy=0,wi[10010],mov_const=50000;
bool dirX=1,dirY=1;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Calc()
{
	_Vec res;
	for (int i=1;i<=n;i++)
	{
		pnt[i]=src[i];
		pnt[i].x-=ox; pnt[i].y-=oy;
	}
	for (int i=1;i<=n;i++)
	{
		if (fabs(pnt[i].x)<eps && fabs(pnt[i].y)<eps) continue;
		double vlen=sqrt(pnt[i].x*pnt[i].x+pnt[i].y*pnt[i].y);
		res.x+=wi[i]/vlen*pnt[i].x;
		res.y+=wi[i]/vlen*pnt[i].y;
	}
	double tmp=sqrt(res.x*res.x+res.y*res.y);
	ox+=(mov_const/tmp)*res.x;
	oy+=(mov_const/tmp)*res.y;
}

int main()
{
	readx(n); int tmpx,tmpy;
	for (int i=1;i<=n;i++) scanf("%lf%lf%lf",&src[i].x,&src[i].y,&wi[i]);
	
	while (1)
	{
		double px=ox,py=oy;
		Calc();
		if (fabs(px-ox)<eps2 && fabs(py-oy)<eps2) break;
		if (dirX!=(ox>px) || dirY!=(oy>py)) 
		{
			dirX=(ox>px);
			dirY=(oy>py);
			mov_const*=0.95;
		}
	}
	printf("%.3lf %.3lf\n",ox,oy);
}
