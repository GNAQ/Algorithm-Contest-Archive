#include<stdio.h>
#include<string.h>
#define ll long long

char chs[1000010];
int fail[1000010],len,dep[1000010];
ll ans=1;
const ll mod=1000000007;

void Clear()
{
	memset(fail,0,sizeof fail);
	memset(dep,0,sizeof dep);
	ans=1; len=0;
}

void Get_Fail()
{
	int su=0; dep[1]=1;
	for (int i=2;i<=len;i++)
	{
		while (su && chs[su+1]!=chs[i]) su=fail[su];
		if (chs[su+1]==chs[i]) su++;
		fail[i]=su; dep[i]=dep[su]+1;
	}
	su=0;
	for (int i=2;i<=len;i++)
	{
		while (su && chs[su+1]!=chs[i]) su=fail[su];
		if (chs[su+1]==chs[i]) su++;
		while ((su<<1)>i) su=fail[su];
		ans=(1LL*ans* (dep[su]+1) )%mod;
	}
}

int main()
{
	int T; scanf("%d",&T);
	while (T--)
	{
		Clear();
		scanf("%s",chs+1); len=strlen(chs+1);
		Get_Fail();
		printf("%lld\n",ans);
	}
}
