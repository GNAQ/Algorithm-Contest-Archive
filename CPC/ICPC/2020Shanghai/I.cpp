#include<bits/stdc++.h>
 
using namespace std;
 
 
const double pi=acos(-1);
 
double dis[2010][2010];
 
int cal(int j)
{
	return (j*(j+1)*(2*j+1)/6-j*(j+1)/2)/2;
}
 
int main()
{
	int n,m;
	cin>>n>>m;
	double rad=pi/m;
	m*=2;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			int d=abs(i-j);
			double drad=rad*d;
			drad=min(drad,2*pi-drad);
			dis[i][j]=min(drad,2.0);
		}
	}
	double ans=0;
	for(int i=0;i<m;i++)
	{
		for(int k=0;k<m;k++)
		{
			ans+=dis[i][k]*cal(n);
			ans+=dis[i][k]*(n*(n+1)*n/2-cal(n)*2);
			ans+=cal(n)*2;
		}
	}
	if(m!=2) ans+=m*(n+1)*n;
	ans/=2;
	cout<<fixed<<setprecision(8);
	cout<<ans<<'\n';
}