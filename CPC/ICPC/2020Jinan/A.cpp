#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN=220;
const int mod=998244353;
int n,a[MAXN][MAXN],b[MAXN][MAXN],data[MAXN][MAXN],tmp[MAXN],ans,res=1,base[MAXN];
void add(int x,int y)
{
	for(int i=1;i<=n;i++)
	{
		if(i==x) tmp[i]=a[x][i]^b[x][y];
		else tmp[i]=a[x][i];
	}
	for(int i=1;i<=n;i++)
		cout<<tmp[i];
	cout<<endl;
	for(int i=1;i<=n;i++)
	{
		if(!tmp[i]) continue;
		if(!data[i][i])
		{
			ans++;
			for(int j=i;j<=n;j++)
				data[i][j]=tmp[j];
			break;
		}
		else for(int j=i;j<=n;j++)
				tmp[j]^=data[i][j];
	}
}
int main()
{
	cin>>n;base[0]=1;
	for(int i=1;i<=n;i++)
		base[i]=(base[i-1]*2)%mod;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&b[i][j]);
	for(int i=1;i<=n;i++)
	{
		ans=0;
		memset(data,0,sizeof data);
		for(int j=1;j<=n;j++) add(j,i);
		res*=base[n-ans];
		res%=mod;
	}
	cout<<res;
}
