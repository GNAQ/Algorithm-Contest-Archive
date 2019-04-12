#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;



template<typename inp_t>
void readx(inp_t x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SAM
{
	#define CH(a,b) node[a].ch[b]
	
	struct SAM_Node { int ch[27],ends,maxs,suf; } node[1200010];
	int samsiz,end;
	
	void Append(const int c)
	{
		SAM_Node& now=node[++samsiz]; int pos=end;
		now.ends=1; now.maxs=node[end].maxs+1; end=samsiz;
		
	}
	
	struct SAMed { int pre,to; } edge[1200010];
	int at=1,ptr[1200010];
	void Is(int fx,int tx)
	{
		at++;
		edge[at].pre=ptr[fx];
		edge[at].to=tx;
		ptr[fx]=at;
	}
	void BuildTree()
	{
		for (int i=2;i<=samsiz;i++) 
			Is(node[i].suf,i);
	}
	void GetEndP(int now)
	{
		for (int v=ptr[now];v;v=edge[v].pre)
		{
			GetEndP(edge[v].to);
			node[now].ends+=node[edge[v].to].ends;
		}
	}
};

namespace LCT
{
	#define LCH tree[inx].ch[0]
	#define RCH tree[inx].ch[1]
	
	struct Splay_Node
	{
		int fa,ch[2],rev,val,tag;
	} tree[1200010];
	int tsiz;
	
	#undef LCH
	#undef RCH
};

int main()
{
	
	
}