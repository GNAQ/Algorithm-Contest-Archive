#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
const LL MAXN=1e5+100;
LL k,L,R,a[MAXN],l[MAXN],r[MAXN],suml,sumr,tmp[MAXN];

struct node
{
	int l,r,a;
} nod[MAXN];


bool check(LL tot)
{
	for(LL i=1;i<=k;i++)
	{
		tmp[i]=a[i]-l[i]*tot;
		if(tmp[i]<0) return 0;
	}
	LL res=0,delt=L-suml;
	if(delt<=0) return 1;
	for(LL i=1;i<=k;i++)
	{
		LL plus=tmp[i]/tot;
		if(plus>=r[i]-l[i])
			delt-=r[i]-l[i];
		else {
			delt-=plus;
			res+=tmp[i]%tot;
			if(res>=tot)
			{
				res-=tot;
				delt--;
			}
		}
		if(delt<=0) return 1;
	}
	return 0;
}	

bool cmp(node a, node b)
{
	return a.r-a.l>b.r-b.l;
}

int main()
{
	cin>>k>>L>>R;
	for(LL i=1;i<=k;i++)
		scanf("%lld",&a[i]);
	for(LL i=1;i<=k;i++)
	{
		scanf("%lld%lld",&l[i],&r[i]);
		suml+=l[i];
		sumr+=r[i];
	}
	
	for (int i=1;i<=k;i++)
	{
		nod[i].a=a[i];
		nod[i].l=l[i];
		nod[i].r=r[i];
	}	
	sort(nod+1,nod+k+1,cmp);
	for (int i=1;i<=k;i++)
	{
		a[i]=nod[i].a;
		l[i]=nod[i].l;
		r[i]=nod[i].r;
	}
	
	if(suml>R)
	{
		cout<<0;
		return 0;
	}
	LL ll=1,rr=1e9,ans=0;
	while(ll<=rr)
	{
		LL mid=(ll+rr)>>1;
		if(check(mid)) ans=mid,ll=mid+1;
		else rr=mid-1;
	}
	cout<<ans;
}
