#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstdlib>
#define ll long long
using namespace std;

int pnum[100010],ptr=0,mu[100010];
bool nnum[100010];
struct _F { int cod,val; } F[100010];
struct _Qris { int cod,a,A,B; } ask[100010];

int fwt[100010];
const int U=100000;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool cmp1(const _F& a1,const _F& a2) { return a1.val<a2.val; }
bool cmp2(const _Qris& a1,const _Qris& a2) { return a1.a<a2.a; }

void Eular_Shake(int upat)
{
	mu[1]=1;
	for (int i=2;i<=upat;i++)
	{
		if (!nnum[i]) { mu[i]=-1; pnum[++ptr]=i; }
		for (int j=1;j<=ptr && i*pnum[j]<=upat;j++)
		{
			nnum[i*pnum[j]]=1;
			if (!(i%pnum[j])) { mu[i*pnum[j]]=0; break; }
			mu[i*pnum[j]]=-mu[i];
		}
	}
}

void Init_F(int upat)
{
	for (int i=1;i<=upat;i++)
	{
		F[i].cod=i;
		for (int j=1;i*j<=upat;j++) F[i*j].val+=i;
	}
	sort(F+1,F+upat+1,cmp1);
}

void upd(int pos,int val)
{
	while (pos<=U)
	{
		fwt[pos]+=val;
		pos+=(pos&(-pos));
	}
}
int qry(int pos)
{
	int ret=0;
	while (pos)
	{
		ret+=fwt[pos];
		pos-=(pos&(-pos));
	}
	return ret;
}

int ans[100010];

int Calc(int _A,int _B,int _chi)
{
	int ret=0;
	for (int l=1,r;l<=_chi;l=r+1)
	{
		r=min(_A/(_A/l),_B/(_B/l));
		ret+=(_A/l)*(_B/l)*(qry(r)-qry(l-1));
	}
	return ret;
}

int main()
{
	Eular_Shake(U); Init_F(U); int Q; readx(Q);
	for (int i=1;i<=Q;i++)
	{
		readx(ask[i].A); readx(ask[i].B); readx(ask[i].a);
		ask[i].cod=i;
	}
	sort(ask+1,ask+Q+1,cmp2);
	
	int maxval=0;
	for (int i=1;i<=Q;i++)
	{
		while (maxval<U && F[maxval+1].val<=ask[i].a)
		{
			maxval++;
			for (int j=1;j*F[maxval].cod<=U;j++) upd(j*F[maxval].cod,mu[j]*F[maxval].val);
		}
		ans[ask[i].cod]=Calc(ask[i].A,ask[i].B,min(ask[i].A,ask[i].B));
	}
	for (int i=1;i<=Q;i++) printf("%d\n",ans[i]&0x7fffffff);
}
