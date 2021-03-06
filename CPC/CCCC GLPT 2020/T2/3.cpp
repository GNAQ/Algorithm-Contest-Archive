#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
using namespace std;

int a[1010],cnt;
int fa[1010],val[1010];
vector<int> to[1010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	to[fx].push_back(tx);
	fa[tx]=fx;
}

void Back(int u)
{
	if (to[u].size()==2)
	{
		int a=to[u][0],b=to[u][1];
		if (a>b) swap(a,b);
		Back(a); Back(b);
	}
	else if (to[u].size()==1)
	{
		Back(to[u][0]);
	}
	cnt++;
	val[u]=a[cnt];
}

int main()
{
	int n; readx(n);
	for (int i=1;i<=n;i++)
	{
		Is(i>>1,i);
	}
	cnt=0; 
	for (int i=1;i<=n;i++) readx(a[i]);
	
	Back(1);
	for (int i=1;i<=n;i++) printf("%d%c", val[i], " \n"[i==n]);
	
	return 0;
}
