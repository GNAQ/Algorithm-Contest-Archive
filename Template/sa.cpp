#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
#include<set>
#include<map>
typedef long long ll;
using namespace std;

int n,str[1000010];
char str1[1000010];

template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SA
{
	int sa[1000010],rk[1000010],high[1000010];
	int fst[1000010],snd[1000010],tmp[1000010],bac[1000010];
	int setx[1000010],chr[1000010];
	
	void New(int* str,int len)
	{
		memcpy(setx,str,sizeof(int)*(len+2));
		sort(setx+1,setx+len+1); int CST=unique(setx+1,setx+len+1)-(setx+1);
		for (int i=1;i<=len;i++) 
			chr[i]=lower_bound(setx+1,setx+CST+1,str[i])-setx;
		
		for (int i=1;i<=len;i++) bac[chr[i]]++;
		for (int i=1;i<=len;i++) bac[i]+=bac[i-1];
		for (int i=1;i<=len;i++) rk[i]=bac[chr[i]-1]+1;
		
		for (int w=1;w<=len;w<<=1)
		{
			for (int i=1;i<=len;i++) fst[i]=rk[i];
			for (int i=1;i<=len;i++) snd[i]=(i+w>len) ? 0 : rk[i+w];
			
			memset(bac,0,sizeof(int)*(len+2));
			for (int i=1;i<=len;i++) bac[snd[i]]++;
			for (int i=1;i<=len;i++) bac[i]+=bac[i-1];
			for (int i=1;i<=len;i++) tmp[len-(--bac[snd[i]])]=i;
			
			memset(bac,0,sizeof(int)*(len+2));
			for (int i=1;i<=len;i++) bac[fst[i]]++;
			for (int i=1;i<=len;i++) bac[i]+=bac[i-1];
			for (int j=1,i;j<=len;j++) { i=tmp[j]; sa[bac[fst[i]]--]=i; }
			
			int uniq=1,last=0;
			for (int j=1,i;j<=len;j++)
			{
				i=sa[j];
				if (!last) rk[i]=1;
				else if (fst[i]==fst[last] && snd[i]==snd[last]) { uniq=0; rk[i]=rk[last]; }
				else rk[i]=rk[last]+1;
				last=i;
			}
			if (uniq) break;
		}
		
		for (int i=0,k=0;i<=len;i++)
		{
			if (rk[i]==1) k=0;
			else
			{
				if (k>0) k--;
				int j=sa[rk[i]-1];
				while (i+k<=len && j+k<=len && chr[i+k]==chr[j+k]) k++;
			}
			high[rk[i]]=k;
		}
	}
};

int main()
{
	scanf("%s",str1+1);
	n=strlen(str1+1); for (int i=1;i<=n;i++) str[i]=str1[i];
	
	SA::New(str,n);
	
	for (int i=1;i<=n;i++) printf("%d%c",SA::sa[i]," \n"[i==n]);
}