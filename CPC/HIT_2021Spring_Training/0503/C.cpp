#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<string>
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



int main()
{
	int n, tmp;
	vector<int> vec;
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(tmp);
		vec.push_back(tmp);
	}
	for (int i=1;i<=n;i++) printf("%d%c", i, " \n"[i==n]);
	for (int i=1;i<=n;i++) printf("1%c", " \n"[i==n]);
	return 0;
}