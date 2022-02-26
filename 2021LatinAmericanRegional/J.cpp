#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXKW = 43046726;

ll n, k;
ll pres[MAXKW + 100];
vector<int> lim, rec[100010], qry;
int cnt;
ll upd_w; 

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int conv(const vector<int> &l)
{
	int ret = 0;
	for (int i = k; i >= 1; i--)
		ret = ret * 9 + l[i];
	return ret;
}

void DFS_UPD(const vector<int> &lim, vector<int> &now, int lvl)
{
	if (lvl == k + 1)
	{
		// cout << "ADD " << conv(now) << endl; 
		pres[conv(now)] += upd_w;
		return;
	}
	for (int i = 0; i <= lim[lvl]; i++)
	{
		now[lvl] = i;
		DFS_UPD(lim, now, lvl + 1);
	}
}

int main()
{	
	readx(n); readx(k);
	lim.resize(k+1);
	qry.resize(k+1);
	for (int i=1;i<=n;i++)
	{
		char op[1]; int val;
		vector<int> tmp(k + 1, 0);
		
		scanf("%s", op);
		if (op[0] == 'C')
		{
			rec[++cnt].resize(k+1);
			int r; readx(r);
			for (int j=1;j<=r;j++)
			{
				readx(val);
				rec[cnt][val]++;
			}
			
			upd_w = 1;
			DFS_UPD(rec[cnt], tmp, 1);
		}
		if (op[0] == 'D')
		{
			int r; readx(r);
			
			upd_w = -1;
			DFS_UPD(rec[r], tmp, 1);
		}
		if (op[0] == 'J')
		{
			fill(qry.begin(), qry.end(), 0);
			int r; readx(r);
			for (int j=1;j<=r;j++)
			{
				readx(val);
				qry[val]++;
			}
			
			// printf("\t\t %lld\n", pres[conv(qry)]);
			printf("%lld\n", pres[conv(qry)]);
		}
	}
}

/*
- Solution: (3)
	
	所以这题是一个反复读错题意的过程。
	
	问题限制的是最多有 8 个贡献，也就是 sum of val of 8 dimentions <= 8
	
	考虑维护一个 8 维前缀和数组，根据均值不等式，发现每次更新它的代价不会高于 2^8 = 256
	
	所以我们可以在 O(nk*256) 的复杂度内完成题目。
	
*/

/*
- Solution: (2)
	
	这个傻逼读错题意了，一看值域是 <=8
	
	麻了！
	
	……
	
*/

/*
- Solution:
	
	考虑高位偏序不好用 CDQ 分治做，于是一转分块。
	
	尝试一下对各个量分块，最后发现可以对值域分块。
	
	下面对单一维度进行考虑，按照值排序后，分块，每块整合进一个 bitset。
	
	然后处理好这 sqrt(W) 个 bitset 的前缀 / 后缀或（其实是加法……）。
	
	这里也可以压到一步完成。
	
	之后对于每个询问，在每一个单一维度下，做取前缀+O(sqrt(W)) 的块内暴力。
	
	然后把 d 个 sqrt(W) 的 bitset 全都 AND 起来即可。
	
	总复杂度 O(nsqrt(W)d)
	
*/