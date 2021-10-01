#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
typedef long long ll;
using namespace std;

int n;
int pw[1010];

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
	for (int i=1;i<=100;i++) pw[i]=i*i;
	
	string s;
	int n;
	cin >> n >> s;
	
	ll ans = 0;
	for (int i=1;i<=n;i++) ans+=pw[i]*(s[i-1]=='1'?1:-1);
	cout << ans;
}