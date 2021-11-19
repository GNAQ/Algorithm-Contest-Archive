#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
const int maxn=3e5+100;
LL val[maxn],cnt[maxn],sum[maxn],last[maxn],pos[maxn],dat[maxn];
int main()
{
	int n,w;
	cin>>n>>w;
	for(int i=1;i<=n;i++)
		pos[i]=0;
	for(int i=1;i<=w;i++)
	{
		int S;scanf("%d",&S);
		for(int j=1;j<=S;j++)
		{
			int tmp,p;
			scanf("%d",&tmp);
			p=pos[tmp];dat[j]=tmp;
			sum[p]+=cnt[p]*(i-1-last[p]);
			last[p]=i-1;
			LL tag=val[tmp]+sum[p];
			
			sum[p+1]+=(cnt[p+1])*(i-1-last[p+1]);
			last[p+1]=i-1;
			val[tmp]=tag-sum[p+1];
			pos[tmp]=p+1;
			// cout<<"!!!"<<p<<" "<<tmp<<" "<<dat[j]<<" "<<pos[dat[j]]<<" "<<sum[p]<<endl;
		}
		for(int j=1;j<=S;j++)
			cnt[pos[dat[j]]-1]++;
		// for(int j=1;j<=S;j++)
		// 	printf("%d %d %d %d|",(i-last[pos[dat[j]]])*cnt[pos[dat[j]]]+val[dat[j]],(i-last[pos[dat[j]]]),cnt[pos[dat[j]]],val[dat[j]]);
		// cout<<endl;
	}
	for(int i=1;i<=n;i++)
	{
		sum[pos[i]]+=cnt[pos[i]]*(w-last[pos[i]]);last[pos[i]]=w;
		printf("%.10lf\n",1.0*(sum[pos[i]]+val[i]+w)/w);
	}
}