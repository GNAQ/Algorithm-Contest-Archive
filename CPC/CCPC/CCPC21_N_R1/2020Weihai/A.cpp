#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int main()
{
	int T;cin>>T;
	while(T--)
	{
		LL n,x,t;
		scanf("%lld%lld%lld",&n,&x,&t);
		LL tmp1=max(x+2*t,2*n*t)+2*n*t;
		tmp1=min(tmp1,max(x+t,2*n*t+t)+2*n*t);
		printf("%lld\n",tmp1);
	}
}