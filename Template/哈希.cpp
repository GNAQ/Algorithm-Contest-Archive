#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;


int ans,n;
char chs[1000010];


const ll mod1=49999991;
const ll mod2=49998437;
const ll baz1=26;
const ll baz2=123;
bool hah1[50000010],hah2[50000010];

//void go_hash(char* chr)
//{
//	ll ret1=0,ret2=0,len=strlen(chr+1);
//	for (int i=1;i<=len;i++) 
//	{
//		ret1=(ret1*baz1+chr[i])%mod1;
//		ret2=(ret2*baz2+chr[i])%mod2;
//	}
//	hah1[ret1]=hah2[ret2]=1;
//}

void chk_hash(char* chr)
{
	ll ret1=0,ret2=0,len=strlen(chr+1);
	for (int i=1;i<=len;i++)
	{
		ret1=(ret1*baz1+chr[i])%mod1;
		ret2=(ret2*baz2+chr[i])%mod2;
	}
	if (hah1[ret1]==1 && hah2[ret2]==1) ans++;
	hah1[ret1]=hah2[ret2]=1;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",chs+1);
		chk_hash(chs);
//		go_hash(chs);
	}
	cout<<n-ans<<endl;
}
