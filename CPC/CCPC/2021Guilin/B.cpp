#include<bits/stdc++.h>
#define ROOT 1,1,n
#define ls root<<1
#define rs root<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
using namespace std;
const int maxn=1e6+100;
struct node{
	int nine;
	int zero;
	int val;
}tree[maxn<<2];
char ch[3][maxn];
int n,q;
void update(int root)
{
	tree[root].nine=tree[ls].nine&tree[rs].nine;
	tree[root].zero=tree[ls].zero&tree[rs].zero;
}
void push_down(int root)
{
	if(tree[root].nine)
	{
		tree[ls].nine=1;
		tree[rs].nine=1;
		tree[ls].zero=0;
		tree[rs].zero=0;
	}
	if(tree[root].zero)
	{
		tree[ls].zero=1;
		tree[rs].zero=1;
		tree[ls].nine=0;
		tree[rs].nine=0;
	}
}
int build(int root,int l,int r,int tag)
{
	if(l==r)
	{
		tree[root].val=ch[1][l]-'0'+ch[2][l]-'0'+tag;		
		if(tree[root].val%10==0) tree[root].zero=1;
		if(tree[root].val%10==9) tree[root].nine=1;
		if(tree[root].val>=10) 
		{
			tree[root].val-=10;
			return 1;
		}
		else return 0;
	}
	else {
		int mid=(l+r)>>1;
		int jz=build(lson,tag);
		jz=build(rson,jz);
		update(root);
		return jz;
	}
}
int ANS=0;
int query(int root,int l,int r,int pos,int delt)
{
	if(l==r)
	{
		int tag=0;
		// cout<<"tmp="<<tree[root].zero<<" "<<tree[root].val<<" "<<delt<<endl;
		if(tree[root].nine)
			tree[root].val=9;
		if(tree[root].zero)
			tree[root].val=0;
		if(tree[root].val+delt>=10)
			tag=-1;
		else {
			if(tree[root].val+delt<0)
				tag=1;
			else tag=0;
		}
		tree[root].val=tree[root].val+delt+tag*10;
		if(tree[root].val==9) 
			tree[root].nine=1;
		else tree[root].nine=0;
		if(tree[root].val==0)
			tree[root].zero=1;
		else tree[root].zero=0;
		// cout<<"!!!"<<tree[root].val<<" "<<tree[root].nine<<" "<<tree[root].zero<<endl;
		ANS=tree[root].val;
		return tag;
	}
	else {
		int mid=(l+r)>>1,ans;
		push_down(root);
		if(pos<=mid) ans=query(lson,pos,delt);
		else ans=query(rson,pos,delt);
		update(root);
		return ans;
	}
}
int change(int root,int l,int r,int L,int R,int tag)
{
	// cout<<"###"<<root<<" "<<tree[root].nine<<" "<<l<<" "<<r<<" "<<L<<" "<<R<<endl;
	if(L<=l&&R>=r) 
	{
		//cout<<l<<" "<<r<<" "<<tag<<endl;
		if(tag==-1&&tree[root].nine==1)
		{
			tree[root].nine=0;
			tree[root].zero=1;		
			return -1;
		}		
		if(tag==1&&tree[root].zero==1)
		{
			tree[root].nine=1;
			tree[root].zero=0;
			// cout<<"change"<<l<<" "<<r<<endl;
			return -1;
		}
		if(l==r)
		{
			if(tag==-1)
				tree[root].val++;
			else tree[root].val--;
			if(tree[root].val==9) 
				tree[root].nine=1;
			else tree[root].nine=0;		
			if(tree[root].val==0)
				tree[root].zero=1;
			else tree[root].zero=0;
			
			// cout<<"!!!ans="<<l<<endl;
			if(l==n) return l-1;
			else return l;
		}
		int mid=(l+r)>>1,ans;
		push_down(root);
		if(tag==-1)
		{
			if(tree[ls].nine)
			{
				tree[ls].nine=0;
				tree[ls].zero=1;
				// cout<<"add="<<l<<" "<<mid<<endl;
				ans=change(rson,L,R,tag);
			}
			else ans=change(lson,L,R,tag);
			update(root);
			return ans;
		}
		if(tag==1)
		{
			if(tree[ls].zero)
			{
				tree[ls].zero=0;
				tree[ls].nine=1;
				ans=change(rson,L,R,tag);
			}
			else ans=change(lson,L,R,tag);
			update(root);
			return ans;
		}
	}
	else {
		int mid=(l+r)>>1;
		push_down(root);
		int lans=0;
		if(L<=mid)
		{
			lans=change(lson,L,R,tag);
			if(lans!=-1) 
			{
				update(root);
				return lans;
			}
		}
		if(R>mid)
		{
			lans=change(rson,L,R,tag);
			update(root);
			return lans;
		}		
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	scanf("%s%s",ch[1]+1,ch[2]+1);
	reverse(ch[1]+1,ch[1]+n+1);
	reverse(ch[2]+1,ch[2]+n+1);
	ch[1][n+1]='0';ch[2][n+1]='0';n++;
	build(ROOT,0);
	for(int i=1;i<=q;i++)
	{
		int opt,pos,val,ansadd=1;
		scanf("%d%d%d",&opt,&pos,&val);pos=(n-1)-pos+1;
		int delt=(val+'0')-ch[opt][pos];
		// cout<<"???"<<delt<<endl;
		if(delt==0) 
		{
			query(ROOT,pos,delt);
			printf("%d %d\n",ANS,0);
			continue;
		}
		ch[opt][pos]=val+'0';
		int cg=query(ROOT,pos,delt);
		// cout<<"cg="<<cg<<endl;
		if(cg==-1) ansadd+=(change(ROOT,pos+1,n,cg)-pos+1);
		else if(cg==1) ansadd+=(change(ROOT,pos+1,n,cg)-pos+1);
		else ansadd++;
		printf("%d %d\n",ANS,ansadd);
		// cout<<"-----------"<<endl;
	}
}