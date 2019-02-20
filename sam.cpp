#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<iterator>
#include<queue>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

char str[100010]; int n,m;


template<typename inp_typ>
void readx(inp_typ& x)
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
		int ch[27],ends,maxs,suf;
	}node[200010];
	int end=1,samsiz=1;
	
	void Append(char c)
	{
		SAM_Node& now=node[++samsiz]; int pos=end;
		
		now.maxs=node[pos].maxs+1; now.ends=1; end=samsiz;
		for (;pos && !CH(pos,c);pos=node[pos].suf)
			CH(pos,c)=samsiz;
		
		if (!pos)
			now.suf=1;
		else if (node[CH(pos,c)].maxs==node[pos].maxs+1)
			now.suf=CH(pos,c);
		else
		{
			int pre=CH(pos,c);
			SAM_Node& N=node[++samsiz],& O=node[pre];
			
		}
	}
	
}

int main()
{
	readx(n); readx(m);
	scanf("%s",str+1);
	
	
	
}