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

int n,m,conn[1000010][3]; // - 1 - 2 | 3

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}



int Find(int e,int ds[])
{
	if (e!=ds[e]) ds[e]=Find(ds[e],ds);
	return ds[e];
}

void Merge(int a,int b,int ds[])
{
	ds[Find(b,ds)]=Find(a,ds);
}


namespace SGT
{
	#define LCH (inx<<1)
	#define RCH (inx<<1|1)
	
	struct Seg_Tree
	{
		int l,r,mid;
		int ds[10];
	}SGT[100010];
	int lx,rx;
	
	Seg_Tree Update(Seg_Tree A,Seg_Tree B)
	{
		Seg_Tree C;
	}
	
	void BuildTree()
	{
		
	}
	
	void Upd(int inx)
	{
		
	}
	
	
	
};

int main()
{
	
	
	
}


// a brief thought
/*

1. initalize a new ds,set L[1] & L[2] as default

2. try to update the connection between L[1]&R[3|4] , L[2]&R[3|4]

	2.0 note that the index is consistant

	2.1 we can merge them any times
	
	2.2 try to enum L[3] L[4] R[1] R[2]

3. copy the new ds

*/
