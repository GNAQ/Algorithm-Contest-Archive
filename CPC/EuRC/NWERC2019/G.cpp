#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

double xi[10010];
int n, k;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

double Calc(int upper)
{
	double ret = ((double)k / (double)n) * ((double)(k-1) / (double)(n-1));
	int lower = n - 2;
	for (int i=1;i<=k-2;i++)
	{
		ret = ret * ( (double)(upper) / (double)(lower) );
		upper--;
		lower--;
	}
	return ret;
}

int main()
{
	readx(n); readx(k);
	for (int i=1;i<=n;i++)
	{
		scanf("%lf", &xi[i]);
		xi[i+n] = xi[i];
	}
	
	if (k == 1)
	{
		for (int i=1;i<=n;i++)
			printf("%.8lf%c", 100.00/(double)n, " \n"[i==n]);
		return 0;
	}
	if (n == 2)
	{
		printf("%.8lf %.8lf\n", xi[1], xi[2]);
		return 0;
	}
	
	for (int i=n+1;i<=2*n;i++)
	{
		double ans = 0;
		double accu = 0;
		for (int j=0;j<=(n-k);j++)
		{
			accu += xi[i-j];
			// cerr << "!!" << accu << endl;
			// cerr << "Calc C(" << n-2-j << " " << k-2 << ") =" << Calc(n-2-j) << endl;
			ans += (accu) * Calc(n-2-j);
		}
		printf("%.12lf ", ans);
	}
	return 0;
}