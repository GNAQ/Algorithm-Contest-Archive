#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<ctime>
typedef long long ll;
using namespace std;

char ch[1500006];
int cnt[26][1500006];
int n;
ll hs[1500006];
const ll ww = 133, mod = 1000000007;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an, ll p)
{
	ll ret = 1;
	for (;p;p>>=1, an=an*an%mod) if (p&1) ret = ret*an%mod;
	return ret;
}

bool OK(int k, int x)
{
	for (int i=x;i<x+k;i++)
	{
		ll tmp=(hs[x+k-1]-hs[i-1]+mod)%mod + (hs[i-1]-hs[x-1])*fastpow(ww, k);
		tmp%=mod;
		tmp+=mod;
		tmp%=mod;
		
		// cerr<<"%"<<tmp<<" "<<hs[k]*fastpow(ww, i-1)%mod<<endl;
		
		if(tmp==hs[k]*fastpow(ww, i-1)%mod)
		{
			return true;
		}
	}
	return false;
}

void Init()
{
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<26;j++)
		{
			cnt[j][i]=cnt[j][i-1];
		}
		cnt[ch[i]-'a'][i]++;
		
		hs[i]=(hs[i-1]+fastpow(ww,i)*ch[i])%mod;
	}
	
	// for (int i=1;i<=n;i++) printf("%lld ", hs[i]);
	// printf("\n");
}

void Solve()
{
	scanf("%d", &n);
	scanf("%s", ch+1);
	
	Init();
	
	int ans = 0;
	for (int i=2;i<n;i++) if (n%i==0)
	{		
		int flag = 1;
		for (int j=i+1;j<=n;j+=i)
		{
			for (int k=0;k<26;k++)
			{
				if (cnt[k][i] != (cnt[k][j+i-1]-cnt[k][j-1]) )
					flag = 0;
			}
		}
		
		if (flag)
		{
			// cerr<<"OK i = "<<i<<endl;
			
			vector<int> ord;
			for (int j=i+1;j<=n;j+=i) ord.push_back(j);
			random_shuffle(ord.begin(), ord.end());
			
			for (auto p: ord)
			{
				// cerr<<"!!"<<p<<endl;
				
				if (!OK(i, p)) 
				{
					flag = 0;
					break;
				}
			}
		}
		
		if (flag) ans = 1;
	}
	
	if (ans == 1) printf("1\n");
	else printf("2\n");
}

void Clear()
{
	memset(ch, 0, sizeof(ch));
}

int main()
{
	srand(time(0));
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
}