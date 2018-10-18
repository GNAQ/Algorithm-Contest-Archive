#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#define ll long long
using namespace std;

ll n,seq[500020],fg[500020][21],fm[500020][21],lg2[500020];
vector<int> vec;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll gcd(ll a,ll b)
{
	if (!b) return a;
	return gcd(b,a%b);
}

void init_ST()
{
	lg2[1]=0; lg2[2]=1;
	for (int i=3;i<=n+2;i++) lg2[i]=lg2[i>>1]+1;
	for (int i=1;i<=n;i++) fg[i][0]=fm[i][0]=seq[i];
	for (int w=1;w<=20;w++)
		for (int i=n;i;i--) if (i+(1<<w)-1<=n)
			fm[i][w]=min(fm[i][w-1],fm[i+(1<<(w-1))][w-1]);
	// exit(0);
	for (int w=1;w<=20;w++)
		for (int i=n;i;i--) if (i+(1<<w)-1<=n)
			fg[i][w]=gcd(fg[i][w-1],fg[i+(1<<(w-1))][w-1]);
	// system("pause");
}

ll Get_Gcd(int lx,int rx)
{
	int tp=lg2[rx-lx+1];
	return gcd(fg[lx][tp],fg[rx-(1<<tp)+1][tp]);
}

ll Get_Min(int lx,int rx)
{
	int tp=lg2[rx-lx+1];
	return min(fm[lx][tp],fm[rx-(1<<tp)+1][tp]);
}

bool Judge(int len)
{
	for (int i=1;i<=n-len+1;i++)
		if (Get_Gcd(i,i+len-1)==Get_Min(i,i+len-1)) return true;
	return false;
}

int main()
{
	freopen("data.in","r",stdin);
	freopen("t1.out","w",stdout);
	
	readx(n);
	for (int i=1;i<=n;i++) readx(seq[i]);
	init_ST();
	
	int l=1,r=n,mid,ans;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (Judge(mid)) { ans=mid; l=mid+1; }
		else r=mid-1;
	}
	for (int i=1;i<=n-ans+1;i++)
		if (Get_Min(i,i+ans-1)==Get_Gcd(i,i+ans-1)) vec.push_back(i);
	
	printf("%d %d\n",vec.size(),ans-1);
	for (auto v:vec) printf("%d ",v); putchar('\n');
	return 0;
}