#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<string>
typedef long long ll;
using namespace std;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Solve()
{
	int k, m, n;
	readx(k); readx(m); readx(n);
	vector<int> vec; int tmp;
	int tot = 0;
	for (int i=1;i<=n;i++)
	{
		readx(tmp); vec.push_back(tmp);
		tot += tmp;
	}
	sort(vec.begin(), vec.end());
	int ans=0;
	for (int i=n-1;i>=0;i--)
	{
		if (tot+m<=k)
		{
			printf("%d\n", ans);
			return;
		}
		tot-=vec[i];
		ans++;
	}
	printf("%d\n", ans);
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
	}
}