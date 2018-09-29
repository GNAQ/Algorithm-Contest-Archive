#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<utility>
#define inf 1e9
using namespace std;

long long a[100010]={0},b[100010]={0};
int fwt[100010]={0},setx[100010]={0},n,len,ans=0;

inline void uniq()
{
	int old_len=len;
	for (int i=1;i<=old_len;i++) if (b[i]==b[i+1]) 
	{
		b[i]=inf;
		len--;
	}
	sort(b+1,b+old_len+1);
}
inline void makeset() { for (int i=1;i<=len;i++) setx[i]=b[i]; }
inline int BinSearch(int element)
{
	int l=1,r=len,mid;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (setx[mid]==element) return mid;
		else if (setx[mid]>element) r=mid-1;
		else l=mid+1;
	}
}

inline void add(int pos,int val)
{
	while (pos<=len)
	{
		fwt[pos]+=val;
		pos+=(pos&(-pos));
	}
}

inline int getsum(int pos)
{
	int res=0;
	while (pos)
	{
		res+=fwt[pos];
		pos-=(pos&(-pos));
	}
	return res;
}

int main()
{
	scanf("%d",&n); len=n;
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	memcpy(b,a,sizeof(a));
	sort(b+1,b+n+1);
	
	uniq();
	makeset();
	
	for (int i=1;i<=n;i++) a[i]=BinSearch(a[i]);
		
	long long ans=0;
	for (int i=1;i<=n;i++)
	{
		add(a[i],1);
		ans+=getsum(len)-getsum(a[i]);
	}
	cout<<ans<<endl;
	return 0;
}
