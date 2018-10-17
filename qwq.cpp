#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cstdlib>
#include<map>
#include<set>
#include<vector>
#include<queue>
#define ll long long
using namespace std;

int T,ans,seq[20],n;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void DFS(int step)
{
	if (step>=ans) return;
	int len=0;
	for (int i=3;i<=14;i++) //单顺 
	{
		if (!seq[i]) len=0;
		else
		{
			len++;
			if (len>=5)
			{
				for (int j=i;j>=i-len+1;j--) seq[j]--;
				DFS(step+1);
				for (int j=i;j>=i-len+1;j--) seq[j]++; 
			}
		}
	}
	len=0;
	for (int i=3;i<=14;i++) // 双顺
	{
		if (seq[i]<2) len=0;
		else
		{
			len++;
			if (len>=3)
			{
				for (int j=i;j>=i-len+1;j--) seq[j]-=2;
				DFS(step+1);
				for (int j=i;j>=i-len+1;j--) seq[j]+=2; 
			}
		}
	}
	len=0;
	for (int i=3;i<=14;i++)
	{
		if (seq[i]<3) len=0;
		else
		{
			len++;
			if (len>=2)
			{
				for (int j=i;j>=i-len+1;j--) seq[j]-=3;
				DFS(step+1);
				for (int j=i;j>=i-len+1;j--) seq[j]+=3;
			}
		}
	}
	
	for (int i=2;i<=14;i++) // 带牌
	{
		if (seq[i]>=3)
		{
			seq[i]-=3;
			for (int j=2;j<=14;j++) // 三带一
			{
				if (seq[j]<1||j==i) continue;
				seq[j]--;
				DFS(step+1);
				seq[j]++;
			}
			for (int j=2;j<=14;j++)
			{
				if (seq[j]<2||j==i) continue;
				seq[j]-=2;
				DFS(step+1);
				seq[j]+=2;
			}
			seq[i]+=3;
		}
		if (seq[i]==4)
		{
			seq[i]-=4;
			for (int j=2;j<=14;j++)
			{
				if (seq[j]<1||j==i) continue;
				seq[j]--;
				for (int k=2;k<=14;k++)
				{
					if (seq[k]==0||j==k||i==k) continue;
					seq[k]--;
					DFS(step+1);
					seq[k]++;
				}
				seq[j]++;
			}
			for (int j=2;j<=14;j++)
			{
				if (seq[j]<2||j==i) continue;
				
			}
			seq[i]+=4;
		}
	}
	
}

int main()
{
	readx(n); ans=2*1e9; int tmp=0,crd;
	for (int i=1;i<=n;i++) 
	{
		readx(tmp); readx(crd);
		if (!tmp) seq[15]++;
		else if (tmp==1) seq[14]++;
		else seq[tmp]++;
	}
	DFS(0);
	printf("%d\n",ans);
	return 0;
}