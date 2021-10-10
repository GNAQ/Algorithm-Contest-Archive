#include<iostream>
#include<cstdio>
#include<vector>
#include<cstdlib>
#define ls tree[root].l
#define rs tree[root].r
using namespace std;
const int MAXN=2e5+100;
struct E{
	int to;
	int next;
}e[MAXN<<1];
struct Node{
	int l;
	int r;
	int mx;
	int mn;
	int tag;
}tree[MAXN<<2];
int dat[MAXN],siz[MAXN],id[MAXN];
int n,m,cnt,tot,head[MAXN],TOT=1;
void add_edge(int u,int v)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	head[u]=tot;
}
void update(int root)
{
	if(tree[root].l&&tree[root].r)
	{
		tree[root].mx=max(tree[ls].mx,tree[rs].mx);
		tree[root].mn=min(tree[ls].mn,tree[rs].mn);
	}
	else if(ls) 
	{
		tree[root].mx=tree[ls].mx;
		tree[root].mn=tree[ls].mn;
	}
	else {
		tree[root].mx=tree[rs].mx;
		tree[root].mn=tree[rs].mn;
	}
}
void push_down(int root)
{
	if(ls)
	{
		tree[ls].mx+=tree[root].tag;
		tree[ls].mn+=tree[root].tag;
		tree[ls].tag+=tree[root].tag;
	}
	if(rs)
	{
		tree[rs].mx+=tree[root].tag;
		tree[rs].mn+=tree[root].tag;
		tree[rs].tag+=tree[root].tag;
	}
	tree[root].tag=0;
}
void add(int root,int l,int r,int pos,int num)
{
	if(l==r) tree[root].mx=tree[root].mn=num;
	else {
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			if(!tree[root].l)
				tree[root].l=++TOT;
			add(tree[root].l,l,mid,pos,num);
		}
		if(pos>mid)
		{
			if(!tree[root].r)
				tree[root].r=++TOT;
			add(tree[root].r,mid+1,r,pos,num);
		}
		update(root);
	}
}
void add_tag(int root,int l,int r,int L,int R,int delt)
{
	if(L<=l&&R>=r) 
	{
		tree[root].mx+=delt;
		tree[root].mn+=delt;
		tree[root].tag+=delt;
	}
	else {
		push_down(root);
		int mid=(l+r)>>1;
		if(L<=mid&&ls) add_tag(ls,l,mid,L,R,delt);
		if(R>mid&&rs)  add_tag(rs,mid+1,r,L,R,delt);
		update(root);
	}
}
void dfs(int x,int f,int dep)
{
	id[x]=++cnt;siz[x]=1;
	if(dat[x]) add(1,1,n,id[x],dep);
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==f) continue;
		dfs(to,x,dep+1);
		siz[x]+=siz[to];
	}
}
void get_ans(int x,int f)
{
	add_tag(1,1,n,id[x],id[x]+siz[x]-1,-2);
	if(tree[1].mx==tree[1].mn) {cout<<"YES"<<endl<<x;exit(0);}
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==f) continue;
		get_ans(to,x);
	}
	add_tag(1,1,n,id[x],id[x]+siz[x]-1,2);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=m;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		dat[tmp]=1;
	}
	dfs(1,-1,1);
	get_ans(1,-1);
	cout<<"NO";
}
