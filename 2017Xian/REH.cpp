#include<iostream>
#include<cstdio>
#define ROOT 1,1,n
#define ls root<<1
#define rs root<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
using namespace std;
const int maxn=1e5+100;
struct node{
	int tag;
	int minx;
}tree[maxn<<2];
int dat[maxn];
void update(int root)
{
	tree[root].minx=min(tree[ls].minx,tree[rs].minx);
}
void push_down(int root)
{
	tree[ls].tag+=tree[root].tag;
	tree[rs].tag+=tree[root].tag;
	tree[ls].minx+=tree[root].tag;
	tree[rs].minx+=tree[root].tag;
	tree[root].tag=0;
}
void build(int root,int l,int r)
{
	tree[root].tag=0;
	tree[root].minx=0;
	if(l==r)
	{
		tree[root].minx=dat[l];
		return ;
	}
	else {
		int mid=(l+r)>>1;
		build(lson);
		build(rson);
		update(root);
	}
}
int query(int root,int l,int r,int L,int R)
{
	if(L<=l&&R>=r) return tree[root].minx;
	else {
		int mid=(l+r)>>1,ans=1e9+10;
		push_down(root);
		if(L<=mid) ans=min(ans,query(lson,L,R));
		if(R>mid)  ans=min(ans,query(rson,L,R));
		update(root);
		return ans;
	}
}
void change(int root,int l,int r,int L,int R,int delt)
{
	if(L<=l&&R>=r) 
	{
		tree[root].minx+=delt;
		tree[root].tag+=delt;
	}
	else {
		int mid=(l+r)>>1;
		push_down(root);
		if(L<=mid) change(lson,L,R,delt);
		if(R>mid)  change(rson,L,R,delt);
		update(root);
	}
}
int main()
{
	int T;cin>>T;
	while(T--)
	{
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&dat[i]);
		build(ROOT);
		long long ans=0;
		for(int i=1;i+k-1<=n;i++)
		{
			int l=i,r=i+k-1;
			int delt=query(ROOT,l,r);
			change(ROOT,l,r,-delt);
			ans+=delt;
		}
		printf("%lld\n",ans);
	}
}