#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=1e7+100;
int b[MAXN],n,vis[MAXN],data[MAXN],ans[MAXN],res;
template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
inline int Max(int x,int y)
{
	return x>y?x:y;
}
int main()
{
	cin>>n;int maxn=0;
	for(int i=1;i<=n;i++)
	{
		readx(data[i]);
		b[data[i]]++;
		maxn=Max(maxn,data[i]);
	}
	sort(data+1,data+n+1);
	for(int i=n;i>=1;i--)
	{
		if(vis[data[i]]) continue;
		vis[data[i]]=1;
		ans[data[i]]+=b[data[i]];
		int plus=0;
		for(int j=2;j*data[i]<=maxn;j++)
			plus=Max(plus,ans[j*data[i]]);
		ans[data[i]]+=plus;
		res=Max(res,ans[data[i]]);
	}
	cout<<res;
}