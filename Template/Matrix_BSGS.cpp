#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<vector>
#include<map>
#define ll long long
using namespace std;

int P,n,Mat_Mod;
struct Mat
{
	int a[310][310],dem;
	
	Mat(){ memset(a,0,sizeof a); dem=0; }
	
	bool operator < (const Mat& B) const
	{
		for (int i=1;i<=dem;i++)
			for (int j=1;j<=dem;j++) if (B.a[i][j]!=a[i][j])
				return a[i][j]<B.a[i][j];
		return false;
	}
	Mat operator * (const Mat& B)
	{
		Mat C; C.dem=dem;
		for (int i=1;i<=dem;i++)
			for (int j=1;j<=dem;j++)
				for (int k=1;k<=dem;k++)
					C.a[i][j]=(C.a[i][j]+a[i][k]*B.a[k][j])%Mat_Mod;
		return C;
	}
	bool operator == (const Mat& B)
	{
		for (int i=1;i<=dem;i++)
			for (int j=1;j<=dem;j++) if (a[i][j]!=B.a[i][j]) return false;
		return true;
	}
}A,B;
map<Mat,int> pows;

inline char gc()
{
    static char BUFF[20000],*S=BUFF,*T=BUFF;
    return S==T&&(T=(S=BUFF)+fread(BUFF,1,20000,stdin),S==T)?EOF:*S++;
}
template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=gc(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=gc(); }
	x*=k;
}

ll fastpow(ll an,ll p)
{
	ll ret=1;
	for (;p;p>>=1,an=an*an%P) if (p&1) ret=ret*an%P;
	return ret;
}

Mat fastpow(Mat an,ll p)
{
	Mat ret=an; p--;
	for (;p;p>>=1,an=an*an) if (p&1) ret=ret*an;
	return ret;
}

Mat Matrix_Inv(Mat M)
{
	int N=M.dem;
	for (int i=1;i<=N;i++) M.a[i][i+N]=1;
	for (int i=1;i<=N;i++)
	{
		int ml=i;
		for (int j=i+1;j<=N;j++) if (M.a[j][i]) { ml=j; break; }
		if (ml!=i) for (int j=1;j<=N*2;j++) swap(M.a[i][j],M.a[ml][j]);
		
		ll inv=fastpow(M.a[i][i],P-2);
		for (int j=i;j<=N*2;j++) M.a[i][j]=(M.a[i][j]*inv)%P;
		for (int j=1;j<=N;j++) if (j!=i)
		{
			int baz=M.a[j][i];
			for (int k=i;k<=N*2;k++) M.a[j][k]=((M.a[j][k]-baz*M.a[i][k])%P+P)%P;
		}
	}
	Mat ret; ret.dem=N;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++) ret.a[i][j]=M.a[i][j+N];
	return ret;
}

int main()
{
	readx(n); readx(P);
	A.dem=B.dem=n; Mat_Mod=P;
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) readx(A.a[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) readx(B.a[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) { B.a[i][j]%=P; A.a[i][j]%=P; }
	
	int upat=sqrt(P); Mat nval,mulval=fastpow(A,upat);
	
	nval.dem=n;
	for (int i=1;i<=n;i++) nval.a[i][i]=1;
	
	for (int i=0;i<upat;i++)
	{
		if (nval==B) { printf("%d\n",i); return 0; }
		int& tmp=pows[nval];
		if (!tmp) tmp=i+1;
		nval=nval*A;
	}
	
	nval=mulval;
	for (int k=1;;k++)
	{
		Mat inv=Matrix_Inv(nval);
		Mat tmp=inv*B;
		if (pows[tmp]!=0) { printf("%d\n",pows[tmp]-1+k*upat); return 0; }
		nval=nval*mulval;
	}
}
