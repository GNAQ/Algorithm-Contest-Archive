#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

int bac[2000010];
int ai[1000010], bi[1000010];
int blkid[1000010];
int cans[11];

struct Ask
{
	int l, r, id;
	int ans[11];
}as[1000010];

bool cmp(const Ask &a, const Ask &b)
{
	if (blkid[a.l] == blkid[b.l])
		return a.r < b.r;
	return blkid[a.l] < blkid[b.l];
}

// 1: Merge | -1: Split
void MergeRange(int v, int mode)
{
	int l = v, r = v;
	while (bac[r+1] && r-v<=11) r++;
	while (bac[l-1] && v-l<=11) l--;
	
	if (v-l<=10) 
		cans[v-l]-=mode;
	if (r-v<=10)
		cans[r-v]-=mode;
	
	if (r-l+1<=10)
		cans[r-l+1]+=mode;
}

void Solve()
{
	memset(bac, 0, sizeof(bac));
	int n, q;
	scanf("%d%d", &n, &q);
	vector<int> vec;
	for (int i=1;i<=n;i++)
	{
		scanf("%d", &ai[i]);
		vec.push_back(ai[i]);
	}
	
	// 离散化 
	sort(vec.begin(), vec.end());
	int lim = vec.size()-1;
	for (int i=0;i<lim;i++)
		if (vec[i+1]!=vec[i]+1)
			vec.push_back(vec[i]+1);
	sort(vec.begin(), vec.end());
	auto eit = unique(vec.begin(), vec.end());
	for (int i=1;i<=n;i++)
		bi[i] = lower_bound(vec.begin(), eit, ai[i]) 
			- vec.begin() + 1;
	
	for (int i=1;i<=n;i++)
		printf("%d%c", bi[i], " \n"[i==n]);
	
	// 对询问分块
	int blksz = sqrt(q);
	for (int i=1;i<=q;i++)
		blkid[i]=1+(i/blksz);
	for (int i=1;i<=q;i++)
	{
		// readx(as[i].l); readx(as[i].r);
		scanf("%d%d", &as[i].l, &as[i].r);
		as[i].id = i;
	}
	sort(as+1, as+q+1, cmp);
	
	int lx = as[1].l, rx = as[1].l - 1;
	int al, ar;
	memset(cans, 0, sizeof(cans));
	
	// 做莫队
	for (int qi=1;qi<=q;qi++)
	{
		al = as[qi].l; ar = as[qi].r;
		
		while (rx < ar)
		{
			rx++;
			if (!bac[bi[rx]])
			{
				MergeRange(bi[rx], 1);
			}
			bac[bi[rx]]++;
		}
		while (rx > ar)
		{
			bac[bi[rx]]--;
			if (!bac[bi[rx]])
			{
				MergeRange(bi[rx], -1);
			}
			rx--;
		}
		
		while (lx > al)
		{
			lx--;
			if (!bac[bi[lx]])
			{
				MergeRange(bi[lx], 1);
			}
			bac[bi[lx]]++;
		}
		while (lx < al)
		{
			bac[bi[lx]]--;
			if (!bac[bi[lx]])
			{
				MergeRange(bi[lx], -1);
			}
			lx++;
		}
		
		for (int k=1;k<=10;k++)
			as[qi].ans[k] = cans[k];
	}
	
	sort(as+1, as+q+1, [](const Ask &a, const Ask &b) { return a.id < b.id; } );
	for (int i=1;i<=q;i++)
	{
		for (int j=1;j<=10;j++)
			printf("%d", (as[i].ans[j]+5)%10);
		puts("");
	}
}

int main()
{
	// int T; readx(T);
	int T; scanf("%d", &T);
	while (T--)
	{
		Solve();
	}
	
}