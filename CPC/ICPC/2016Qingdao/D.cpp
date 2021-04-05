#include <bits/stdc++.h>
using namespace std;
const int maxn=20;
int a[maxn],n;
double p[maxn];
double die[maxn][110],live[maxn][110];
int main()
{
    int T,cas=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%lf",&a[i],&p[i]);
        }
        if(n==1) {puts("1.000000");continue;}
        for(int i=1;i<=n;i++)
        for(int k=0;k<=100;k++)
        {
            die[i][k]=pow(1.0-pow(p[i],k),a[i]);
            live[i][k]=1.0-die[i][k];
        }
        for(int i=1;i<=n;i++)
        {
            double ans=0;
            for(int k=1;k<=100;k++)
            {
                double tmp=1;
                for(int j=1;j<=n;j++)
                if(j!=i)tmp*=die[j][k];
                ans+=(live[i][k]-live[i][k+1])*tmp;
            }
            printf("%.6lf%c",ans,i==n?'\n':' ');
        }
    }
    return 0;
}
