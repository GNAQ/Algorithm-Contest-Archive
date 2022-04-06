#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=1e6+100;
LL sum[5][5][2],ans,dat[MAXN];
int main()
{
	int n,opt=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&dat[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=2;j++)//ans
			for(int k=0;k<=2;k++)//sum
			{
				sum[(j+dat[i]*k)%3][(k+dat[i])%3][opt]=sum[j][k][opt^1];
//				if(j==0&&k==2) cout<<"??"<<(j+dat[i]*k)%3<<" "<<(k+dat[j])%3<<" "<<dat[j]<<" "<<sum[j][k][opt^1]<<endl;
			}
//		cout<<sum[1][2][opt]<<endl;
		sum[0][dat[i]%3][opt]++;
		for(int j=0;j<=2;j++)
			ans+=sum[0][j][opt];
//		for(int j=0;j<=2;j++)
//		{
//			for(int k=0;k<=2;k++)
//				cout<<sum[j][k][opt]<<" ";
//			cout<<endl;
//		}
//		cout<<endl;
		opt^=1;
	}
	printf("%lld\n",ans);
}