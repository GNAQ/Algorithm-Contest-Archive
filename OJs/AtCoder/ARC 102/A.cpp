#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
typedef long long ll;
using namespace std;

int n,ans;
char dna[100010];
int cnt[1000];

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
	scanf("%d %s", &n, dna+1);
	
	for (int i=1;i<=n;i++)
	{
		cnt['A']=cnt['G']=cnt['C']=cnt['T']=0;
		for (int j=i;j<=n;j++)
		{
			cnt[dna[j]]++;
			if (cnt['A']==cnt['T'] && cnt['C']==cnt['G']) ans++;
		}
	}
	printf("%d\n",ans);
}