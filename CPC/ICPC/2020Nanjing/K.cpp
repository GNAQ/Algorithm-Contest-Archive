#include<bits/stdc++.h>

using namespace std;

int sec[1000010];

int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) sec[i]=i;
	if(k==0) return cout<<-1<<'\n',0;
	if(k&1)
	{
		k/=2;
		for(int i=1;i<=k;i++)
		{
			swap(sec[i*2],sec[i*2+1]);
		}
	}
	else
	{
		k/=2;
		for(int i=1;i<=k;i++)
		{
			swap(sec[i*2-1],sec[i*2]);
		}	
	}
	for(int i=1;i<=n;i++) cout<<sec[i]<<' ';
	cout<<'\n';
}