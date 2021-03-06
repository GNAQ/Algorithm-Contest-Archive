// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<string>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

int T,N,pw[55];
double P;
struct node
{
    double k,b; 
    node(double _x=0,double _y=0) { k=_x; b=_y; }
};

inline node DP(int t,int low)
{
    if (t>T) return node(0,0);
    double _k=0.0,_b=0.0; node cac;
    for (int i=1;i<=low;i++)
    {
        cac=DP(t+pw[i],i);
        _k+=cac.k; _b+=cac.b;
    }
    double p=(!t)? 0:P,A=(1.0-p)*(1.0/low);
    return node(p/(1-A*_k),(1+A*_b)/(1-A*_k)); 
}

int main()
{
    while (scanf("%lf%d%d",&P,&T,&N)!=EOF)
    {
        for (int i=1;i<=N;i++) scanf("%d",&pw[i]);
        sort(pw+1,pw+N+1);
        printf("%.3lf\n",DP(0,N).b);	
    }
}