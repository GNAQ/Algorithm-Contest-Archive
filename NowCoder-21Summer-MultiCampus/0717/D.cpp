#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int a[2010][2010],b[2010];
int n, m;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}



int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			char c = getchar(); 
			while (c<'0' || c>'2') c=getchar();
			a[i][j]=c-'0';
		}
	}
	for (int i=1;i<=m;i++) 
	{
		char c = getchar(); 
		while (c<'0' || c>'2') c=getchar();
		b[i]=c-'0';
	}
	
	// for (int i=1;i<=n;i++)
	// 	for (int j=1;j<=n;j++)
	// 		printf("%d%c", a[i][j], " \n"[j==n]);
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			a[i][j]+=a[i][j-1];
	
	// for (int i=1;i<=n;i++)
	// 	for (int j=1;j<=n;j++)
	// 		printf("%d%c", a[i][j], " \n"[j==n]);
	
	int ans = 0;
	for (int i=1;i<=n;i++)
		for (int j=m;j<=n;j++)
			if (a[i][j]-a[i][j-m]==0)
				ans++;
	
	cout << ans << endl;
	return 0;
}