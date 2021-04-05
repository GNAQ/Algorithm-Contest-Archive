#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e6+100;
int gcd(int a,int b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}
int dat[maxn];
int main()
{
	int T;cin>>T;
	while(T--)
	{
		int n;cin>>n;
		for(int i=1;i<=n;i++)
			scanf("%d",&dat[i]);
		int g=dat[1];
		for(int i=2;i<=n;i++)
			if(g>dat[i]) g=gcd(g,dat[i]);
			else g=gcd(dat[i],g);
		int cnt=0;
		for(int i=1;i<=n;i++)
			if(dat[i]==g) cnt++;
		if(!cnt) printf("1\n");
		else if(cnt&1) printf("%d\n",cnt/2+1);
		else printf("%d\n",cnt/2);
	}
}