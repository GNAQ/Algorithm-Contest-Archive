/* 
白写了，寄
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
int a[100010], inval[100010], c[100010];
int h1r[100010], same[100010];
int bel[100010];

// 不能处理全 -1
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	// init
	int pr1 = 1, pr2;
	while (a[pr1] == -1) pr1++;
	pr2 = pr1 + 1;
	while (a[pr2] == -1) pr2++;
	for (int i = pr2 + 1; i <= n; i++) if (a[i] != -1)
	{
		if (a[pr1] < a[pr2] < a[i] || a[pr1] > a[pr2] > a[i])
		{
			for (int j = pr1 + 1; j < i; j++)
				inval[j] = 1;
		}
		pr1 = pr2;
		pr2 = i;
	}
	
	// get C[]
	int m = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!inval[i] && a[i] != -1) 
		{
			m++;
			while (i < n && a[i + 1] == -1)
			{
				h1r[m]++;
				i++;
			}
			c[m] = a[i];
		}
	}
	if (a[1] == -1) h1r[0] = 1;
	while (a[h1r[0] + 1] == -1)
		h1r[0]++;
	
	// mark continous subseqs
	for (int i = 2; i < m; i++)
		if (c[i] == c[i-1] && c[i] == c[i+1])
			for (int j = i-1; c[j] == c[i]; j++)
				same[j] = 1;
	
	for (int i=1;i<=m;i++)
	{
		printf("%d%c", c[i], " \n"[i==m]);
		printf("%d%c", h1r[i], " \n"[i==m]);
		printf("%d%c", same[i], " \n"[i==m]);
	}
	
	// find illegal ranges
	// 这里只有 3 种情况：[i] > [i+1] 或者 [i] < [i+1] 或者 [i] = [i+1]
	bool ans = 1;
	int arr_cnt = 0;
	int sta = 1; // next part is [1 2 3]
	for (int i=1;i<=m;i++) if (!same[i])
	{
		if (!ans) break;
		if (sta == 1)
		{
			arr_cnt++;
			if (i == m) // spc
			{
				if (h1r[i-1]+h1r[i] <= 1)
					ans = 0;
				continue;
			}
			if (c[i] > c[i+1])
			{
				if (h1r[i-1] || h1r[i])
				{
					sta = 1;
					i++;
				}
				else
				{
					ans = 0;
					break;
				}
			}
			if (c[i] < c[i+1])
			{
				sta = 2;
			}
			if (c[i] == c[i+1])
			{
				if (h1r[i-1] + h1r[i] + h1r[i+1] < 1)
				{
					ans = 0;
					break;
				}
				else
				{
					bel[i] = bel[i+1] = arr_cnt;
					i++;
					if (h1r[i-1] + h1r[i] == 0)
						h1r[i+1]--;
				}
			}
		}
		else if (sta == 2)
		{
			if (i == m) // spc
			{
				if (h1r[i-1]+h1r[i] == 0)
					ans = 0;
				continue;
			}
			if (c[i] < c[i+1])
			{
				// ? is it really happens?
			}
			if (c[i] >= c[i+1])
			{
				sta = 3;
				bel[i] = arr_cnt;
			}
		}
		else // sta == 3
		{
			bel[i] = arr_cnt;
			sta = 1;
		}
	}
	
	// calc equal seqs
	// wait, we don't need to care about them anymore
	printf("%c\n", "NY"[ans]);
}

/*
-> Solution

考虑一个显然的性质
就是在长的上升 / 下降段内的 -1 毫无意义。
那么我们先去掉 -1 做一遍，然后贪心处理：
如果 b[i-1] < b[i] < b[i+1]，这段的 -1 和 b[i] 一起直接扔了。
然后形成一个 c[]，对它贪心：每次利用 -1 填出小大小三段即可

注意题目要求是非减 / 增
所以问题在于：连续的平段也可以优化掉吗？不一定
这是最麻烦的。也就是单独 [3 3 3] / [3 3 3 3] 的情况。

实际上也不麻烦。我们提前处理出来，求的时候跳过。
它又有 4 种情况：
1. 被左面的段占用，那中间可以全归左边
2.  右面       ，
3. 两边，
4. 独立，这个时候如果是 2 连段直接没救，否则就可以跳出来。这里我们不标二连段就行了，只标更大的。

我们是不是还要考虑 3 3 -1 3 3 -1 -1 3 的问题？太恶心了吧
*/

