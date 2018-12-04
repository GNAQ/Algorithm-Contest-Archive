#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

ll n,p;
const ll mod=1e9+7;

struct Mat
{
	int a[110][110];
	Mat(){ memset(a,0,sizeof a); }
	Mat operator * (const Mat& B)
	{
		Mat C;
		for (int k=1;k<=n;k++)
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++) C.a[i][j]=(C.a[i][j]+1LL*a[i][k]*B.a[k][j]%mod)%mod;
		return C;
	}
};

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

Mat fastpow(Mat an,ll p)
{
	Mat ret=an; p--;
	for (;p;p>>=1,an=an*an) if (p&1) ret=ret*an;
	return ret;
}

int main()
{
	readx(n); readx(p); Mat an;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) readx(an.a[i][j]);
	an=fastpow(an,p);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) printf("%d%c",an.a[i][j]," \n"[j==n]);
}
