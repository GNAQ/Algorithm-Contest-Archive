#include<iostream>
#include<cstdio>
#define qwq register 
using namespace std;
double p[10001],f[2001][2001],dp[2001][2001][2];
int a[2001][2001],c[20001],d[20001];
inline double min(double a,double b){
    return a<b?a:b;
}
inline int  qread(){
    int  k = 0;
    char c;
    c = getchar();
    while(!isdigit(c))c = getchar();
    while(isdigit(c)){
        k = (k<<1)+(k<<3)+c-48;
        c = getchar();
    }
    return k ;
}
int main()
{
	freopen("dat.in","r",stdin);
	freopen("std.out","w",stdout);
	
    int n,m,v,e,a1,b1,c1;
    cin>>n>>m>>v>>e;
    for(qwq int i=1;i<=n;i++)c[i]=qread();
    for(qwq int i=1;i<=n;i++)d[i]=qread();
    for(qwq int i=1;i<=n;i++)cin>>p[i];

    for(qwq int i=1;i<=v;i++)
     for(qwq int j=1;j<i;j++)
      f[i][j]=f[j][i]=999999999;

    for(qwq int i=1;i<=e;i++){
        a1=qread(),b1=qread(),c1=qread();
        f[a1][b1]=f[b1][a1]=min(f[a1][b1],c1);
    }

    for(qwq int k=1;k<=v;k++)
      for(qwq int i=1;i<=v;i++)
        for(qwq int j=1;j<i;j++)
          if(f[i][k]+f[k][j]<f[i][j])
             f[i][j]=f[j][i]=f[i][k]+f[k][j];
			 
    for(qwq int i=1;i<=n;i++)
        for(qwq int j=0;j<=m;j++)
            dp[i][j][0]=dp[i][j][1]=999999999;

    dp[1][0][0]=dp[1][1][1]=0;
    for(qwq int i=2;i<=n;i++){
     double add1=f[c[i-1]][c[i]];
      for(qwq int j=0;j<=min(m,i);j++)
       {                     
          dp[i][j][0]=min(
			  			  dp[i-1][j][0]+add1,
		  				  dp[i-1][j][1]+f[d[i-1]][c[i]]*p[i-1]+f[c[i-1]][c[i]]*(1-p[i-1])
						 );
          if(j!=0)
          dp[i][j][1]=min(
			  			  dp[i-1][j-1][0]+f[c[i-1]][d[i]]*p[i]+f[c[i-1]][c[i]]*(1-p[i]),
						  dp[i-1][j-1][1]+f[c[i-1]][c[i]]*(1-p[i-1])*(1-p[i])
										 +f[c[i-1]][d[i]]*(1-p[i-1])*p[i]
										 +f[d[i-1]][c[i]]*(1-p[i])*p[i-1]
										 +f[d[i-1]][d[i]]*p[i-1]*p[i]
						 );
       }   
    }          

    double hahaha=9999999999;
    for(int i=0;i<=m;i++){
    hahaha=min(dp[n][i][0],min(dp[n][i][1],hahaha));}
    printf("%.2lf",hahaha);
}