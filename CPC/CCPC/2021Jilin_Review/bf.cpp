#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
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

bool OK(vector<int> &a)
{
	if (a[0]!=1) return false;
	for (int i=1;i<a.size();i++) if (a[i]!=a[i-1]+1) return false;
	return true;
}

int Solve(int n, int m)
{
	// cout << "Solve" << n << " " << m << endl;
	
	vector<int> a, b;
	for (int i=1;i<=n*m;i++)
		a.push_back(i);
	
	int ans = 0;
	while (1)
	{
		for (int i=1;i<=m;i++)
			for (int j=1;j<=n;j++)
				b.push_back(a[(j-1)*m+i -1]);
		
		// for (auto v:b) printf("%d ", v);
		// puts("");
		
		ans++;
		if (OK(b)) return ans;
		a=b;
		b.clear();
	}	
}

int phi[100010]={0};
int ctr1,pnum[100010]={0};
bool vis[100010]={0};
inline void PhiShake(int lim)
{
	phi[1]=1;
	for (int i=2;i<=lim;i++) phi[i]=i-1;
	
	for (int i=2;i<=lim;i++)
	{
		if (!vis[i]) pnum[++ctr1]=i;
		for (int j=1;j<=ctr1 && i*pnum[j]<=lim;j++)
		{
			vis[i*pnum[j]]=true;
			if (!(i%pnum[j]))
			{
				phi[i*pnum[j]]=phi[i]*pnum[j];
				break;
			}
			else phi[i*pnum[j]]=phi[i]*(pnum[j]-1);
		}
	}
}

ll fastpow(ll an, ll p, ll mod)
{
	ll ret = 1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

bool Check(int k, int n, int m)
{
	return fastpow(n,k,n*m-1)==1;
}

int main()
{
	PhiShake(10000);
	int n, m;
	
	for (int i=2;i<=15;i++)
	{
		for (int j=2;j<=15;j++)
		{
			printf("%3d ", Solve(i,j));
		}
		cout<<endl;
	}
	cout<<endl;
	
	for (int i=2;i<=15;i++)
		for (int j=2;j<=15;j++)
		{
			int ans = phi[i*j-1], tmp = phi[i*j-1];
			int lim = sqrt(ans);
			for (int w=2;w<=lim;w++)
				if (!(tmp%w))
				{
					while (!(tmp%w)) tmp/=w;
					while ( !(ans%w) && Check(ans/w, i, j) ) ans/=w;
					lim=sqrt(tmp);
				}
			if (tmp>1 && Check(ans/tmp, i, j)) ans/=tmp;
			 
			printf("%3d%c", ans, " \n"[j==15]);
		}
	
	cout << Solve(2,26) << endl;
	
}