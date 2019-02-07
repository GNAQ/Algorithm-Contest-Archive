//Trie graph
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>
#include<iterator>
#include<vector>
#include<map>
#include<set>
#define ll long long
#define PAUSE system("pause")
using namespace std;

struct ACAutomaton
{
    int fail,ch[26],val;
    ACAutomaton()
    {
        memset(ch,0,sizeof ch);
        val=fail=0;
    }
}AC[1000010];
int n=0,tsiz=0;
char chs[1000010]={0};

queue<int> que;

inline void readx(int& x)
{
    x=0; int k=1; register char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

inline void Insert(char wd[])
{
    register int pos=0,len=strlen(wd+1);
    for (int i=1;i<=len;i++)
    {
        if (!AC[pos].ch[wd[i]-'a']) AC[pos].ch[wd[i]-'a']=++tsiz;
        pos=AC[pos].ch[wd[i]-'a'];
    }
    AC[pos].val++;
}

inline void GetFail()//Build Trie Graph
{
    register int cac;
    for (int i=0;i<26;i++) if (AC[0].ch[i]) que.push(AC[0].ch[i]);
    
    while (!que.empty())
    {
        cac=que.front(); que.pop();
        for (int i=0;i<26;i++)
        {
            if (AC[cac].ch[i])
            {
                AC[AC[cac].ch[i]].fail=AC[AC[cac].fail].ch[i];
                que.push(AC[cac].ch[i]);
            }
            else AC[cac].ch[i]=AC[AC[cac].fail].ch[i];
        }
    }
}

inline int query(char wd[])
{
    register int len=strlen(wd+1),pos=0,ans=0;
    for (int i=1;i<=len;i++)
    {
        while (AC[pos].ch[wd[i]-'a']==0) pos=AC[pos].fail;
        for (int t=pos;t && AC[t].val!=-1;t=AC[t].fail)
        {
            ans+=AC[t].val;
            AC[t].val=-1;
        }
    }
    return ans;
}

int main()
{
    readx(n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",chs+1);
        Insert(chs);
    }
    AC[0].fail=0;
    GetFail();
    scanf("%s",chs+1);
    printf("%d\n",query(chs));
    PAUSE;
    return 0;
}