//D1 F
#include<bits/stdc++.h>

using namespace std;

struct Node
{
    long double val;
    int x,y;

    Node(long double val=0,int x=0,int y=0):val(val),x(x),y(y){}

    bool operator<(const Node &other) const
    {
        return val>other.val;
    }
};

int pre[100010],nxt[100010];
int speed[100010],pos[100010];

priority_queue<Node>q;

bool vis[100010];

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>pos[i]>>speed[i];
        pre[i]=i-1,nxt[i]=i+1;
        if(speed[i-1]==speed[i]) continue;
        if(i-1) q.push(Node(1.0*(pos[i]-pos[i-1])/(1.0*(speed[i-1]-speed[i])),i-1,i));
    }
    int ans=n;
    vis[0]=vis[n+1]=1;
    while(!q.empty())
    {
        Node now=q.top();
        q.pop();
        if(now.val<0) continue;
        if(vis[now.x]||vis[now.y]) continue;
        vis[now.x]=vis[now.y]=1;
        ans-=2;
        int pr=pre[now.x],nx=nxt[now.y];
        pre[nx]=pr;
        nxt[pr]=nx;
        if(speed[pr]==speed[nx]) continue;
        q.push(Node((long double)(pos[nx]-pos[pr])/((long double)(speed[pr]-speed[nx])),pr,nx));
    }
    cout<<ans<<'\n';
    for(int i=1;i<=n;i++)
    {
        if(!vis[i]) cout<<i<<' ';
    }
    cout<<'\n';
}