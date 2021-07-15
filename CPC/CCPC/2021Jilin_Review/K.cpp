#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
typedef long long ll;
using namespace std;

int n, a[100010], b[100010];

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
	readx(n); int ans = 0;
	for (int i=1;i<=n;i++) readx(a[i]);
	for (int i=1;i<=n;i++) readx(b[i]);
	
	map<int, int> mapx;
	for (int i=1;i<=n;i++)
		mapx[a[i]]++;
	
	for (int i=1;i<=n;i++)
	{
		map<int, int>::iterator iter = mapx.upper_bound(b[i]);
		
		if (iter != mapx.end() && (*iter).second>0)
		{
			(*iter).second--;
			if ((*iter).second == 0) mapx.erase(iter);
			ans++;
		}
	}
	
	cout<<ans<<endl;
	return 0;
}