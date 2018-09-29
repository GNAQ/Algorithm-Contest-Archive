#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
#include<queue>
#define ll long long
using namespace std;

struct pri_seg
{
	int lc,rc,val;
}PGT[200010*22];
int tsiz=0,rootx[200010]={0},valu,lx,rx,kv;

int n,m,leftx,rightx;
int seq[200010]={0},setx[200010]={0},setlen;

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void init1()
{
	memcpy(setx,seq,sizeof(seq));
	setlen=unique(setx+1,setx+n+1)-(setx+1);
	sort(setx+1,setx+setlen+1);
	for (int i=1;i<=n;i++) seq[i]=lower_bound(setx+1,setx+setlen+1,seq[i])-setx;
}

inline void updatex(int inx,int& newx)
{
	newx=++tsiz; PGT[newx].val=PGT[inx].val+1;
	if (lx==rx) return;
	
	PGT[newx].lc=PGT[inx].lc; PGT[newx].rc=PGT[inx].rc;
	int mid=(lx+rx)>>1;
	if (valu<=mid) { rx=mid; updatex(PGT[inx].lc,PGT[newx].lc); }
	else { lx=mid+1; updatex(PGT[inx].rc,PGT[newx].rc); }
}

inline int queryx(int inx,int newx)
{
	if (lx==rx) return lx;
	kv=PGT[PGT[newx].lc].val-PGT[PGT[inx].lc].val; 
	int mid=(lx+rx)>>1;
	if (valu<=kv) { rx=mid; return queryx(PGT[inx].lc,PGT[newx].lc); }
	else { valu-=kv; lx=mid+1; return queryx(PGT[inx].rc,PGT[newx].rc); }
}

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(seq[i]);
	init1();
	
	for (int i=1;i<=n;i++)
	{
		valu=seq[i]; lx=1; rx=setlen;
		updatex(rootx[i-1],rootx[i]);
	}
	
	for (int i=1;i<=m;i++)
	{
		readx(leftx); readx(rightx); readx(valu);
		lx=1; rx=setlen;
		printf("%d\n",setx[queryx(rootx[leftx-1],rootx[rightx])]);
	}
	return 0;
}
