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

long double n,p1,p2,v1,v2;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

long double Go(long double t)
{
	long double l=0, r=t, mid, ans=t;
	
	for (int ww=1;ww<=64;ww++)
	{
		mid=(l+r)/2.0;
		
		long double lmax=p1,rmin=p2;
		// L
		if (mid*v1 >= p1*2.0)
		{
			lmax=max(lmax, mid*v1-p1);
		}
		if (mid*v1 >= p1)
		{
			lmax=max(lmax, (v1*mid+p1)/2);
		}
		else goto here;
		// R
		if (v2*mid >= (n-p2)*2.0)
		{
			rmin=min(rmin, p2 - (v2*mid-(n-p2)*2.0) );
		}
		if (v2*mid >= n-p2)
		{
			rmin=min(rmin, p2 - (v2*mid - (n-p2))/2 );
		}
		else goto here;
		if (rmin<=lmax) 
		{
			ans=min(ans,mid);
			r=mid;
		}
		else 
		{
			here:
			l=mid;
		}
	}
	return ans;
}

int main()
{
	int T;cin>>T;
	while(T--)
	{
		long double t;
		scanf("%Lf%Lf%Lf%Lf%Lf",&n,&p1,&v1,&p2,&v2);
		if(p1>p2) {swap(p1,p2);swap(v1,v2);}
		
		t=(n+p1)/v1;
		t=min(t,(2.0*n-p1)/v1);
		t=min(t,(p2+n)/v2);
		t=min(t,(2.0*n-p2)/v2);
		
		t=min(t,max(p1/v1,(2.0*n-p1-p2)/v2));
		t=min(t,max(p1/v1,(n+p2-2.0*p1)/v2));
		t=min(t,max((2.0*p2-p1)/v1,(n-p2)/v2));
		t=min(t,max((p2+p1)/v1,(n-p2)/v2));
		t=min(t,max((n-p1)/v1,p2/v2));
		
		t=min(t, Go(t));
		
		
		printf("%.10Lf\n",t);
	}
}
