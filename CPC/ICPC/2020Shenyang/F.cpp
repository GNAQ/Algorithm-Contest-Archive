#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXN=1e6+100;

int n;


template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
struct node{
	int val;
	int pos;
	bool friend operator <(node a,node b)
	{
		if(a.val==b.val) return a.pos<b.pos;
		else return a.val<b.val;
	}
}dat[MAXN];
int fa[MAXN],siz[MAXN];
int find(int x)
{
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	readx(n);
	for(int i=0;i<=n;i++)
	{
		fa[i]=i;
		siz[i]=1;
	}
		
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&dat[i].val);
		dat[i].pos=i;
	}
	sort(dat+1,dat+n+1);
	int ans=0,max_pos=0;
	for(int i=1;i<=n;i++)
	{
		max_pos=max(max_pos,dat[i].pos);
		siz[find(dat[i].pos-1)]+=siz[find(dat[i].pos)];
		fa[find(dat[i].pos)]=find(dat[i].pos-1);
		if(siz[find(dat[i].pos)]==max_pos+1) ans++;
	}
	cout<<ans;
}