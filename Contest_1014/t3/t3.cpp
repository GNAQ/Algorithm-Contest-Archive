#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstdlib>
#define ll long long
using namespace std;

int n;
int a[10010],b[10010],seq_a[10010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Trans(int l,int r)
{
	int tmp=a[r];
	for (int i=r;i>l;i--) a[i]=a[i-1];
	a[l]=tmp; 
}

int Find(int st,int val)
{
	for (int i=st;i<=n;i++) if (a[i]==val) return i;
	return -1;
}

bool Judge(int k)
{
	for (int i=1;i<=n-k+1;i++)
	{
		if (a[i]!=b[i])
		{
			int pos=Find(i,b[i]),pre_pos;
			if (pos==-1) return false;
			
			while (pos!=i)
			{
				pre_pos=max(pos-k+1,i);
				Trans(pre_pos,pre_pos+k-1);
				pos=Find(i,b[i]);
			}
		}
	}
	for (int i=1;i<=n;i++) if (a[i]!=b[i]) return false;
	return true;
}

void Solve()
{
	memset(a,0,sizeof a); memset(b,0,sizeof b); memset(seq_a,0,sizeof seq_a);
	readx(n);
	for (int i=1;i<=n;i++) readx(a[i]);
	for (int i=1;i<=n;i++) readx(b[i]);
	for (int i=1;i<=n;i++) seq_a[i]=a[i];
	
	for (int i=n;i>=1;i--)
	{
		for (int j=1;j<=n;j++) a[j]=seq_a[j];
		if (Judge(i))
		{
			printf("%d\n",i);
			return;
		}
	}
	printf("-1\n");
}

int main()
{
	// freopen("t3.out","w",stdout);
	int T; readx(T);
	while (T--) Solve();
	// system("pause");
	return 0;
}