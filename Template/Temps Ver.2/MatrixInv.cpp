#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

const ll mod=1000000007LL;
int n;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

struct Matrix
{
	ll siz,a[410][810];
	
	ll* operator [] (const int inpr) { return a[inpr]; }
	
	bool GetInv()
	{
		int swp; ll baze,siz2=siz*2;
		for (int i=1;i<=siz;i++)
		{
			if (i%50==0) cerr<<i<<endl;
			swp=i;
			for (int j=i;j<=siz;j++) if (a[j][i]) { swp=j; break; }
			if (swp!=i) for (int j=1;j<=siz2;j++) swap(a[i][j],a[swp][j]);
			if (!a[i][i]) return false;
			
			baze=fastpow(a[i][i],mod-2);
			for (int j=i;j<=siz2;j++) a[i][j]=a[i][j]*baze%mod;
			for (int j=1;j<=siz;j++) if (j!=i)
			{
				baze=a[j][i];
				for (int k=i;k<=siz2;k++) 
					a[j][k]=(a[j][k]-(baze*a[i][k])%mod+mod)%mod;
			}
		}
		return true;
	}
};

Matrix Mat;

int main()
{
	readx(n); Mat.siz=n; 
	for (int i=1;i<=n;i++)	
		for (int j=1;j<=n;j++) 
			readx(Mat[i][j]);
	for (int i=1;i<=n;i++) Mat[i][i+n]=1;
	
	if (Mat.GetInv()) 
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				printf("%lld%c",Mat[i][j+n]," \n"[j==n]);
	else printf("No Solution\n");
}