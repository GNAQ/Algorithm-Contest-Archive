#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAXN=1e5+100;



template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
int dat[MAXN];
int main()
{
	int n;cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&dat[i]);
	sort(dat+1,dat+n+1);
	int opt=-1,step=0;
	for(int i=(n+1)/2;i>=1&&i<=n;i+=opt*step)
	{
		printf("%d ",dat[i]);
		opt*=-1;step++;
	}
}