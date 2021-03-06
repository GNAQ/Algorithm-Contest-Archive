#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<map>
#define eps 1e-8
#define ll long long
using namespace std;

int fwt[100010]={0},n,_n;
struct asks { int typ,I,K,A,B,C; double val; }ask[100010];
char chr[10]={0};

int _ans=0,align[100010]={0};
bool vis[100010]={0},neg[100010]={0};

map<double,int> mapx;
double dts[100010]={0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
inline void upd(int pos,int val) { while (pos<=_n) { fwt[pos]+=val; pos+=(pos&(-pos)); } }
inline int que(int pos) { int ret=0; while (pos) { ret+=fwt[pos]; pos-=(pos&(-pos)); } return ret; }
inline double sol_equ(double A,double B,double C) { double ret=(C-B)/A; return ret; }

inline void _init()
{
	for (int i=1;i<=n;i++)
	{
		_n++;
		if (ask[i].typ==1 && ask[i].A) { dts[_n]=ask[i].val=sol_equ(ask[i].A,ask[i].B,ask[i].C); neg[i]=(ask[i].A<0); }
		else if (ask[i].typ==3) dts[_n]=ask[i].val=(double)ask[i].K;
		else _n--;
	}
	sort(dts+1,dts+_n+1);
	for (int i=1;i<=_n;i++) mapx[dts[i]]=i+1;
}

inline void READ()
{
	readx(n); int cnt=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",chr+1);
		if (chr[1]=='A')
		{
			readx(ask[i].A); readx(ask[i].B); readx(ask[i].C);
			ask[i].typ=1; align[++cnt]=i;
		}
		else if (chr[1]=='D') { readx(ask[i].I); ask[i].typ=2; }
		else { readx(ask[i].K); ask[i].typ=3; }
	}
}

int main()
{
	READ(); _init(); _n++;
	for (int i=1;i<=n;i++)
	{
		if (ask[i].typ==1)
		{
			if (!ask[i].A) { if (ask[i].B>ask[i].C) { _ans++; ask[i].I=1; } continue; }
			if (!neg[i]) upd(mapx[ask[i].val]+1,1);
			else { upd(1,1); upd(mapx[ask[i].val],-1); }
		}
		else if (ask[i].typ==2)
		{
			if (vis[ask[i].I]) continue; 
			int pos=align[ask[i].I]; vis[ask[i].I]=1;
			if (!ask[pos].A) { _ans-=(ask[pos].I==1); continue; }
			if (!neg[pos]) upd(mapx[ask[pos].val]+1,-1);
			else { upd(1,-1); upd(mapx[ask[pos].val],1); }
		}
		else printf("%d\n",_ans+que(mapx[ask[i].val]));
	}
	return 0;
}