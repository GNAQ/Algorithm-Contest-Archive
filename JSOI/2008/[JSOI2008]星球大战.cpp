#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<utility>
using namespace std;

struct ed
{
    int pre,to;
}edge[1000010]={0};
int pointer[500010]={0},edgenum,nodenum,fx,tx,prex,anum,c1=0,ufsnum;
int fatherx[500010]={0},attack[500010]={0};
int ans[500010]={0},heada=0;
bool able[500010]={0};

void Insert()
{
    edge[++c1].pre=pointer[fx];
    edge[c1].to=tx;
    pointer[fx]=c1;
    edge[++c1].pre=pointer[tx];
    edge[c1].to=fx;
    pointer[tx]=c1;
}

int findx(int e)
{
    if (e!=fatherx[e]) fatherx[e]=findx(fatherx[e]);
    return fatherx[e];
}

void mergex(int e1,int e2)
{
    fatherx[findx(e1)]=fatherx[findx(e2)];
}

int main()
{
    scanf("%d%d",&nodenum,&edgenum);				//!!!! 0 ¡ªN-1
    for (int i=1;i<=edgenum;i++)
    {
        scanf("%d%d",&fx,&tx);
        Insert();
    }
    scanf("%d",&anum);
    fill(able,able+nodenum,true);
    for (int i=0;i<nodenum;i++) fatherx[i]=i;
    ufsnum=nodenum-anum;
    for (int i=1;i<=anum;i++) 
    {
        scanf("%d",&attack[i]);
        able[attack[i]]=false;
    }
    
    for (int i=0;i<nodenum;i++) if (able[i])
    {
        prex=pointer[i];
        while (prex)
        {
            if (able[edge[prex].to] && (findx(i)!=findx(edge[prex].to)))
            {	
//				printf("Merged %d & %d\n",i,edge[prex].to);
                mergex(i,edge[prex].to);
                ufsnum--;
            }
            prex=edge[prex].pre;
        }
    }
    ans[heada++]=ufsnum;
    
    for (int i=anum;i>=1;i--)
    {
        ufsnum++;
        able[attack[i]]=true;
        prex=pointer[attack[i]];
        while(prex)
        {
            if (able[edge[prex].to] && (findx(attack[i])!=findx(edge[prex].to)))
            {
//				printf("Merged %d & %d\n",attack[i],edge[prex].to);
                mergex(attack[i],edge[prex].to);
                ufsnum--;
            }
            prex=edge[prex].pre;
        }
        ans[heada++]=ufsnum;
    }
    for (int i=heada-1;i>=0;i--) printf("%d\n",ans[i]);
    return 0;
}
