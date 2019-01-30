#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<queue>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;



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
        int ch[27],suf,maxs,ends;
    }node[300010];
    int samsiz=1,end=1;
    
    void Append(int c)
    {
        SAM_Node& now=node[++samsiz]; int pos=end;
        
        now.ends=1; now.maxs=node[end].maxs+1; end=samsiz;
        
        for (;pos && !CH(pos,c);pos=node[pos].suf) 
            CH(pos,c)=samsiz;
        
        if (!pos)
            now.suf=1;
        if (node[pos].maxs+1==node[CH(pos,c)].maxs)
            now.suf=CH(pos,c);
        else
        {
            int pre=CH(pos,c);
            SAM_Node& N=node[++samsiz],& O=node[pre];
            
            for (int i=1;i<=26;i++) N.ch[i]=O.ch[i];
            N.suf=O.suf; N.maxs=node[pos].maxs+1;
            
        }
    }
	
	struct ed { int pre,to; } edge[100010];
	int at=1,ptr[100010]; 
	
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
	
	void Get_Endsiz(int now)
	{
		for (int v=ptr[now];v;v=edge[v].pre) 
		{
			Get_Endsiz(edge[v].to);
			node[now].ends+=node[edge[v].to].ends;
		}
	}
    
    #undef CH
};

namespace SGT
{
	struct Seg_Tree
	{
		int l,r,mid;
		
	}tree[400010];
};

int main()
{
    
    
    
    
}