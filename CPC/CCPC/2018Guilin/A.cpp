#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
const LL MAXN=1e5+100;
LL a[MAXN],b[MAXN],tota,totb;
struct node{
	LL sum;
	LL cnt;
	LL l;
	LL r;
	double average;
}ansa[MAXN],ansb[MAXN],tmp;
int main()
{
	LL T;cin>>T;
	for(LL ii=1;ii<=T;ii++)
	{
		LL n,m;cin>>n>>m;
		long long ans=0;
		tota=totb=0;
		a[0]=b[0]=1e9;tmp.l=0;
		tmp.sum=tmp.cnt=0;
		for(LL i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			if(a[i]>=a[i-1])
			{
				tmp.sum+=a[i];
				tmp.cnt++;
				tmp.average=1.0*tmp.sum/tmp.cnt;
			}
			else {
				while(tota&&tmp.average>ansa[tota].average)
				{
					tmp.cnt+=ansa[tota].cnt;
					tmp.sum+=ansa[tota].sum;
					tmp.l=ansa[tota].l;
					tmp.average=1.0*tmp.sum/tmp.cnt;
					tota--;
				}
				tmp.r=i-1;
				if(tmp.l!=0)
					ansa[++tota]=tmp;
				tmp.sum=a[i];
				tmp.cnt=1;
				tmp.l=i;
				tmp.average=a[i];
			}
		}
		tmp.r=n;
		while(tota&&tmp.average>ansa[tota].average)
		{
			tmp.cnt+=ansa[tota].cnt;
			tmp.sum+=ansa[tota].sum;
			tmp.l=ansa[tota].l;
			tmp.average=1.0*tmp.sum/tmp.cnt;
			tota--;
		}
		ansa[++tota]=tmp;
		tmp.l=0;
		tmp.sum=tmp.cnt=0;
		for(LL i=1;i<=m;i++)
		{
			scanf("%lld",&b[i]);
			if(b[i]>=b[i-1])
			{
				tmp.sum+=b[i];
				tmp.cnt++;
				tmp.average=1.0*tmp.sum/tmp.cnt;
			}
			else {
				while(totb&&tmp.average>ansb[totb].average)
				{
					tmp.cnt+=ansb[totb].cnt;
					tmp.sum+=ansb[totb].sum;
					tmp.l=ansb[totb].l;
					tmp.average=1.0*tmp.sum/tmp.cnt;
					totb--;
				}
				tmp.r=i-1;
				//cout<<"!!!!"<<ansb[totb].average<<" "<<tmp.average<<endl;
				if(tmp.l!=0)
					ansb[++totb]=tmp;
				tmp.sum=b[i];
				tmp.cnt=1;
				tmp.l=i;
				tmp.average=b[i];
			}
		}
		tmp.r=m;	
		while(totb&&tmp.average>ansb[totb].average)
		{
			tmp.cnt+=ansb[totb].cnt;
			tmp.sum+=ansb[totb].sum;
			tmp.l=ansb[totb].l;
			tmp.average=1.0*tmp.sum/tmp.cnt;
			totb--;
		}
		ansb[++totb]=tmp;
		LL tot_pos=0,now_tota=1,now_totb=1;
		while(now_tota<=tota&&now_totb<=totb)
		{
			//cout<<"!!!"<<average[pos1][0]<<" "<<average[pos2][1]<<endl;
			if(ansa[now_tota].average>ansb[now_totb].average)
			{
				LL R=ansa[now_tota].r;
				for(int i=ansa[now_tota].l;i<=R;i++)
					ans+=(++tot_pos)*a[i];
				now_tota++;
			}
			else {
				LL R=ansb[now_totb].r;
				for(int i=ansb[now_totb].l;i<=R;i++)
					ans+=(++tot_pos)*b[i];
				now_totb++;
			}
		}
		while(now_tota<=tota)
		{
			LL R=ansa[now_tota].r;
			for(int i=ansa[now_tota].l;i<=R;i++)
				ans+=(++tot_pos)*a[i];
			now_tota++;
		}
		while(now_totb<=totb)
		{
			LL R=ansb[now_totb].r;
			for(int i=ansb[now_totb].l;i<=R;i++)
				ans+=(++tot_pos)*b[i];
			now_totb++;
		}
		printf("Case %lld: %lld\n",ii,ans);
	}
}
/*
7 9
12 7 5 12 2 2 9 
17 4 8 4 16 3 4 19 19
*/