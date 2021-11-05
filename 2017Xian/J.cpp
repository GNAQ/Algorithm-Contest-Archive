#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9+7;

string ss[7];

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
	for (;p;p>>=1, an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

ll dp[110][80];

int main()
{
	ll C = 1;
	for (int i=95;i>80;i--) 
		C = C * i % mod;
	for (int i=5;i>1;i--)
		C = C * fastpow(i, mod-2) % mod * fastpow(i, mod-2) % mod;
	// cout << C << endl;
	
	while (cin >> ss[1])
	{
		memset(dp, 0, sizeof(dp));
		for (int i=2;i<=5;i++)
			cin >> ss[i];
		
		dp[0][0]=1;
		for (int i=1;i<=100;i++)
		{
			for (int s1 = 0; s1 < 32; s1++)
			{
				dp[i][s1] = (dp[i][s1] + dp[i-1][s1]) % mod;
				for (int j=1;j<=5;j++) if (ss[j][i-1] == '1')
					if ( (s1>>(j-1)) & 1 )
						dp[i][s1] = (dp[i][s1] + dp[i-1][s1^(1<<(j-1))]) % mod;
			}
		}
		
		ll ans = C * dp[100][31] % mod;
		
		cout << ans << endl;
	}
	
}