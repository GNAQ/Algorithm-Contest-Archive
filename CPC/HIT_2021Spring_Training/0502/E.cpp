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
	int n, tmp; ll ans=0;
	vector<int> vec;
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(tmp);
		vec.push_back(tmp);
	}
	sort(vec.begin(), vec.end());
	
	int j=0;
	for (int i=1;i<n;i++)
	{
		while (abs(vec[i]-vec[j])>=32) j++;
		ans+=i-j;
	}
	printf("%lld\n", ans);
	return;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
	}
}