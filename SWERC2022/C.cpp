#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 998244353;

struct Matrix
{
	int a[202][202];
	int s;
	
	Matrix operator * (const Matrix &b)
	{
		Matrix ret;
		ret.s = this->s;
		for (int i=1;i<=s;i++)
			for (int j=1;j<=s;j++)
				ret.a[i][j] = 0;
		for (int i=1;i<=s;i++)
			for (int k=1;k<=s;k++)
				for (int j=1;j<=s;j++)
					ret.a[i][j] = ((ll)ret.a[i][j] + 1LL * this->a[i][k] * b.a[k][j]) % mod;
		return ret;
	}
};

int n, m, k;
Matrix G, A, X;
int d[2010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

Matrix fastpow(Matrix an, int p)
{
	Matrix ret; ret.s = an.s;
	for (int i=1;i<=an.s;i++)
		ret.a[i][i] = 1;
	for (;p;p>>=1, an = an * an)
		if (p & 1) ret = ret * an;
	return ret;
}

int main()
{
	readx(n); readx(m); readx(k);
	G.s = n;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			G.a[i][j] = 0;
	int u, v;
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v);
		G.a[u][v] = G.a[v][u] = 1;
		d[u]++; d[v]++;
	}
	
	if (k == 1)
	{
		puts("0");
		return 0;
	}
	
	X.s = A.s = 2 * n;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			A.a[i][j] = G.a[i][j];
			if (i == j)
			{
				A.a[i + n][j] = 1;
				A.a[i][j + n] = 1 - d[i];
			}
		}
	Matrix Xhigh = G * G;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			X.a[i][j] = Xhigh.a[i][j];
			if (i == j) X.a[i][j] -= d[i];
			X.a[i + n][j] = G.a[i][j];
		}
	
	A = fastpow(A, k - 2);
	X = A * X;
	
	ll ans = 0;
	for (int i=1;i<=n;i++)
		ans = (ans + X.a[i][i]) % mod;
	printf("%lld\n", (ans % mod + mod) % mod);
}