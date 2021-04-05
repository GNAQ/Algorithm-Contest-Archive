#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int MAXN=4e5+100;
const double eps=1e-8;
template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
double dat[110];
int main()
{
	double e=exp(1.0);
	int T;cin>>T;
	while(T--)
	{
		int n;char ch[10];double d,ans=0;
		scanf("%d%s",&n,ch);
		if(ch[0]=='b') d=2.0;
		if(ch[0]=='n') d=e;
		if(ch[0]=='d') d=10.0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf",&dat[i]);
			dat[i]/=100;
			if(dat[i]<=eps)
				continue;
			ans-=dat[i]*(log(dat[i])/log(d));
		}
		printf("%.12lf\n",ans);
	}
}