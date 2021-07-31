#include<bits/stdc++.h>

using namespace std;

__int128 INF = 1e18;

__int128 p[20],q[20];
__int128 a,b;
int n;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

__int128 nowq[20];
__int128 nowA;

__int128 ansA=0x7fffffffffffffff,ansB=0x7fffffffffffffff;

void dfsB(__int128 now,int pos)
{
    if(nowA+now>=ansA+ansB) return;
    if(pos>n)
    {
        if(now<b) return;
        if(nowA+now<ansA+ansB)
        {
            ansA=nowA;
            ansB=now;
        }
        return;
    }

    if(nowq[pos]!=q[pos])
    {
        __int128 tmp=1;
        for(int i=1;i<=q[pos];i++) tmp*=p[pos];
        dfsB(now*tmp,pos+1);
    }
    else
    {
        __int128 tmp=1;
        for(int i=0;i<=q[pos];i++) 
        {   
            dfsB(now*tmp,pos+1);
            tmp*=p[pos];
        }
    }
}

void dfsA(__int128 now,int pos)
{
    if(pos>n)
    {  
        if(now<a) return;
        nowA=now;
        dfsB(1,1);
        return;
    }
    __int128 tmppow=1;
    for(int i=0;i<=q[pos];i++)
    {
        nowq[pos]=i;
        dfsA(now*tmppow,pos+1);
        nowq[pos]=0;
        tmppow*=p[pos];
    }
}

void print(__int128 x)
{
    if(!x) return;
    print(x/10);
    cout<<((int)(x%10));
}

int main()
{
    INF*=INF;
    ansA=INF,ansB=INF;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        readx(p[i]);
        readx(q[i]);
    }
    readx(a);readx(b);
    dfsA(1,1);
    __int128 ans=ansA+ansB-a-b;
    if (ans==0)
    {
        puts("0");
    }
    else
    {
        print(ans);
        cout<<'\n';
    }
}
