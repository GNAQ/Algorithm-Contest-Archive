#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
typedef long long ll;
using namespace std;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int ma[100010][17],n,m;
int ans, minv,maxv;
int ok[100010];

struct _Val
{
	int v,x,y;
}val[100010*15];
int cnt;

void Clear()
{
	ans=0;
	cnt=0;
	for (int i=1;i<=n;i++) ok[i]=0;
}

bool cmp(_Val a, _Val b)
{
	return a.v>b.v;
}

void Print(int p)
{
	for (int i=1;i<=m;i++) 
	{
		if ((1<<i)&ok[p])
			printf("1 ");
		else
			printf("0 ");
	}
	putchar('\n');
}

int dp[100010];

bool Judge(int aa)
{
	int cur = 0, px, py;
	
	for (int i=1;i<=n;i++) ok[i]=0;
	
	while ((cur < cnt) && (val[cur+1].v>=aa))
	{
		cur++; px=val[cur].x; py=val[cur].y;
		ok[px]+=(1<<py);
	}
	
//	cout<<"Judge "<<aa<<endl;
//	for (int i=1;i<=n;i++) Print(i);
	
	int std=0;
	for (int i=1;i<=m;i++) std+=(1<<i);
	
	for (int i=0;i<=std;i++) dp[i]=0;
	for (int i=1;i<=n;i++) dp[ std-ok[i] ]=1;
	for (int i=0;i<=std;i++)
		for (int w=1;w<=m;w++) if ((i&(1<<w)) == 0)
			dp[i+(1<<w)] += dp[i];
	
	for (int i=1;i<=n;i++) if (dp[ok[i]]!=0)
		return true;
	return false;
}

void Solve()
{
	sort(val+1,val+cnt+1,cmp);
	
	int l=minv,r=maxv;
	while (l<=r)
	{
		int mid = (l+r)/2;
		if (Judge(mid))
		{
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
	}
	return;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		readx(n); readx(m); minv=2*1e9; maxv=-1;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				readx(ma[i][j]);
				minv=min(minv, ma[i][j]);
				maxv=max(maxv, ma[i][j]);
				cnt++;
				val[cnt].v=ma[i][j];
				val[cnt].x=i;
				val[cnt].y=j;
			}
		
		Solve();
		
		int aans;
		for (int i=1;i<=n;i++)
		{
			aans=ma[i][1];
			for (int j=2;j<=m;j++) aans=min(aans, ma[i][j]);
			ans=max(ans,aans);
		}
		
		printf("%d\n", ans);
		Clear();
	}
	
}
