#include<bits/stdc++.h>
using namespace std;

char t[10010],ans[10010];
char s[1010][1010];
double xi[1010],ansv;
int n,m,slen[1010];

bool Match(char* src,char* dst,int len)
{
	for (int i=1;i<=len;i++) if (src[i]!=dst[i]) return false;
	return true;
}

void Upd()
{
	double val=0;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n-slen[i]+1;j++) 
			if (Match(t+j-1,s[i],slen[i])) val+=xi[i];
	if (
}

char seq[1010];
void DFS(int now)
{
	if (now==n+1)
	{
		Upd();
		return;
	}
	
}

int main()
{
	scanf("%d%d",&n,&m); ansv=-2000000000;
	scanf("%s",t+1);
	for (int i=1;i<=m;i++)
	{
		scanf("%s%lf",s[i]+1,xi[i]);
		xi[i]=log2(xi[i]); slen[i]=strlen(s[i]+1);
	}
	
	DFS(1);
	
}
