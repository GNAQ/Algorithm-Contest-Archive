#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<iterator>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int gcd(int a,int b)
{
	if (!b) return a;
	return gcd(b,a%b);
}

ll fastpow(ll an,ll p,ll mod)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

int Real_BSGS(int a,int b,int p,int a_res)
{
	map<int,int> mapx;
	int upat=sqrt(p),nval=1,step=fastpow(a,upat,p);
	
	nval=b;
	for (int i=1;i<=upat;i++)
	{
		nval=1LL*nval*a%p;
		mapx[nval]=i; // mapx cannot equal to 0
	}
	
	nval=a_res;
	for (int k=1;k<=upat+1;k++)
	{
		nval=1LL*nval*step%p; 
		if (mapx[nval]!=0) return k*upat-mapx[nval];
	}
	return -1;
}

// exBSGS
int Solve(int a,int b,int p) // get x that satisfying a^x=b (mod p)
{
	a%=p; b%=p; 
	if (b==1) return 0; // stupid sol
	if (!a) return -1; // no sol
	
	int a_res=1,ex=0;
	for (int g=gcd(a,p);g!=1;g=gcd(a,p))
	{
		if (b%g) return -1;
		p/=g; b/=g; 
		a_res=1LL*a_res*a/g%p; ex++;
		if (b==a_res) return ex;
	}
	
	int result=Real_BSGS(a,b,p,a_res);
	if (result==-1) return -1;
	return result+ex;
}

int main()
{
	int a,b,p;
	while (1)
	{
		scanf("%d%d%d",&a,&p,&b);
		if (!a && !b && !p) return 0;
		
		// SPJ
		if (p==1) { printf("0\n"); continue; }
		
		int result = Solve(a,b,p);
		if (result==-1) printf("No Solution\n");
		else printf("%d\n",result);
	}
}