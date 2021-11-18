#include<bits/stdc++.h>

using namespace std;

const int mod=1e9+7;

int sec[100010];
int sum[100010];
int num[100010][23];

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,Q;
		cin>>n>>Q;
		for(int i=1;i<=n;i++) cin>>sec[i];
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]^sec[i];
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=22;j++)
			{
				num[i][j]=num[i-1][j]+((sum[i]>>j)&1);
			}
		}
		while(Q--)
		{
			int l,r;
			cin>>l>>r;
			int ans=0;
			for(int j=0;j<=22;j++)
			{
				int nu=num[r][j]-num[max(0,l-2)][j];
				ans+=1ll*nu*(r-l+2-nu)%mod*(1<<j)%mod;
				ans%=mod;
			}
			cout<<ans<<'\n';
		}
	}	
}