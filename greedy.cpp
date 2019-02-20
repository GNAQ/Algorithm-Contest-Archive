// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

int n,seq[500010],ans[500010]; double k;
const double eps=1e-9;

vector<int> edge[500010];

int tsiz[500010];

template<typename inp_typ>
void readx(inp_typ& x)
{
    x=0; int k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

void Is(int fx,int tx)
{
    edge[fx].push_back(tx);
}

void DFS(int now)
{
    tsiz[now]=1;
    for (int v=0;v<edge[now].size();v++)
    {
        DFS(edge[now][v]);
        tsiz[now]+=tsiz[edge[now][v]];
    }
}
void BuildTree()
{
    for (int i=1;i<=n;i++)
        Is((int)floor(i/k),i);
    DFS(0);
}

void Solve(int now,int l,int r)
{
    ans[now]=seq[l];
    for (int v=0;v<edge[now].size();v++)
    {
        Solve(edge[now][v],r-tsiz[edge[now][v]]+1,r);
        r-=tsiz[edge[now][v]];
    }
}

int main()
{
    readx(n); scanf("%lf",&k); 
    for (int i=1;i<=n;i++) readx(seq[i]);
    BuildTree(); sort(seq+1,seq+n+1);
    
    Solve(0,0,n);
    for (int i=1;i<=n;i++) printf("%d%c",ans[i]," \n"[i==n]);
}