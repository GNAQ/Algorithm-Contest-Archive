#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1145140019;

ll ctr1,pnum[200010];
bool vis[200010];

ll CalcF(ll x)
{
	ll ret = 0;
	for (ll l = 1, r = 0; l <= x; l = r + 1)
	{
		r = x / (x / l);
		ret += (x / l) * (r - l + 1);
	}
	return ret;
}

void Sieve(ll li)
{
	for (int i=2;i<=li;i++)
	{
		if (!vis[i]) pnum[++ctr1]=i;
		for (int j=1;j<=ctr1 && i*pnum[j]<=li;j++)
		{
			vis[i*pnum[j]]=true;
			if (!(i%pnum[j]))
				break;
		}
	}
}

ll n, lim;
ll blkcnt, hash1[201000], hash2[201000], f[201000];
ll blkv[201000];

void Solve()
{
	scanf("%lld", &n);
	lim = sqrt(n);
	
	for (ll l=1, r=0; l<=n; l=r+1)
	{
		r = n / (n / l);
		ll v = n / l;
		blkv[++blkcnt] = v;
		if (v <= lim)
		{
			hash1[v] = blkcnt;
		}
		else
		{
			hash2[n/v] = blkcnt;
		}
		f[blkcnt] = v - 1; // 筛 1...n/i 质数个数
	}
	
	for (int j=1;j<=ctr1;j++) // primes
	{
		ll pri = pnum[j];
		for (int i=1; i<=blkcnt && pri*pri <= blkv[i]; i++)
		{
			ll blkid = blkv[i] / pri, fid;
			if (blkid <= lim)
			{
				fid = hash1[blkid];
			}
			else
			{
				fid = hash2[n / blkid];
			}
			f[i] = (f[i] - (f[fid] - (j-1)) + 2*mod ) % mod;
		}
	}
	
	ll ans = 0;
	for (int i=1; i<blkcnt; i++)
	{
		ll len = f[i]-f[i+1];
		if (len)
			ans = (ans + len * CalcF(n / blkv[i]) % mod ) % mod;
	}
	
	cout << ans << endl;
}

void Clear()
{
	blkcnt = 0;
}

int main()
{
	Sieve(200004);
	
	int T; scanf("%d", &T);
	while (T--)
	{
		Solve();
		Clear();
	}
}