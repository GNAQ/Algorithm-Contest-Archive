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
using namespace std;
typedef long long ll;

int g[1010][1010];
int p[1010][1010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Clear(int n)
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			g[i][j]=p[i][j]=0;
}

void OutG(int n)
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			printf("%d%c", g[i][j], " \n"[j==n]);
	
}

void Write4(int x, int mul, int n) // mul: 4*mul steps
{
	for (int i=1;i<=n;i+=2)
	{
		g[i][x] = 1 + 4*(i/2) + 4*mul*n;
		g[i][x+1] = 2 + 4*(i/2) + 4*mul*n;
		g[i+1][x+1] = 3 + 4*(i/2) + 4*mul*n;
		g[i+1][x] = 4 + 4*(i/2) + 4*mul*n;
	}
	
	x+=2;
	for (int i=n-1;i>=1;i-=2)
	{
		int j = n-i;
		g[i+1][x+1] = 1 + 4*(j/2) + 2*n + 4*mul*n;
		g[i+1][x] = 2 + 4*(j/2) + 2*n + 4*mul*n;
		g[i][x] = 3 + 4*(j/2) + 2*n + 4*mul*n;
		g[i][x+1] = 4 + 4*(j/2) + 2*n + 4*mul*n;
	}
	x-=2;
	
	int delta = 2 * (n-2) + 4*mul*n;
	g[n-1][x] = 1 + delta;
	g[n][x] = 2 + delta;
	g[n][x+1] = 3 + delta;
	g[n-1][x+1] = 4 + delta;
	g[n-1][x+2] = 5 + delta;
	g[n][x+2] = 6 + delta;
	g[n][x+3] = 7 + delta;
	g[n-1][x+3] = 8 + delta;
}

void CCopy(int x, int y, int n, int delta)
{
	for (int i=x;i<x+n;i++)
		for (int j=y;j<y+n;j++)
			g[i][j] = n*n+1 - p[i-x+1][j-y+1] + delta;
}

void Enlarge5(int n)
{
	CCopy(3, 3, n-4, (6*n-12));
	
	for (int i=1;i<=n;i+=2)
	{
		g[i][1] = 1 + 4*(i/2);
		g[i][2] = 2 + 4*(i/2);
		g[i+1][2] = 3 + 4*(i/2);
		g[i+1][1] = 4 + 4*(i/2);
	}
	
	for (int i=3;i<=n;i+=2)
	{
		g[n][i] = 1 + 4*((i-2)/2) + 2*n;
		g[n-1][i] = 2 + 4*((i-2)/2) + 2*n;
		g[n-1][i+1] = 3 + 4*((i-2)/2) + 2*n;
		g[n][i+1] = 4 + 4*((i-2)/2) + 2*n;
	}
	
	for (int i=n-3;i>=3;i-=2)
	{
		int j = n-2-i;
		g[i+1][n] = 1 + 4*(j/2) + 4*n-4;
		g[i+1][n-1] = 2 + 4*(j/2) + 4*n-4;
		g[i][n-1] = 3 + 4*(j/2) + 4*n-4;
		g[i][n] = 4 + 4*(j/2) + 4*n-4;
	}
	g[3][n]=g[4][n]+1;
	g[3][n-1]=g[3][n]+1;
	
	int delta = g[3][3];
	for (int i=3;i<=n;i+=2)
	{
		g[2][i] = 1 + 4*((i-2)/2) + delta;
		g[1][i] = 2 + 4*((i-2)/2) + delta;
		g[1][i+1] = 3 + 4*((i-2)/2) + delta;
		g[2][i+1] = 4 + 4*((i-2)/2) + delta;
	}
}

void Enlarge7(int n)
{
	CCopy(3, 3, n-4, (n-2)*2);
	
	for (int i=1;i<=n-3;i+=2)
	{
		g[i][1] = 1 + 4*(i/2);
		g[i][2] = 2 + 4*(i/2);
		g[i+1][2] = 3 + 4*(i/2);
		g[i+1][1] = 4 + 4*(i/2);
	}
	g[n-2][1]=g[n-3][1]+1;
	g[n-2][2]=g[n-2][1]+1;
	
	int delta = g[3][3];
	for (int i=3;i<=n-2;i+=2)
	{
		g[2][i] = 1 + 4*((i-2)/2) + delta;
		g[1][i] = 2 + 4*((i-2)/2) + delta;
		g[1][i+1] = 3 + 4*((i-2)/2) + delta;
		g[2][i+1] = 4 + 4*((i-2)/2) + delta;
	}
	// OutG(n);
	
	delta = g[1][n-2];
	for (int i=1;i<=n;i+=2)
	{
		g[i][n-1] = 1 + (i/2)*4 + delta;
		g[i][n] = 2 + (i/2)*4 + delta;
		g[i+1][n] = 3 + (i/2)*4 + delta;
		g[i+1][n-1] = 4 + (i/2)*4 + delta;
	}
	g[n-1][n]=g[n-2][n]+1;
	g[n][n]=g[n-1][n]+1;
	
	delta = g[n][n];
	for (int i=n-2;i>=1;i-=2)
	{
		int j = n-1-i;
		g[n][i+1] = 1 + 4*(j/2) + delta;
		g[n-1][i+1] = 2 + 4*(j/2) + delta;
		g[n-1][i] = 3 + 4*(j/2) + delta;
		g[n][i] = 4 + 4*(j/2) + delta;
	}
	g[n-1][1]=g[n-1][2]+1;
	g[n][1]=g[n-1][1]+1;
	
}

void Solve(void)
{
	int n; readx(n);
	if (n==2)
	{
		printf("1 2\n4 3\n");
		return;
	}
	if (!(n%2)) // even number
	{
		for (int i=1;i<=n;i+=4)
		{
			Write4(i, i/4, n);
		}
		if (n%4)
		{
			for (int i=1;i<=n;i+=2)
			{
				g[i][n-1] = 1 + 4*(i/2) + 4*(n/4)*n;
				g[i][n] = 2 + 4*(i/2) + 4*(n/4)*n;
				g[i+1][n] = 3 + 4*(i/2) + 4*(n/4)*n;
				g[i+1][n-1] = 4 + 4*(i/2) + 4*(n/4)*n;
			}
		}
	}
	else // odd number
	{
		int st;
		if (n%4==1)
		{
			st=1;
			g[1][1]=p[1][1]=1;
		}
		else
		{
			st=3;
			g[1][1]=p[1][1]=1; g[1][2]=p[1][2]=2; g[1][3]=p[1][3]=3;
			g[2][1]=p[2][1]=8; g[2][2]=p[2][2]=7; g[2][3]=p[2][3]=4;
			g[3][1]=p[3][1]=9; g[3][2]=p[3][2]=6; g[3][3]=p[3][3]=5;
		}
		while (st<n)
		{
			st+=4;
			if (st%4==1) Enlarge5(st);
			else Enlarge7(st);
			for (int i=1;i<=st;i++)
				for (int j=1;j<=st;j++)
					p[i][j]=g[i][j];
		}
		
	}
	
	OutG(n);
	Clear(n);
}


int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
	}
	
	return 0;
}