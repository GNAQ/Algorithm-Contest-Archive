#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n, ai[1000010];
struct s5n
{
	ll p3, sum4;
	bool operator < (const s5n &b) const
	{
		if (p3 == b.p3) return sum4 > b.sum4;
		return p3 > b.p3;
	}
};
ll ans;
set<s5n> sx;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int BiS(ll val, int Lx)
{
	int L = Lx,R = n, mid, id = -1;
	while (L<=R)
	{
		mid = (L+R)/2;
		if (ai[mid] < val)
		{
			L = mid + 1;
			id = mid;
		}
		else
		{
			R = mid - 1;
		}
	}
	return id;
}

int main()
{
	ans = -1;
	readx(n);
	for (int i=1;i<=n;i++)
		readx(ai[i]);
	sort(ai+1, ai+n+1);
	
	for (int i=6;i<n;i++)
	{
		// update set
		if (ai[i] + ai[i-1] < ai[i-2] + ai[i-3] + ai[i-4] + ai[i-5])
		{
			sx.insert((s5n){ai[i-1], ai[i-2] + ai[i-3] + ai[i-4] + ai[i-5]});
		}
		// pop out illegal
		while ((!sx.empty()) && ai[i] + sx.begin()->p3 >= sx.begin()->sum4)
		{
			sx.erase(sx.begin());
		}
		if (!sx.empty()) // update answer
		{
			ll p1 = BiS(ai[i] + sx.begin()->p3, i + 1);
			if (p1 > i) // has availible P1
			{
				ans = max(ans, ai[p1] + ai[i] + sx.begin()->p3 + sx.begin()->sum4);
			}
		}
	}
	
	printf("%lld\n", ans);
	return 0;
}

/* 
Solution:
  
  首先考虑左边 P1 和右面 P4~P7 都不好下手，一个太简单，一个太复杂。
  所以考虑中间处理 P2+P3。
  考虑如果选定了 P2+P3，则前后该怎么选。因为有 max(ANS) 的限制，所以 P4~P7 应该尽可能大
  所以显然是跟在 P3 的后面，组成一个连续的段，记为 s5[i]。
  
  这样我们可以枚举 P2，自然会得到一组可行的 s5 和一组可行的 P1
  考虑到对 s5 set 排序之后，(P3-P1) 是随着 P3 增大不降的。
  对于答案，只考虑最大的 (P3-P1) 即可。
  考虑到每个 s5 的合法性是随着P2增大连续的。
  所以还是要维护一个 s5 的 set，有出有进即可。
  然后每次取 top ，先检验是否合法，然后二分 P1 即可。
  
*/