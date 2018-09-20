// luogu-judger-enable-o2
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 10100
#define M 20100
#define P 60
#define TT 80
#define eps 1e-7
#define inf 0x3f3f3f3f
using namespace std;

struct Trie
{
    int next[N*20][TT],cnt;
    int note[N*20],sign;
    char s[TT];
    inline int insert()
    {
        scanf("%s",s+1);
        int x=0,i,alp;
        for(i=1;s[i];i++)
        {
            alp=s[i]-'0';
            if(!next[x][alp])next[x][alp]=++cnt;
            x=next[x][alp];
        }
        if(!note[x])note[x]=++sign;
        return note[x];
    }
    inline int judge()
    {
        for(int i=1;s[i];i++)if(i>=5&&s[i]=='t'&&s[i-1]=='r'&&s[i-2]=='a'&&s[i-3]=='t'&&s[i-4]=='s')return 1;
        for(int i=1;s[i];i++)if(i>=3&&s[i]=='s'&&s[i-1]=='a'&&s[i-2]=='g')return 2;
        for(int i=1;s[i];i++)if(i>=3&&s[i]=='d'&&s[i-1]=='n'&&s[i-2]=='e')return 3;
        return 0;
    }
}trie;
/*for original graph or prespfa or the gas_station graph. */
struct KSD
{
    int u,v,next;
    double len;
}e[M<<1],E[15][P*P<<1];
int head[N],cnt;
void add(int u,int v,double len)
{
    cnt++;
    e[cnt].u=u;
    e[cnt].v=v;
    e[cnt].len=len;
    e[cnt].next=head[u];
    head[u]=cnt;
}
int HEAD[15][P],CNT[15];
void ADD(int light,int u,int v,double len)
{/*i feel sick for my code here, but i can't do anything. */
    CNT[light]++;
    E[light][CNT[light]].u=u;
    E[light][CNT[light]].v=v;
    E[light][CNT[light]].len=len;
    E[light][CNT[light]].next=HEAD[light][u];
    HEAD[light][u]=CNT[light];
}
struct Lux
{
    int x,y;
    Lux(int _x,int _y):x(_x),y(_y){}
    Lux(){}
};
queue<Lux>q;
double dist[15][N];
bool in[15][N];
/*for static code*/
int n,m,lig,gas,cost;
/*for each point*/
bool red[N];
int sta[N];
double ave[N];
int gas_station[N],num;
/*for temp input*/
char ttt[TT];
 
void prespfa(int S)
{/*build the direct combinations between the gas_stations. */
    while(!q.empty())q.pop();
    memset(dist,0x7f,sizeof(dist));
    int i,v,temp;
    dist[0][S]=0;
    in[0][S]=1;
    q.push(Lux(0,S));
    while(!q.empty())
    {
        Lux U=q.front();q.pop();in[U.x][U.y]=0;
        for(i=head[U.y];i;i=e[i].next)
        {
            v=e[i].v;
            temp=U.x+red[v];
            if(temp<=lig&&dist[U.x][U.y]+e[i].len+ave[v]<=gas&&dist[temp][v]>dist[U.x][U.y]+e[i].len+ave[v])
            {
                dist[temp][v]=dist[U.x][U.y]+e[i].len+ave[v];
                if(!in[temp][v])in[temp][v]=1,q.push(Lux(temp,v));
            }
        }
    }
}
double divspfa(int S,int T)
{
    while(!q.empty())q.pop();
    memset(dist,0x7f,sizeof(dist));
    int i,j,v,temp;
    dist[0][S]=0;
    in[0][S]=1;
    q.push(Lux(0,S));
    while(!q.empty())
    {
        Lux U=q.front();q.pop();in[U.x][U.y]=0;
        for(j=0;j+U.x<=lig;j++)
        {
            for(i=HEAD[j][U.y];i;i=E[j][i].next)
            {
                v=E[j][i].v;
                if(dist[j+U.x][v]>dist[U.x][U.y]+E[j][i].len+cost)
                {
                    dist[j+U.x][v]=dist[U.x][U.y]+E[j][i].len+cost;
                    if(!in[j+U.x][v])in[j+U.x][v]=1,q.push(Lux(j+U.x,v));
                }
            }
        }
    }
    
    double ret=99999999999.999;
    for(i=0;i<=lig;i++)ret=min(ret,dist[i][T]);
    return ret;
}
 
void work()
{
    int i,j,k;
    double a,b,c;
    int ia,ib;
    int s,t,v;
    scanf("%d%d%d%d%d",&n,&m,&lig,&gas,&cost);
    for(i=1;i<=n;i++)
    {
        trie.insert();
        if(k=trie.judge())
        {
            sta[i]=++num;
            gas_station[num]=i;
            if(k==1)s=i;
            if(k==3)t=i;
        }
        scanf("%lf%lf",&a,&b);
        if(k==1||k==3)continue;
        if(a>eps)
            red[i]=1,ave[i]=a*a/2.0/(a+b);          
    }
    
    for(i=1;i<=m;i++)
    {
        ia=trie.insert();
        ib=trie.insert();
        scanf("%s",ttt);
        scanf("%lf",&c);
        add(ia,ib,c);
        add(ib,ia,c);
    }
 
    for(i=1;i<=num;i++)
    {
        prespfa(gas_station[i]);
        
        for(j=1;j<=num;j++)
        {
            v=gas_station[j];
            if(j!=i) for(k=0;k<=lig;k++) if(dist[k][v]<inf)
                ADD(k,i,j,dist[k][v]);
        }
    }
    printf("%.3lf\n",divspfa(sta[s],sta[t])-cost);
}
 
int main()
{
    work();
    return 0;
}