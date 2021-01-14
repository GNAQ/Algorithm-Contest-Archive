#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
using namespace std;
const int MAXN=1e3+10;
struct node{
    int x;
    int y;
    int val;
    bool friend operator <(const node &a,const node &b)
    {
        return a.val>b.val;
    }
}edge[MAXN*MAXN*2];
int n,m,A,B,C,P,X[MAXN*MAXN],dx[10],dy[10],fa[MAXN*MAXN];
int find(int x)
{
    if(x!=fa[x]) fa[x]=find(fa[x]);
    return fa[x];
}
int main()
{
    int T;cin>>T;
    for(int ii=1;ii<=T;ii++)
    {      
        LL ans=0,cnt=0,a;
        cin>>n>>m>>a>>a>>a>>a;
        cin>>X[1]>>X[2]>>A>>B>>C>>P;
        for(int i=3;i<=n*m;i++)
            X[i]=(A*X[i-1]+B*X[i-2]+C)%P;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                int now=(i-1)*m+j,to;
                if(i!=1)
                {
                    to=(i-2)*m+j;
                    edge[++cnt].val=X[now]*X[to];
                    edge[cnt].x=now;
                    edge[cnt].y=to;
                }
                if(j!=1)
                {
                    to=(i-1)*m+j-1;
                    edge[++cnt].val=X[now]*X[to];
                    edge[cnt].x=now;
                    edge[cnt].y=to;                
                }
            }
        sort(edge+1,edge+cnt+1);
        for(int i=1;i<=n*m;i++)
            fa[i]=i;
        int e=0;
        for(int i=1;i<=cnt;i++)
        {
            int f1=find(edge[i].x),f2=find(edge[i].y);
            if(f1==f2) continue;
            fa[f1]=f2;e++;     
            ans+=edge[i].val;
            if(e==n*m-1) break;
        }
        printf("Case #%d: %lld\n",ii,ans);
    }
}