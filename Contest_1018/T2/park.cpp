#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstdlib>
#define ll long long
using namespace std;

int n,L;
int xs[510],ys[510];

int fa[510];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

double GetDist(int x_1,int y_1,int x_2,int y_2)
{
	return sqrt((x_1-x_2)*(x_1-x_2) + (y_1-y_2)*(y_1-y_2));
}

inline int Find(int x) {
  while(fa[x]>=0&&fa[fa[x]]>=0)x=fa[x]=fa[fa[x]];return fa[x]<0?x:fa[x];
}
inline void Merge(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) {if(fa[x]<fa[y])fa[y]=x;else{if(fa[x]==fa[y])fa[y]--;fa[x]=y;}}
}

bool chk(double dist)
{
	// for (int i=0;i<=n+1;i++) fa[i]=i;
	memset(fa,-1,sizeof fa);
	for (int i=1;i<=n;i++)
	{
		for (int j=i+1;j<=n;j++) if (GetDist(xs[i],ys[i],xs[j],ys[j])<dist) Merge(i,j);
	}
	for (int i=1;i<=n;i++) if (ys[i]<dist) Merge(0,i);
	for (int i=1;i<=n;i++) if (L-ys[i]<dist) Merge(i,n+1);
	if (Find(0)==Find(n+1)) return false;
	return true;
}

int main()
{
	readx(n); readx(L);
	for (int i=1;i<=n;i++) { readx(xs[i]); readx(ys[i]); }
	
	double l=0.0,r=L+1,mid,ans=-1;
	int upat=(L<300?14:(L<1000?18:25));
	for (int timer=1;timer<=upat;timer++)
	{
		mid=(l+r)/2.0;
		if (chk(mid)) { ans=l=mid; }
		else r=mid;
	}
	printf("%.3lf\n",ans);
	return 0;
}