#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

const double eps=1e-7;
int n;

struct Mat
{
	double a[110][110];
	
	bool Gauss_Elimination()
	{
		double baz; int ml;
		
		for (int i=1;i<=n;i++)
		{
			ml=i; 
			for (int j=i+1;j<=n;j++) if (fabs(a[j][i])>fabs(a[ml][i])) ml=j;
			if (ml!=i) for (int j=1;j<=n+1;j++) swap(a[i][j],a[ml][j]);
			
			if (fabs(a[i][i])>eps) for (int j=i+1;j<=n;j++)
			{
				baz=a[j][i]/a[i][i];
				for (int k=1;k<=n+1;k++) a[j][k]-=baz*a[i][k];
			}
		}
		
		bool nosol=0;
		for (int i=1;i<=n;i++)
		{
			int pos=1;
			while (fabs(a[i][pos])<=eps) pos++;
			nosol=(pos>=n+1);
		}
		if (nosol) return false;
		
		//set back
		a[n][n+1]/=a[n][n];
		for (int i=n-1;i>=1;i--)
		{
			double sum=0;
			for (int j=i+1;j<=n;j++) a[i][n+1]-=a[i][j]*a[j][n+1];
			a[i][n+1]/=a[i][i];
		}
		return true;
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

int main()
{
	readx(n); Mat A;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n+1;j++) scanf("%lf",&A.a[i][j]);
	if (!A.Gauss_Elimination()) printf("No Solution\n");
	else for (int i=1;i<=n;i++) printf("%.2lf\n",A.a[i][n+1]);
}
