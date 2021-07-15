#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
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

char ch[100010];


void Solve()
{
	scanf("%s", ch+1); 
	int len = strlen(ch+1);
	
	ll ans = 0;
	for (int i=1;i<=len;i++)
	{
		int cnt = 1;
		while (i<len && ch[i]==ch[i+1])
			{ i++; cnt++; }
		ans += 1LL*cnt*(cnt+1)/2;
	}
	cout << ans << endl;
}

void Clear()
{
	
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
	
	
}