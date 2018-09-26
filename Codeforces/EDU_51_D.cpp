#include<cstdio>
#include<cstring>
#define ll long long
#define mod 998244353
using namespace std;

int N,K;
int dp[1010][2010][4];

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int sta_s[4][4]={0};
void _Init()
{
	sta_s[0][0]=0; sta_s[0][2]=1;
	sta_s[0][1]=1; sta_s[0][3]=1;
	
	sta_s[1][0]=0; sta_s[1][1]=0;
	sta_s[1][2]=2; sta_s[1][3]=0;
	
	sta_s[2][0]=0; sta_s[2][1]=2;
	sta_s[2][2]=0; sta_s[2][3]=0;
	
	sta_s[3][0]=1; sta_s[3][1]=1;
	sta_s[3][2]=1; sta_s[3][3]=0;
}

int main()
{
	readx(N); readx(K); _Init();
	
	dp[1][1][0]=1; dp[1][2][1]=1; dp[1][2][2]=1; dp[1][1][3]=1;
	
	for (int i=2;i<=N;i++)
		for (int j=0;j<=2*(i-1);j++)
			for (int w=0;w<=3;w++)
				for (int o=0;o<=3;o++)
					dp[i][j+sta_s[o][w]][w]=(dp[i][j+sta_s[o][w]][w]+dp[i-1][j][o])%mod;
	
	int ans=0;
	for (int w=0;w<=3;w++) ans=(ans+dp[N][K][w])%mod;
	printf("%d\n",ans);
}
