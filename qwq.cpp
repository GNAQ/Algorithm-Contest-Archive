#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

struct Mat
{
	int siz,a[310][310];
	Mat() { siz=0; memset(a,0,sizeof a); }
};

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int Gauss_Elimination(Mat M)
{
	int N=M.siz;
	for (int i=1;i<=N;i++)
	{
		int 
	}
}



int main()
{
	
}