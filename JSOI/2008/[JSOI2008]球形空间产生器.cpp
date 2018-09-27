#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;

struct _Matrix
{
	double a[30][30]; int sz;
	double sol[30];
	_Matrix ()
	{
		memset(a,0,sizeof a);
		memset(sol,0,sizeof sol);
		sz=0;
	}
	
	void Gauss_Elimination()
	{
		for (int i=1;i<=sz;i++)
		{
//			int tmp=i;
//			for (int j=i+1;j<=sz;j++) if (fabs(a[j][i])>fabs(a[tmp][i])) tmp=j;
//			if (tmp!=i) for (int j=1;j<=sz+1;j++) swap(a[i][j],a[tmp][j]);
			
			for (int j=i+1;j<=sz;j++)
			{
				double baz=a[j][i]/a[i][i];
				for (int k=1;k<=sz+1;k++) a[j][k]-=a[i][k]*baz;
			}
		}
		
		for (int i=sz;i;i--)
		{
			double sumv=0.0;
			for (int j=i+1;j<=sz;j++) sumv+=a[i][j]*sol[j];
			sol[i]=(a[i][sz+1]-sumv)/a[i][i];
		}
	}
};

_Matrix origin;
int n;
double mapx[30][30];

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	readx(n);
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=n;j++) scanf("%lf",&mapx[i][j]);
	
	origin.sz=n;
	for (int i=2;i<=n+1;i++)
	{
		for (int j=1;j<=n;j++) origin.a[i-1][j]=2*(mapx[i][j]-mapx[1][j]);
		for (int j=1;j<=n;j++) origin.a[i-1][n+1]+=mapx[i][j]*mapx[i][j]-mapx[1][j]*mapx[1][j];
	}
	
	origin.Gauss_Elimination();
	for (int i=1;i<=n;i++) printf("%.3lf%c",origin.sol[i]," \n"[i==n]);
}
