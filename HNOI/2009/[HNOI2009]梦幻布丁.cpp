#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include<map>
#include<set>
#include<queue>
#include<vector>
#define ll long long
using namespace std;

int n,m,seq[100010],opt,xc,yc;
int rots[1000010];
set<int> tree[1000010];
vector<int> cols;

int ans;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Hrs_Merge(int inx,int targ)
{
//	for (auto u:tree[inx])
	for (set<int>::iterator u=tree[inx].begin();u!=tree[inx].end();u++)
	{
		if (seq[(*u)-1]==targ) ans--;
		if (seq[(*u)+1]==targ) ans--;
		tree[targ].insert(*u);
	}
//	for (auto u:tree[inx]) seq[u]=targ;
	for (set<int>::iterator u=tree[inx].begin();u!=tree[inx].end();u++)
		seq[(*u)]=targ;
	tree[inx].clear();
}


int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(seq[i]);
	for (int i=1;i<=n;i++) ans+=(seq[i]!=seq[i-1]);
	for (int i=1;i<=n;i++)
	{
		rots[seq[i]]=seq[i];
		tree[seq[i]].insert(i);
	}
	
	for (int i=1;i<=m;i++)
	{
		readx(opt);
		if (opt==1)
		{
			readx(xc); readx(yc); 
			if (xc==yc) continue;
			if (tree[rots[xc]].size()>tree[rots[yc]].size()) swap(rots[yc],rots[xc]);
			Hrs_Merge(rots[xc],rots[yc]);
		}
		else printf("%d\n",ans);
	}
}
