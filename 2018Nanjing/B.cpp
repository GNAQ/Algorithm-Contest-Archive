#include<bits/stdc++.h>

using namespace std;

int sec[300010];
int n,k;

bool check(double dis)
{
	double nowl=sec[0];
	int nowptr=0;
	int cnt=0;
	while(nowptr<=n)
	{
		cnt++;
		double nowr=nowl+dis;
		while(nowptr<=n&&sec[nowptr]<=nowr) nowptr++;
		nowl=sec[nowptr];
	}
	return cnt<=k;
}

int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>sec[i];
	double nl=0,nr=20;
	while(nr-nl>1e-2)
	{
		double mid=(nl+nr)/2;
		if(check(mid)) nr=mid;
		else nl=mid; 
	}	
	cout<<floor(nl)<<'\n';
}