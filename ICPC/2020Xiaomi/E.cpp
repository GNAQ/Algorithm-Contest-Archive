#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

int n,m;
int ai[200010],pi[200010];
vector<int> elem[200010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

struct Seg_Tree
{
	int l,r;
	int ans,val;
	int tag;
} t[200010*4];

#define LCH (u<<1)
#define RCH (u<<1|1)

int lx,rx,vx,px;

void Pushup(int u)
{
	// t[u].val=min(t[LCH].val,t[RCH].val);
	t[u].ans=min(t[LCH].ans,t[RCH].ans);
}

void Pushdown(int u)
{
	if (t[u].tag==-1) return;
	int tmp=t[u].tag; t[u].tag=-1;
	t[LCH].tag=t[RCH].tag=t[LCH].val=t[RCH].val=tmp;
	t[LCH].ans=tmp-t[LCH].r+1;
	t[RCH].ans=tmp-t[RCH].r+1;
}

void BuildTree(int u,int L,int R)
{
	t[u].l=L; t[u].r=R; t[u].tag=-1;
	if (L==R)
	{
		t[u].ans=pi[L]-L+1;
		t[u].val=pi[L];
		return;
	}
	int m=(L+R)/2;
	BuildTree(LCH,L,m); BuildTree(RCH,m+1,R);
	Pushup(u);
}

void Upd(int u)
{
	if (t[u].l>=lx && t[u].r<=rx)
	{
		t[u].val=vx; t[u].ans=vx-t[u].r+1;
		t[u].tag=vx; // add tags
		return;
	}
	Pushdown(u);
	int m=(t[u].l+t[u].r)/2;
	if (lx<=m) Upd(LCH);
	if (rx>m) Upd(RCH);
	Pushup(u);
}

int Qry1(int u) // Query val by a point
{
	if (t[u].l==px && t[u].r==px)
		return t[u].val;
	Pushdown(u);
	int m=(t[u].l+t[u].r)/2, ret;
	if (px<=m) ret=Qry1(LCH);
	else ret=Qry1(RCH);
	Pushup(u);
	return ret;
}

int GetAns()
{
	// just return t[1]~!
	return t[1].ans;
}

int FindRx(int li,int ri,int val) // find a border | val means P[j]
{
	px=li;
	if (Qry1(1)>=val) return -1; // don't change
	
	int mid, ans;
	while (li<=ri)
	{
		mid=(li+ri)/2;
		px=mid; int ret=Qry1(1);
		
		if (ret<val) 
		{
			li=mid+1;
			ans=mid;
		}
		else ri=mid-1;
	}
	return ans;
}

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) 
	{
		readx(ai[i]);
		elem[ai[i]].push_back(i);
	}
	
	if (m==1)
		{ printf("1\n"); return 0; }
	
	int pos1=1e8;
	for (int i=n;i>=1;i--)
	{
		if (ai[i]==1) pos1=i;
		pi[i]=pos1;
	}
	BuildTree(1,1,n);
	
	printf("1 ");
	for (int i=2;i<=m;i++)
	{
		int pre_pos=0;
		for (int j:elem[i])
		{
			lx=pre_pos+1; 
			rx=FindRx(lx,j,j);
			if (rx!=-1) 
			{
				vx=j;
				Upd(1);
			}
			pre_pos=j;
		}
		if (pre_pos<n)
		{
			vx=1e8; lx=pre_pos+1; rx=n;
			Upd(1);
		}
		printf("%d%c", GetAns()," \n"[i==m]);
	}
	return 0;
}

// 有激进的策略可以合并区间赋值信息
// 左右子树相同 -> 合并值; 否则 -1
// 这样可以优化

/* 
 讨论一下为什么只需要考虑向左合并
 其实是考虑了所有区间
 不过选定了一个端点，然后强行考虑这个端点的一切情况
 这样就只需要维护另一个，把每个情况的（这里是右）端点维护到最优
 这样就一定能出答案（毕竟答案需要有一个左端点，一定在这 n 个里面） 
*/