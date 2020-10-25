#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;

char str[1000010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SAM
{
	#define CH(a,b) node[a].ch[b]
	
	struct SAM_Node
	{
		int ch[27],suf,maxs,ends;
	}node[2000010];
	int end=1,samsiz=1;
	
	void Append(int c)
	{
		SAM_Node& now=node[++samsiz]; int pos=end;
		
		end=samsiz; now.maxs=node[pos].maxs+1; now.ends=1;
		for (;pos && !CH(pos,c);pos=node[pos].suf)
			CH(pos,c)=samsiz;
		
		if (!pos)
			now.suf=1;
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
	
	struct ed { int pre,to; } edge[2000010];
	int at=1,ptr[2000010];
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
	
	void GetEndPos(int inx)
	{
		for (int v=ptr[inx];v;v=edge[v].pre)
		{
			GetEndPos(edge[v].to);
			node[inx].ends+=node[edge[v].to].ends;
		}
	}
	
	#undef CH
};

int main()
{
	scanf("%s",str+1); int len=strlen(str+1);
	for (int i=1;i<=len;i++) SAM::Append(str[i]-'a'+1);
	SAM::BuildTree(); SAM::GetEndPos(1);
	
	ll ans=0;
	for (int i=2;i<=SAM::samsiz;i++) if (SAM::node[i].ends>1)
		ans=max(ans,1LL*SAM::node[i].ends*SAM::node[i].maxs);
	printf("%lld\n",ans);
}
