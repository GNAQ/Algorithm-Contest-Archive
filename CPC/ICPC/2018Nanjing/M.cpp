#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=1e6+100;
const int base=233;
const int mod=1e9+7;
char s[MAXN],t[MAXN];
int n,m,ans[MAXN];
unsigned int h[MAXN][2],pre_h[MAXN],qpow[MAXN];
int get_hash(int l,int r,int opt,int rev)
{
	if(l>r) return -1;
	if(rev==1) return pre_h[l]-pre_h[r+1]*qpow[r-l+1];
	else return h[r][opt]-h[l-1][opt]*qpow[r-l+1];
}
int main()
{
	scanf("%s",s+1);scanf("%s",t+1);
	n=strlen(s+1);m=strlen(t+1);
	qpow[0]=1;
	for(int i=1;i<=max(n,m);i++)	
		qpow[i]=qpow[i-1]*base;
	for(int i=1;i<=n;i++)
		h[i][0]=h[i-1][0]*base+s[i];
	for(int i=n;i>=1;i--)
		pre_h[i]=pre_h[i+1]*base+s[i];
	for(int i=1;i<=m;i++)
		h[i][1]=h[i-1][1]+qpow[i-1]*t[i];
	for(int i=1;i<=n;i++)
	{
		int l=1,r=min(i,n-i+1),Ans;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(get_hash(i-mid+1,i,0,0)==get_hash(i,i+mid-1,0,1))
			{
				l=mid+1;
				Ans=mid;
			}
			else r=mid-1;
		}
		ans[i-Ans]++;
		ans[i]--;
		l=0;r=min(i,n-i);
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(get_hash(i-mid+1,i,0,0)==get_hash(i+1,i+mid,0,1))
			{
				l=mid+1;
				Ans=mid;
			}
			else r=mid-1;
		}
		ans[i-Ans]++;
		ans[i]--;
	}
	for(int i=1;i<=n;i++)
		ans[i]+=ans[i-1];
	LL res=0;
	for(int i=1;i<=n;i++)
	{
		int l=0,r=min(m,i),Ans=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(get_hash(i-mid+1,i,0,0)==get_hash(1,mid,1,0))
			{
				l=mid+1;
				Ans=mid;
			}
			else r=mid-1;
		}
		res+=1ll*Ans*ans[i];
	}
	printf("%lld\n",res);
}