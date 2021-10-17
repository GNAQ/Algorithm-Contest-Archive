#include <bits/stdc++.h>
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

bool cmp(int a, int b)
{
	return a > b;
}

int main()
{
	vector<int> vec;
	int n, k, tmp;
	readx(n); readx(k);
	for (int i=1;i<=n;i++)
	{
		readx(tmp);
		vec.push_back(tmp);
	}
	sort(vec.begin(), vec.end(), cmp);
	ll ans = 0;
	for (int i=0;i<min(k, (int)vec.size());i++)
	{
		ans += vec[i];
	}
	printf("%lld\n", ans);
	return 0;
}