#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define fst first
#define snd second
#define ll long long
using namespace std;

pair<int,int> pts[100010];
int n;


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
	readx(n);
	for (int i=1;i<=n;i++) { readx(pts[i].fst); readx(pts[i].snd); }
	
	
	
}