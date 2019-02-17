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
typedef long long ll;
using namespace std;

ll n,seq[100010],ans;
const ll mod=998244353;

template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll Solve(int l,int r,int pos)
{
	ll ret=r-l+1;
	if (pos>l)
	{
		int lpos=l;
		for (int i=l+1;i<pos;i++) if (seq[i]>seq[lpos]) lpos=i;
		ret+=Solve(l,pos-1,lpos);
	}
	if (pos<r)
	{
		int rpos=pos+1;
		for (int i=pos+2;i<=r;i++) if (seq[i]>seq[rpos]) rpos=i;
		ret+=Solve(pos+1,r,rpos);
	}
	return ret%mod;
}

int main()
{
	freopen("inverse.in","r",stdin);
	freopen("inverse.out","w",stdout);
	
	readx(n);
	for (int i=1;i<=n;i++) readx(seq[i]);
	
	int pos=1;
	for (int i=2;i<=n;i++) if (seq[i]>seq[pos]) pos=i;
	ans=Solve(1,n,pos);
	printf("%lld\n",ans%mod);
	
}