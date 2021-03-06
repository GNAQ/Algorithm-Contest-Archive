#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<iterator>
#include<queue>
using namespace std;

struct tr
{
    int depth,father;
}tree[110]={0};
struct ed
{
    int pre,to;
}edge[110]={0};
int nodenum,fx,tx,pointer[110]={0},at=0;

int l[110][12]={0};
int answ=1,ansd=0;

inline void Insert()
{
    at++;
    edge[at].pre=pointer[fx];
    edge[at].to=tx;
    pointer[fx]=at;
}

inline void bfs()
{
    queue<int> que;
    int maxw=0,noww=0,cachen,prex;
    
    que.push(1); noww=1;
    while (!que.empty())
    {
        cachen=que.front(); que.pop();
        if (tree[cachen].depth==noww) maxw++;
        else
        {
            noww=tree[cachen].depth;
            answ=max(answ,maxw);
            maxw=1;
        }
        prex=pointer[cachen];
        while (prex)
        {
            que.push(edge[prex].to);
            prex=edge[prex].pre;
        }
    }
    answ=max(answ,maxw);
}

void dfs(int nownode)
{
    l[nownode][0]=tree[nownode].father;
    for (int i=1;i<=10;i++) l[nownode][i]=l[l[nownode][i-1]][i-1];
    
    ansd=max(ansd,tree[nownode].depth);
    int prex=pointer[nownode];
    while (prex)
    {
        dfs(edge[prex].to);
        prex=edge[prex].pre;
    }
}

inline int LCA(int u,int v)
{
    for (int i=10;i>=0;i--) if (tree[l[u][i]].depth>=tree[v].depth) u=l[u][i];
    if (u==v) return v;
    for (int i=10;i>=0;i--) if (l[u][i]!=l[v][i])
    {
        u=l[u][i]; v=l[v][i];
    }
    return tree[u].father;
}

int main()
{
    scanf("%d",&nodenum);
    tree[1].father=-1; tree[1].depth=1;
    for (int i=1;i<nodenum;i++)
    {
        scanf("%d%d",&fx,&tx);
        tree[tx].father=fx;
        tree[tx].depth=tree[fx].depth+1;
        Insert();
    }
    bfs();
    dfs(1);
    printf("%d\n%d\n",ansd,answ);
    
    int un,vn,uvlca; bool flag=false;
    scanf("%d%d",&un,&vn);
    if (tree[un].depth<tree[vn].depth)
    {
        swap(vn,un);
        flag=true;
    }
    uvlca=LCA(un,vn);
    if (uvlca==un || uvlca==vn)
    {
        if (flag) printf("%d\n",tree[un].depth-tree[uvlca].depth);
        else printf("%d\n",2*(tree[un].depth-tree[uvlca].depth));
    }
    else 
    {
        if (!flag) printf("%d\n",2*(tree[un].depth-tree[uvlca].depth)+(tree[vn].depth-tree[uvlca].depth));
        else printf("%d\n",2*(tree[vn].depth-tree[uvlca].depth)+(tree[un].depth-tree[uvlca].depth));
    }
    return 0;
}