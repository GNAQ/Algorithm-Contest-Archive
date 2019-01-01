#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

const double eps=1e-6;
int n;

struct Mat
{
	int C,R;
	double a[310][310];
	Mat() { C=R=0; memset(a,0,sizeof a); }
	
	void Print()
	{
		for (int i=1;i<=C;i++)
			for (int j=1;j<=R;j++) printf("%.2lf%c",a[i][j]," \n"[j==R]);
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

bool G_J_Elim(Mat& A) // -C |R
{
	int N=A.C,M=A.R;
	for (int i=1;i<=N;i++)
	{
		int ml=i;
		for (int j=i+1;j<=N;j++) if (fabs(A.a[j][i])>fabs(A.a[ml][i])) ml=j;
		if (ml!=i) for (int j=1;j<=M;j++) swap(A.a[ml][j],A.a[i][j]);
		
		for (int j=1;j<=N;j++) if (i!=j)
		{
			double baz=A.a[j][i]/A.a[i][i];
			for (int k=1;k<=M;k++) A.a[j][k]-=A.a[i][k]*baz;
		}
	}
	
	for (int i=1;i<=N;i++) if (fabs(A.a[i][i])<eps) return false;
	
	for (int i=1;i<=N;i++) A.a[i][M]/=A.a[i][i];
	return true;
}

int main()
{
	readx(n); Mat M; M.C=n; M.R=n+1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n+1;j++)
			scanf("%lf",&M.a[i][j]);
	
	if (!G_J_Elim(M)) printf("No Solution\n");
	else for (int i=1;i<=n;i++) printf("%.2lf\n",M.a[i][n+1]);
}