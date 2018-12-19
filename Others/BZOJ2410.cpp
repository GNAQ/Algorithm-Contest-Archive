#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long 
using namespace std;

int n,k,t;
int seq[100010];

inline char gc()
{
    static char BUFF[1000000],*S=BUFF,*T=BUFF;
    return S==T&&(T=(S=BUFF)+fread(BUFF,1,1000000,stdin),S==T)?EOF:*S++;
}
inline void readx(int& x)
{
    x=0; register char ch=0;
    while (ch<'0' || ch>'9') ch=gc();
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=gc(); }
}

int sg[122]; bool vis[13];
void GetSG()
{
	sg[1]=1;
	for (int i=2;i<=120;i++)
	{
		memset(vis,0,sizeof vis);
		vis[sg[i-2]]=1;
		for (int a=0;a<=i-3;a++) vis[sg[a]^sg[i-a-3]]=1;
		for (int j=0;;j++) if (!vis[j]) { sg[i]=j; break; }
	}
}
int SG(int x)
{
	if (x<=120) return sg[x];
	x%=34; x+=68; return sg[x];
}

int K1()
{
	seq[n+2]=0; seq[n+3]=1; seq[0]=1; seq[1]=0; int ret=0;
	for (int i=0;i<=n+3;i++)
	{
		if (!seq[i])
		{
			int pos=i;
			while (!seq[pos+1]) pos++;
			if (pos-i>1) ret^=SG(pos-i-1);
			i=pos;
		}
	}
	return ret;
}

int K2()
{
	int ret=0; seq[n+2]=1;
	if (!seq[2])
	{
		int pos=2; while (!seq[pos+1]) pos++;
		ret^=pos-1;
	}
	for (int i=3;i<=n+1;i++) if (!seq[i])
	{
		int pos=i;
		while (!seq[pos+1]) pos++;
		
		if (pos==n+1) ret^=(pos-i+1);
		else if (seq[i-1]==seq[pos+1]) ret^=0;
		else ret^=1;
		i=pos;
	}
	return ret;
}

int main()
{
    readx(t); GetSG();
    while (t--)
    {
        readx(n); readx(k); int ans=0;
        for (int i=2;i<=n+1;i++) readx(seq[i]);
        
        if (k>2)
        {
        	for (int i=2;i<=n+1;i++) ans+=(seq[i]==0);
        	if (ans%2) printf("y\n");
        	else printf("n\n");
        	continue;
		}
		else if (k==1) ans=K1();
		else ans=K2();
		if (ans) printf("y\n");
		else printf("n\n");
    }
}
