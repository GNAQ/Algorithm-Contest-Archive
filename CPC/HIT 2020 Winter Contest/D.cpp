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

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int Scnt[3010], Qcnt[3010];
vector< pair<int, int> > Dvec;
char str[3010];

int main()
{
	int T; readx(T);
	while (T--)
	{
		ll ans=0;
		int n,m; readx(n); readx(m);
		
		if (n == 0 && m == 0) 
		{
			printf("0\n");
			continue;
		}
		
		for (int i=1;i<=n;i++) 
		{
			scanf("%s", str+1);
			for (int j=1;j<=m;j++)
			{
				if (str[j]=='S')
				{
					Scnt[j]++;
				}
				else if (str[j]=='D')
				{
					Dvec.push_back( make_pair(i,j) );
				}
				else
				{
					Qcnt[i]++;
				}
			}
		}
		
		int Dsiz = Dvec.size()-1;
		
		for (int i=0;i<=Dsiz;i++)
		{
			int ii,jj;
			ii = Dvec[i].first;
			jj = Dvec[i].second;
			ans += 1LL * Scnt[jj] * Qcnt[ii];
		}
		
		printf("%lld\n", ans);
		
		for (int i=1;i<=m;i++) Scnt[i]=Qcnt[i]=0;
		Dvec.clear(); 
	}
	
}
