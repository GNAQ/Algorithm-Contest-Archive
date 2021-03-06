#include<cstdio>
#include<cstring>
using namespace std;

int n;
double stime,atime,scost,acost,gcost,incost;
double need[103]={0},tim[103]={0},dp[103][103]={0};

short pre[103][103]={0},go[103][103]={0};


inline void output(int a,int b)
{
    if (pre[a][b])
    {
        output(pre[a][b],a-pre[a][b]);
        printf("%d %.3lf\n",a-1,need[b]);
    }
}
inline double getprimery(int a,int b)
{
    if (pre[a][b]==1) return need[a-pre[a][b]];
    return getprimery(pre[a][b],a-pre[a][b]);
}

int main()
{
    memset(dp,0x43,sizeof dp);
    scanf("%d%lf%lf%lf%lf%lf%lf",&n,&stime,&atime,&scost,&acost,&incost,&gcost);
    
    for (int i=1;i<=n+1;i++) need[i]=need[i-1] + ((need[i-1]*acost+scost)/(1-acost));
    for (int i=1;i<=n+1;i++) tim[i]= tim[i-1] + stime+need[i]*atime;
    for (int i=0;i<=n;i++) dp[1][i]=tim[i];
    
    register double cac=0;
    for (int i=2;i<=n+1;i++)
        for (int j=1;j<=n+1;j++)
            for (int k=1;k<=n+1;k++)
            {
                if (i-k<1) break;
                cac=dp[i-k][k]+tim[j]+incost+gcost*need[j];
                
                if (cac<dp[i][j])
                {
                    dp[i][j]=cac;
                    
                    pre[i][j]=i-k;
                    go[i][j]=go[i-k][k]+1;
                }
            }
    
    register int pos=n; register double start;
    for (int i=n;i;i--) if (dp[i][n+1-i]<dp[pos][n+1-pos]) pos=i;
    if (pos==1) start=need[n];
    else start=getprimery(pos,n+1-pos);
    
//	cout<<"!! pos= "<<pos<<endl<<endl;
    
    printf("%.3lf %.3lf %d\n",dp[pos][n+1-pos],start,go[pos][n+1-pos]);
    output(pos,n+1-pos);
    return 0;
}