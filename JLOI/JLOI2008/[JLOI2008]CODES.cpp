#include<cstdio>
#include<string>
#include<cstring>
using namespace std;

char wd[21][21]={0};
int n=0,len[21]={0},dp[21][21]={0};
char answ[21][21][155]={0};

int vis[21][21][2]={0};

inline bool judgex(int a,int b,int pa,int pb,int l)
{
    for (int i=1;i<=l;i++) if (wd[a][pa+i-1]!=wd[b][pb+i-1]) return false;
    return true;
}
inline bool lex(int a,int b,int c,int d,int l)
{
    for (int i=1;i<=l;i++) if (answ[a][b][i]!=answ[c][d][i]) 
        return (answ[a][b][i]>answ[c][d][i]);
}
inline int minx(int now,int pos,int val,int p,int q)
{
    if (val>2*1e9) return min(dp[now][pos],val);
    if ((dp[pos][now]==val && lex(now,pos,p,q,dp[p][q])) || dp[now][pos]>val) 
    {
        for (int i=1;i<=dp[p][q];i++) answ[now][pos][i]=answ[p][q][i];
        for (int i=dp[p][q]+1;i<=val;i++) answ[now][pos][i]=wd[p][q+i-dp[p][q]];
    }
    return min(dp[now][pos],val);
}

inline int _dp(int now,int pos,int sgn)
{
    if (dp[now][pos]!=2*1e9) return dp[now][pos];
    for (int i=1;i<=n;i++) if (now!=i || pos!=len[i])
    {
        if (len[i]<=pos && !vis[now][pos-len[i]][sgn] && judgex(now,i,pos-len[i]+1,1,len[i]))
        {
            vis[now][pos-len[i]][sgn]=1;
            dp[now][pos]=minx(now,pos,_dp(now,pos-len[i],sgn)+len[i],now,pos-len[i]);
            vis[now][pos-len[i]][sgn]=0;
        }
        if (len[i]>pos && !vis[i][len[i]-pos][sgn^1] && judgex(now,i,1,len[i]-pos+1,pos))
        {
            vis[i][len[i]-pos][sgn^1]=1;
            dp[now][pos]=minx(now,pos,_dp(i,len[i]-pos,sgn^1)+pos,i,len[i]-pos);
            vis[i][len[i]-pos][sgn^1]=0;
        }
    }
    return dp[now][pos];
}

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%s",wd[i]+1),len[i]=strlen(wd[i]+1);
    for (int i=1;i<=20;i++) for (int j=1;j<=20;j++) dp[i][j]=2*1e9;
    int ans=2*1e9,p;
    for (int i=1;i<=n;i++)
    {
        vis[i][len[i]][0]=1;
        if (_dp(i,len[i],0)<ans) { ans=dp[i][len[i]]; p=i; }
        else if (ans!=2*1e9 && _dp(i,len[i],0)==ans && lex(p,len[p],i,len[i],ans)) p=i;
        vis[i][len[i]][0]=0;
    }
    printf("%d\n",ans);
    for (int i=1;i<=ans;i++) printf("%c",answ[p][len[p]][i]); printf("\n");
    return 0;
}