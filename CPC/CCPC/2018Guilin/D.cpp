#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
const int MAXN=100;
int dat[MAXN],tag[MAXN],tag_pos[MAXN][2],org_pos[MAXN][2],cnt,cnt1,ans0,ans1;
int ABS(int x)
{
	if(x<0) x=-x;
	return x;
}
int main()
{
	int T;cin>>T;
	for(int ii=1;ii<=T;ii++)
	{
		LL a,b;int ans=0;
		cnt=cnt1=0;ans0=ans1=0;
		scanf("%lld%lld",&a,&b);
		for(int i=0;i<=60;i++)
		{
			if((1ll<<i)&a)
			{
				dat[i]=1;
				if(i&1) org_pos[++ans0][0]=i;
				else org_pos[++ans1][1]=i;;
			}
			else dat[i]=0;
			if((1ll<<i)&b)
			{
				tag[i]=1;
				if(i&1)
					tag_pos[++cnt][0]=i;
				else tag_pos[++cnt1][1]=i;
			}
			else tag[i]=0;
		}
		if(ans0!=cnt||ans1!=cnt1)
			ans=-1;
		else {
			for(int i=1;i<=ans0;i++)
				ans+=ABS(org_pos[i][0]-tag_pos[i][0])/2;
			for(int i=1;i<=ans1;i++)
				ans+=ABS(org_pos[i][1]-tag_pos[i][1])/2;
		}
		printf("Case %d: %d\n",ii,ans);
	}
}