#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define fst first
#define snd second
typedef long long ll;
using namespace std;

int n;
struct Point
{
	int x,y,z,id,w;
	
	Point(int inx=0,int iny=0,int inz=0,int inid=0)
	{
		x=inx; y=iny;
		z=inz; id=inid;
	}
	
	friend bool operator < (const Point A,const Point B) 
	{
		if (A.x==B.x)
		{
			if (A.y==B.y) return A.z<B.z;
			return A.y<B.y;
		}
		return A.x<B.x;
	}
};
Point pnt[200010];
int ans[200010],ans_bac[100010];
map<Point,int> mapx;

template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace FWT
{
	int lim,tree[200010];
	
	void Upd(int pos,int val)
	{
		for (;pos<=lim;pos+=(pos&(-pos)))
			tree[pos]+=val;
	}
	
	int Qry(int pos)
	{
		int ret=0;
		for (;pos;pos-=(pos&(-pos)))
			ret+=tree[pos];
		return ret;
	}
};

bool cmp_x(const Point& a,const Point& b)
{
	if (a.x==b.x) 
	{
		if (a.y==b.y) return a.z<b.z;
		return a.y<b.y;
	}
	return a.x<b.x;
}
bool cmp_y(const Point& a,const Point& b)
{
	if (a.y==b.y) return a.z<b.z;
	return a.y<b.y;
}

void Solve(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	
	Solve(l,mid);
	Solve(mid+1,r);
	
	sort(pnt+l,pnt+mid+1,cmp_y);
	sort(pnt+mid+1,pnt+r+1,cmp_y);
	
	int lb=l;
	for (int rb=mid+1;rb<=r;rb++)
	{
		while (lb<=mid && pnt[lb].y<=pnt[rb].y) 
		{
			FWT::Upd(pnt[lb].z,pnt[lb].w);
			lb++;
		}
		ans[pnt[rb].id]+=FWT::Qry(pnt[rb].z);
	}
	for (int i=l;i<lb;i++) FWT::Upd(pnt[i].z,-pnt[i].w);	
}

int main()
{
	freopen("flower1.in","r",stdin);
	freopen("dat.out","w",stdout);
	
	int tx,ty,tz,tmp_n,tmp_pos;
	readx(tmp_n); readx(FWT::lim);
	for (int i=1;i<=tmp_n;i++)
	{
		readx(tx); readx(ty); readx(tz);
		if ((tmp_pos=mapx[Point(tx,ty,tz)])!=0)
			pnt[tmp_pos].w++;
		else
		{
			n++;
			pnt[n]=Point(tx,ty,tz,n); pnt[n].w=1;
			mapx[pnt[n]]=n;
		}
	}
	mapx.clear();
	sort(pnt+1,pnt+n+1,cmp_x);
	
	for (int i=1;i<=n;i++)
		printf("%d %d %d %d\n",pnt[i].x,pnt[i].y,pnt[i].z,pnt[i].w);
	
	Solve(1,n);
	
	for (int i=1;i<=n;i++) ans_bac[ans[pnt[i].id]+pnt[i].w-1]+=pnt[i].w;
	for (int i=0;i<tmp_n;i++) printf("%d\n",ans_bac[i]);
}