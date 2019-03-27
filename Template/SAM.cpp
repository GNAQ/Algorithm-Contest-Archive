#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

ll ans,len; char str[1000010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SAM
{
	#define CH(a,b) node[a].ch[b]
	
	struct SAM_Node
	{
		int maxs,ends,ch[27],suf;
		
		SAM_Node() {}
	}node[3000010];
	int top=1,end=1,samsiz=1;
	
	void Extend(int c)
	{
		SAM_Node& now=node[++samsiz]; int pos=end;
		
		now.maxs=node[end].maxs+1; now.ends=1; end=samsiz; 
		for (;pos && !CH(pos,c);pos=node[pos].suf) 
			CH(pos,c)=samsiz;
		
		if (!pos)
			now.suf=top;
		else if (node[pos].maxs+1==node[CH(pos,c)].maxs)
			now.suf=CH(pos,c);
		else
		{
			int pre=CH(pos,c);
			SAM_Node& N=node[++samsiz],& O=node[pre];
			
			for (int i=1;i<=26;i++) N.ch[i]=O.ch[i];
			N.suf=O.suf; N.maxs=node[pos].maxs+1; 
			O.suf=now.suf=samsiz;
			
			for (int i=pos;CH(i,c)==pre;i=node[i].suf) 
				CH(i,c)=samsiz;
		}
	}
	
	// prefix tree
	struct ed { int pre,to; };
	ed edge[3000010]; int at=1,ptr[3000010];
	
	void Is(int fx,int tx)
	{
		at++;
		edge[at].pre=ptr[fx];
		edge[at].to=tx;
		ptr[fx]=at;
	}
	
	void Build_Tree() // the root of the tree is node [1]
	{
		for (int i=2;i<=samsiz;i++) 
			Is(node[i].suf,i);
	}
	
	void Get_Endpos(int now)
	{
		for (int v=ptr[now];v;v=edge[v].pre) 
		{
			Get_Endpos(edge[v].to);
			node[now].ends+=node[edge[v].to].ends;
		}
	}
	
	#undef CH
};

int main()
{
	scanf("%s",str+1); len=strlen(str+1);
	
	for (int i=1;i<=len;i++) SAM::Extend(str[i]-'a'+1);
	SAM::Build_Tree(); SAM::Get_Endpos(1);
	
	for (int i=2;i<=SAM::samsiz;i++) if (SAM::node[i].ends!=1)
		ans=max(ans,1LL*SAM::node[i].maxs*SAM::node[i].ends);
	printf("%lld\n",ans);
}
