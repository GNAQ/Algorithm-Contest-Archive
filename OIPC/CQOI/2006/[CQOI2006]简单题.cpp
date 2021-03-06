#include<cstdio>
#define ll long long
using namespace std;

int n,seq[100010],m;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Upd(int pos)
{
	for (;pos<=n;pos+=(pos&(-pos))) seq[pos]^=1;
}

int Qry(int pos)
{
	int ret=0;
	for (;pos;pos-=(pos&(-pos))) ret^=seq[pos];
	return ret;
}

int main()
{
	readx(n); readx(m); int lx,rx,opt;
	for (int i=1;i<=m;i++)
	{
		readx(opt);
		if (opt==1)
		{
			readx(lx); readx(rx);
			Upd(lx); Upd(rx+1);
		}
		else
		{
			readx(lx);
			printf("%d\n",Qry(lx));
		}
	}
}
