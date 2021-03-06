#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
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


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	int n;
	cin>>n;
	
	int a=n/3;
	
	cout<<a*(n-1)-a*(a-1)/2<<'\n';
	
	
}
