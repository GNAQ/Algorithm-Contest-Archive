#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<bitset>
typedef long long ll;
using namespace std;

int n,m,pre,cnt;
int mseq[100010];

bitset<50001> dp[2],v1,v2,RC;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Out(bitset<50001>& tar)
{
	for (int i=1;i<=n;i++) printf("%d",tar.test(i));
	printf("\n");
}

int main()
{
	char inpfile[20];
	scanf("%s",inpfile);
	freopen(inpfile,"r",stdin);
	
	readx(n); readx(m); // m<=n
	for (int i=1;i<=m;i++) readx(mseq[i]);
	
	
	pre=1,cnt=0;
	for (int i=n;i>=1;i--)
	{
		v1=dp[pre]; v1.flip(); v1<<=i; v1.flip();
		
		v2=dp[pre]; v2.flip(); v2>>=(n-i); v2.flip();
		
		Out(v1); Out(v2);
		
		for (int j=1;j<=n;j++)
		{
			// if (i&1) dp[cnt][j]=(v1[j]&v2[j])^1; 
			// else dp[cnt][j]=(v1[j]^1)|(v2[j]^1);
			if (i&1) { dp[cnt]=v1&v2; dp[cnt].flip(); }
			else { v1.flip(); v2.flip(); dp[cnt]=v1|v2; }
		}
		
		Out(dp[cnt]);
		cout<<endl;
		
		swap(pre,cnt);
	}
	
	for (int i=1;i<=m;i++) printf("%d",dp[pre].test(mseq[i]));
	printf("\n");
}