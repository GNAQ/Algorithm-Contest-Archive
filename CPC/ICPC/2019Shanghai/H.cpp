#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
struct Edge
{
    int nxt,to;
 
    Edge(){}
    Edge(int nxt,int to):nxt(nxt),to(to){}
}e[200010];
int head[100010],cnt;
 
int n,k;
vector<int>son[100010];
 
void addedge(int u,int v)
{
    e[++cnt]=Edge(head[u],v);
    head[u]=cnt;
}
 
ll val[100010],dp[100010];
 
bool cmp(int a,int b)
{
    return dp[a]>dp[b];
}
 
void dfs(int now,int fa)
{
    for(int i=head[now];i;i=e[i].nxt)
    {
        int vs=e[i].to;
        if(vs==fa) continue;
        dfs(vs,now);
        son[now].push_back(vs);
    }
}
 
ll checknow,ansnow;
 
void cut(int now,int fa)
{
    dp[now]=val[now];
    for(int i=head[now];i;i=e[i].nxt)
    {
        int vs=e[i].to;
        if(vs==fa) continue;
        cut(vs,now);
        dp[now]+=dp[vs];
    }
    if(dp[now]>checknow)
    {
        sort(son[now].begin(),son[now].end(),cmp);
        for(int i=0;dp[now]>checknow;i++)
        {
            dp[now]-=dp[son[now][i]];
            ansnow++;
        }
    }
}
 
bool check()
{
    cut(1,0);
    if(ansnow<=k-1) return 1;
    else return 0;
}
 
 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    for(int o=1;o<=T;o++)
    {
        cin>>n>>k;
        for(int i=1;i<n;i++)
        {
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        dfs(1,0);
        ll sum=0,maxx=0;
        for(int i=1;i<=n;i++)
        {
            cin>>val[i];
            sum+=val[i];
            maxx=max(maxx,val[i]);
        }
        ll l=maxx,r=sum;
        while(l<r)
        {
            ll mid=l+r>>1;
            checknow=mid,ansnow=0;
            if(check()) r=mid;
            else l=mid+1;
        }
        cout<<"Case #"<<o<<": "<<l<<'\n';
        memset(head,0,4*n+4);
        cnt=0;
        for(int i=1;i<=n;i++) son[i].clear();
    }
}