#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
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
	int n; readx(n);
	vector<int> vec;
	for (int i=1;i<=n;i++)
	{
		int tmp; readx(tmp);
		vec.push_back(tmp);
	}
	sort(vec.begin(), vec.end());
	for (int i=1;i<vec.size();i++)
	{
		if ((vec[i-1]^vec[i])==1)
		{
			puts("Yes");
			return;
		}
	}
	puts("No");
	return;
}

void Clear()
{
	
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	return 0;
	
}