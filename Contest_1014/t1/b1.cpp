#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#define ll long long
#define fst first
#define snd second
using namespace std;

int n,m,K;
pair<int,int> pnt[100010];
const ll mod=1000000007;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll dp[110][110][10010];
bool mapx[110][110];
void Solve1()
{
	for (int i=1;i<=K;i++) mapx[pnt[i].fst][pnt[i].snd]=1;
	
	dp[1][1][0]=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			for (int k=0;k<=K;k++)
			{
				if (mapx[i][j])
				{
					dp[i][j][k]+=(dp[i-1][j][k-1]+dp[i][j-1][k-1])%mod;
				}
				else dp[i][j][k]+=(dp[i-1][j][k]+dp[i][j-1][k])%mod;
			}
		}
	}
	cout<<dp[n][m][K]%mod<<endl;
}

int main()
{
	freopen("t1.in","r",stdin);
	freopen("b1.out","w",stdout);
	
	readx(n); readx(m); readx(K);
	for (int i=1;i<=K;i++)
	{
		readx(pnt[i].fst);
		readx(pnt[i].snd);
	}
	
	Solve1();
	// system("pause");
	return 0;
}