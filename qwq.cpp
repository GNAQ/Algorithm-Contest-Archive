#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

int n,seq[100010],m;
int mac[110][110],tim[110][110];
bool free[30][510];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}



int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n*m;i++) readx(seq[i]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) readx(mac[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) readx(tim[i][j]);
	
	for (int i=1;i<=n;i++)
	{
		
	}
	
	
	
}