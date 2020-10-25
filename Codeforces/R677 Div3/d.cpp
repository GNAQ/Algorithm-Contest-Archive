#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<map>
typedef long long ll;
using namespace std;

int n,bel[10010];
map<int,int> mp;

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
	int T; readx(T);
	while (T--)
	{
		mp.clear();
		int id1, id2, tar, cnt=0;
		readx(n);
		for (int i=1;i<=n;i++) 
		{
			readx(bel[i]);
			mp[bel[i]]+=1;
			if (mp[bel[i]]==1) cnt++;
		}
		
		if (cnt==1)
		{
			printf("NO\n");
			continue;
		}
		
		printf("YES\n");
		id1=bel[1];
		for (int i=1;i<=n;i++) 
			if (bel[i]!=id1) 
			{
				id2=bel[i];
				tar=i;
				break;
			}
		
		for (int i=1;i<=n;i++) if (bel[i]!=id1)
			printf("1 %d\n",i);
		for (int i=2;i<=n;i++) if (bel[i]==id1)
		{
			printf("%d %d\n", tar, i);
		}
		
	}
	
	
}