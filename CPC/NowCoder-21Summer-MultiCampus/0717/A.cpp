#include<bits/stdc++.h>
typedef long long ll;
using namespace std;


const int MAXN=5e3+100;
template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int dp[MAXN][MAXN],vis[MAXN][MAXN];

int main()
{	
	for(int i=0;i<=5e3;i++)
		for(int j=0;j<=5e3;j++)
			if(!vis[i][j])
			{
				for(int l=1;l+j<=5e3;l++)
					vis[i][l+j]=1;
				for(int l=1;i+l<=5e3;l++)
					vis[i+l][j]=1;
				for(int k=1;k<=5e3;k++)
					for(int l=1;(i+l<=5e3)&&(j+k*l<=5e3);l++)	
						vis[i+l][j+k*l]=1;
				for(int k=1;k<=5e3;k++)
					for(int l=1;(j+l<=5e3)&&(i+k*l<=5e3);l++)	
						vis[i+k*l][j+l]=1;
				
				if (i<=j) printf("%d,%d\n", i, j);
			}
	/*int T;cin>>T;
	while(T--)
	{
		int a,b;scanf("%d%d",&a,&b);
		if(!vis[a][b]) printf("Bob\n");
		else printf("Alice\n");
 	}*/
}
