#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

vector<int> edge[100010];
int col[100010],n,tsiz[100010],vis[100010],hson[100010];
ll cnt[100010][2]; int bac[100010],maxv;

ll ans[100010];

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

void DFS1(int now,int fa)
{
    tsiz[now]=1;
    for (auto v:edge[now]) if (v!=fa)
    {
        DFS1(v,now);
        tsiz[now]+=tsiz[v];
        if (tsiz[v]>tsiz[hson[now]]) hson[now]=v;
    }
}

void Upd(int now,int fa,int val)
{
    int &C=bac[col[now]];
    cnt[C][0]--; cnt[C][1]-=col[now];
    C+=val;
    cnt[C][0]++; cnt[C][1]+=col[now];
    if (val==1) maxv=max(maxv,C);
    else while (!cnt[maxv][0]) maxv--;

    for (auto v:edge[now]) if (v!=fa && !vis[v]) Upd(v,now,val);
}


void DFS2(int now,int fa,int keep)
{
    for (auto v:edge[now]) if (v!=fa && v!=hson[now])
        DFS2(v,now,0);

    if (hson[now]) 
    {
        DFS2(hson[now],now,1);
        vis[hson[now]]=1;
    }
    
    Upd(now,fa,1);
    ans[now]=cnt[maxv][1];
    vis[hson[now]]=0;
    if (!keep) Upd(now,fa,-1);
}


int main()
{
    readx(n); int fx,tx;
    for (int i=1;i<=n;i++) readx(col[i]);
    for (int i=1;i<n;i++)
    {
        readx(fx); readx(tx);
        edge[fx].push_back(tx);
        edge[tx].push_back(fx);
    }
    DFS1(1,0);
    DFS2(1,0,1);
    for (int i=1;i<=n;i++) printf("%lld%c",ans[i]," \n"[i==n]);
}