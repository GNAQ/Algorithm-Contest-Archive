#include<iostream>
#include<cstdio>
#include<unordered_map>
using namespace std;
const int MAXN=2100;
int dat[MAXN];
unordered_map<int,int>mp;
int main()
{
	int T;cin>>T;
	while(T--)
	{
		int n;cin>>n;
		long long ans=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&dat[i]);
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
				ans+=mp[dat[i]*2-dat[j]];
			mp[dat[i]]++;
		}
		cout<<ans<<'\n';
		mp.clear();
	}
}
