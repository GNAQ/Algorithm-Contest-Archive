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
    
    #undef CH
};

int main()
{
    
    
    
    
}