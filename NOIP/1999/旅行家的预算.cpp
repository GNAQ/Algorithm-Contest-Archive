#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<queue>
#define ll long long
using namespace std;

int N;
double dis_t,C,dis_p,cost[10],dis[10];

struct _Node
{
    double rest,pric;
    bool operator < (const _Node& B) const { return pric>B.pric; }
};
priority_queue<_Node> que;

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

int main()
{
    scanf("%lf%lf%lf%lf%d",&dis_t,&C,&dis_p,&cost[0],&N);
    for (int i=1;i<=N;i++) { scanf("%lf%lf",&dis[i],&cost[i]); }
    
    N++; dis[N]=dis_t;
    for (int i=N;i>=1;i--) dis[i]-=dis[i-1];
    
    _Node tmp; tmp.rest=C; tmp.pric=cost[0];
    que.push(tmp);
    
    double ans=0;
    for (int i=1;i<=N;i++)
    {
        double now=dis[i];
        while (now)
        {
            if (que.empty()) { printf("No Solution\n"); return 0; }
            tmp=que.top(); que.pop();
            if (tmp.rest*dis_p>now)
            {
                tmp.rest-=now/dis_p;
                ans+=tmp.pric*(now/dis_p);
                now=0; que.push(tmp);
            }
            else
            {
                now-=tmp.rest*dis_p;
                ans+=tmp.pric*tmp.rest;
            }
        }
        tmp.rest=C; tmp.pric=cost[i]; que.push(tmp);
    }
    printf("%.2lf\n",ans);
    return 0;
}