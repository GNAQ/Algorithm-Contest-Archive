#include<cstdio>
#include<iostream>
#include<string>
#include<queue>
using namespace std;

int mapc[200]={0};
struct ACAutomaton
{
    int ch[23],val,fail;
}AC[1000010];
int tsiz=0,n,m,K;

bool show[2010]={0};
string name[2010];
queue<int> que;

inline void init()
{
    int cnt=0;
    mapc['x']=cnt;
    for (int i=1;i<=8;i++) mapc['a'+i-1]=++cnt;
    for (int i=1;i<=8;i++) mapc['1'+i-1]=++cnt;
    mapc['K']=++cnt; mapc['Q']=++cnt; mapc['B']=++cnt; mapc['N']=++cnt; mapc['R']=++cnt; mapc['P']=++cnt;
}

inline void Insert(string wd,int cod)
{
    int len=wd.length(),pos=0;
    for (int i=0;i<len;i++)
    {
        if (!AC[pos].ch[mapc[wd[i]]]) AC[pos].ch[mapc[wd[i]]]=++tsiz;
        pos=AC[pos].ch[mapc[wd[i]]];
    }
    AC[pos].val=cod;
}

inline void GetFail()
{
    int cac=0,cac2=0;
    for (int i=0;i<=22;i++) if (AC[0].ch[i]) que.push(AC[0].ch[i]);
    
    while (!que.empty())
    {
        cac=que.front(); que.pop(); 
        for (int i=0;i<=22;i++)
        {
            cac2=AC[cac].ch[i];
            if (cac2)
            {
                AC[cac2].fail=AC[AC[cac].fail].ch[i];
                que.push(cac2);
            }
            else AC[cac].ch[i]=AC[AC[cac].fail].ch[i];
        }
    }
}

inline void query(string wd)
{
    int len=wd.length(),pos=0;
    for (int i=0;i<len;i++)
    {
        pos=AC[pos].ch[mapc[wd[i]]];
        for (int t=pos;t;t=AC[t].fail) show[AC[t].val]=true;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    cin>>n>>m; string chs,w;
    for (int i=1;i<=n;i++)
    {
        cin>>K; string chs1; //getchar();
        getline(cin,name[i]); getline(cin,name[i]);
        for (int j=1;j<=K;j++) 
        {
            getline(cin,w);
            chs1+=w;
        }
        Insert(chs1,i);
    }
    GetFail();
    for (int i=1;i<=m;i++)
    {
        getline(cin,w);
        chs+=w;
    }
    query(chs);
    
    for (int i=1;i<=n;i++) if (show[i]) cout<<name[i]<<endl;
    return 0;
}