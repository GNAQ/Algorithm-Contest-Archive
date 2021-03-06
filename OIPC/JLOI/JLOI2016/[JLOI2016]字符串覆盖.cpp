// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<set>
#include<map>
#define ll long long
using namespace std;


int _T,minans,maxans,n;
char chs[10010]={0},cht[5][1010]={0};
int le[5],pre[5][10010],nxt[5][10010],L;

//KMP Part
int fail[10010]={0};
bool mats[10010]={0};

//cache part
int cod[5]={0};
//ans part
int dp[10010][5],top;
bool vis[10010][5],*st[50010]; 

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void ClearAll()
{
    memset(chs,0,sizeof chs);
    memset(cht,0,sizeof cht);
    minans=1e9; maxans=n=top=0;
    memset(cod,0,sizeof cod);
    memset(fail,0,sizeof fail);
    memset(mats,0,sizeof mats);
    memset(le,0,sizeof le);
    memset(pre,0,sizeof pre);
    memset(nxt,0,sizeof nxt);
    memset(vis,0,sizeof vis);
    for (int i=1;i<=4;i++) { dp[0][i]=1e9; vis[0][i]=1; }
}

inline void Calc_Next(int len,char cr[])
{
    int su=0;
    for (int i=2;i<=len;i++)
    {
        while (su && cr[su+1]!=cr[i]) su=fail[su];
        if (cr[su+1]==cr[i]) su++;
        fail[i]=su;
    }
}

inline void ProcessKMP(int w,int a[],int b[])
{
    int su=0; memset(mats,0,sizeof mats);
    for (int i=1;i<=L;i++)
    {
        while (su && chs[i]!=cht[w][su+1]) su=fail[su];
        if (cht[w][su+1]==chs[i]) su++;
        if (su==le[w]) mats[i-su+1]=1;
    }
    for (int i=1;i<=L;i++) a[i]= mats[i]? i : a[i-1];
    a[L+1]=a[L]; b[L+1]=0;
    for (int i=L;i;i--)
    {
        if (mats[i]) b[i]=i;
        else b[i]=b[i+1];
    }
}

inline int DP1(int pos,int w)
{
    if (w>n) return 0;
    pos=nxt[cod[w]][pos];
    
    int& qwq=dp[pos][cod[w]];
    if (*(st[top+1]=&vis[pos][cod[w]])) return qwq;
    *st[++top]=1;
    
    qwq=DP1(pos+1,w);
    
    int end=pos+le[cod[w]],st=pos,tmp;
    while ((++w)<=n)
    {
        qwq=min(qwq, DP1(end,w)+(end-pos) );
        
        tmp=nxt[cod[w]][pos];
        if (tmp<st || tmp>=end) return qwq;
        end=max(end,tmp+le[cod[w]]); st=tmp;
    }
    qwq=min(qwq,end-pos);
    return qwq;
}

inline int DP2(int pos,int w)
{
    if (w>n) return 0;
    pos=nxt[cod[w]][pos];
    if (!pos) return -1e9;
    
    int end=pos+le[cod[w]],st=pos,qwq=-1e9,tmp;
    while ((++w)<=n)
    {
        qwq=max(qwq,DP2(end,w)+(end-pos));
        
        tmp=pre[cod[w]][end];
        if (tmp<st || tmp>=end) return qwq;
        end=max(end, tmp+le[cod[w]] ); st=tmp;
    }
    qwq=max(qwq, end-pos );
    return qwq;
}

int main()
{
    readx(_T);
    while (_T--)
    {
        ClearAll();
        scanf("%s",chs+1); L=strlen(chs+1);
        readx(n);
        for (int i=1;i<=n;i++)
        {
            scanf("%s",cht[i]+1); cod[i]=i;
            Calc_Next(le[i]=strlen(cht[i]+1),cht[i]);
            ProcessKMP(i,pre[i],nxt[i]);
        }
        do
        {
            minans=min(minans,DP1(1,1));
            for (;top;top--) *st[top]=0;
            maxans=max(maxans,DP2(1,1));
        } while (next_permutation(cod+1,cod+n+1));
        printf("%d %d\n",minans,maxans);
    }
    return 0;
}