#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=1e5+100;
int org_dat[MAXN],st[MAXN],top;
double dat[MAXN];
template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar();if(ch=='.') ch=getchar();}
	x*=k;
}
int binary_search(int x)
{
	int l=1,r=top,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(dat[st[mid]]<=x)
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return st[ans];
}
double solve(int n)
{
	top=0;
	double ans=0;int last_h=dat[1];
	st[++top]=1;
	for(int i=2;i<=n;i++)
	{
		if(dat[i]<last_h)
		{
			st[++top]=i;
			last_h=dat[i];
		}
		int pos=binary_search(dat[i]);
		if(pos==1) ans=max(ans,1.0*(i-1));
		else {
			int k=dat[pos-1]-dat[pos];
			ans=max(ans,i-(pos-1.0*(dat[i]-dat[pos])/k));
		}
	}
	return ans;
}
int main()
{
	int n,k;scanf("%d%d",&n,&k);n++;
	for(int i=1;i<=n;i++) scanf("%d",&org_dat[i]);
	for(int ii=1;ii<=k;ii++)
	{
		int g;readx(g);
		for(int i=1;i<=n;i++)
			dat[i]=org_dat[i]-g*i;
		double ans=0;
		ans=max(ans,solve(n));
		for(int i=1;i<=n/2;i++)
			swap(dat[i],dat[n-i+1]);
		for(int i=1;i<=n;i++)
			dat[i]=-dat[i];
		ans=max(ans,solve(n));
		if(ans<=(1e-8)) printf("-1\n");
		else printf("%.10lf\n",ans);
	}
}