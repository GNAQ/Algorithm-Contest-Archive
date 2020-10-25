#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

int n,ai[200010];
ll pref[200010];
ll ans;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline ll Val(int l,int r)
{
	return pref[r]-pref[l-1];
}

pair<ll, ll> Find(int l,int r)
{
	int lx=l,rx=r;
	int mid = (l+r)/2;
	while (l<r)  // [l <-> mid] & [mid+1 <-> r]
	{
		mid = (l+r)/2;
		if (Val(lx,mid)==Val(mid+1,rx))
			return make_pair(Val(lx,mid), Val(mid+1,rx));
		else if (Val(lx,mid)<Val(mid+1,rx))
			l=mid+1;
		else
			r=mid;
	}
	if (mid+2<=rx)
		if ( abs(Val(lx,mid+1)-Val(mid+2,rx)) < abs(Val(lx,mid)-Val(mid+1,rx)) ) 
			mid++;
	if (mid-1>=lx)
		if ( abs(Val(lx,mid-1)-Val(mid,rx)) < abs(Val(lx,mid)-Val(mid+1,rx)) )
			mid--;
	return make_pair(Val(lx,mid), Val(mid+1,rx));
}

int main()
{
	readx(n); ans=100000000000000000LL;
	for (int i=1;i<=n;i++) 
		readx(ai[i]);
	for (int i=1;i<=n;i++)
		pref[i]=pref[i-1]+ai[i];
	
	for (int m=2;m<=n-2;m++) // midpoints  [1 <-> m] & [m+1 <-> n]
	{
		ll maxv,minv;
		pair<ll,ll> v1,v2;
		
		v1=Find(1,m); v2=Find(m+1,n);
		
		maxv=max(max(v1.first,v1.second),max(v2.first,v2.second));
		minv=min(min(v1.first,v1.second),min(v2.first,v2.second));
		ans=min(ans,maxv-minv);
	}
	printf("%lld\n",ans);
	return 0;
}