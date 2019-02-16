#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
#include<set>
#include<map>
typedef long long ll;
using namespace std;

int SG[1000010];
int n,seq[1000010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int min_pri[1000010],pnum[1000010],ptr,phi[100010];
bool nnum[1000010];
void Eular_Shake(int lim)
{
    nnum[0]=nnum[1]=1;
    for (int i=2;i<=lim;i++)
    {
        if (!nnum[i]) { pnum[++ptr]=i; min_pri[i]=i; phi[i]=i-1; }
        for (int j=1;j<=ptr && i*pnum[j]<=lim;j++)
        {
            nnum[i*pnum[j]]=1;
            min_pri[i*pnum[j]]=pnum[j];
            if (!(i%pnum[j])) { phi[i*pnum[j]]=phi[i]*pnum[j]; break; }
			phi[i*pnum[j]]=phi[i]*(pnum[j]-1);
        }
    }
}

int bac[1000010];
void Process(int val)
{
	int vval=val,tmp_SG=0;
	while (val>1)
	{
		bac[min_pri[val]]++;
		tmp_SG=max(tmp_SG,bac[min_pri[val]]);
		val/=min_pri[val];
	}
	SG[vval]=tmp_SG;
	while (vval>1)
	{
		bac[min_pri[vval]]--;
		vval/=min_pri[vval];
	}
}

int main()
{
	// initialization
	Eular_Shake(1000000);
	SG[1]=0;
	// for (int i=2;i<=1000000;i++) Process(i);
	// for (int i=2;i<=1000000;i++) if (!nnum[i]) SG[i]=0;
	
	for (int i=1;i<=20;i++) printf("%d %d\n",i,SG[i]);
	
	readx(n);
	for (int i=1;i<=n;i++) readx(seq[i]);
	
	int ans=0;
	for (int i=1;i<=n;i++) ans=ans^phi[seq[i]];
	
	printf(ans ? "Alice\n" : "Bob\n");
	
}