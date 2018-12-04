#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

int n,m;
bool nnum[10000010];
int pnum[8000010],ptr_p;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Eular_Shake(ll lim)
{
	nnum[0]=nnum[1]=1;
	for (int i=2;i<=lim;i++)
	{
		if (!nnum[i]) pnum[++ptr_p]=i;
		for (int j=1;j<=ptr_p && 1LL*pnum[j]*i<=lim;j++)
		{
			nnum[i*pnum[j]]=1;
			if (!(i%pnum[j])) break;
		}
	}
}

int main()
{
	readx(n); readx(m); int tmp;
	Eular_Shake(n);
	for (int i=1;i<=m;i++)
	{
		readx(tmp);
		printf(nnum[tmp]?"No\n":"Yes\n");
	}
}
