#include<bits/stdc++.h>

using namespace std;

int sec[1010];

int main()
{
	int n;
	cin>>n;
	int ans=0,cnt=0;
	for(int i=1;i<=n;i++) cin>>sec[i];
	for(int i=1;i<=n;i++)
	{
		int maxx=0,pos=0;
		for(int j=i;j<=n;j++)
		{
			if(maxx<sec[j])
			{
				maxx=sec[j];
				pos=j;
			}
		}
		if(i==pos) continue;
		cnt++;
		for(int j=pos;j>=i+1;j--)
		{
			swap(sec[j],sec[j-1]);
		}
		ans+=pos+i;
	}
}