#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int t1[1000010], t2[1000010];
int n; char s[1000010];
int ans[1000010]; // 高精加数组的差分

int LIMT;

void Upd(int t[], int x, int val)
{
	while (x <= LIMT)
	{
		t[x] += val;
		x += (x&(-x));
	}
}

int Qry(int t[], int x)
{
	int ret = 0;
	while (x > 0)
	{
		ret += t[x];
		x -= (x&(-x));
	}
	return ret;
}

int main()
{
	scanf("%d%s", &n, s + 1);
	LIMT = 2 * n + 100;
	int f1 = 0, f2 = 0, zerocnt = 0; // 草泥马树状数组只支持「前」缀和，所以我们 f 的意义要反过来
	for (int i = n; i; i--)
	{
		int slen = n - i + 1;
		f1 += 2 * (s[i] == '1') - 1;
		f2 += 2 * (s[i] == '2') - 1;
		
		if (f1 > 0 || f2 > 0) // 大于半数
		{
			int val = (f1 > 0) ? 1 : 2;
			ans[0] += val;
			ans[max(f1, f2)] -= val;
		}
		else if (slen & 1) // 偶数 -> plus 0  ||  奇数 -> 继续讨论
		{
			if (s[i] == '0' && f1 <= 0 && f2 <= 0) // zeropos right ok
			{
				zerocnt++;
				Upd(t1, f1 + n, 1);
				Upd(t2, f2 + n, 1);
			}
			else // 如果 if 可行，则这是一个好的 zeropos，已经有解
			{
				int tot =  Qry(t1, f1 + n - 1);
					tot += Qry(t2, f2 + n - 1);
				if (tot == zerocnt)
				{
					ans[0] += 1;
					ans[1] -= 1;
				}
			}
		}
	}
	
	for (int i = 1; i <= 2 * n + 100; i++)
		ans[i] += ans[i-1];
	int i = 0;
	while (true)
	{
		if (!ans[i]) break;
		ans[i + 1] += ans[i] / 10;
		ans[i] %= 10;
		i++;
	}
	if (!i && !ans[0])
		puts("0");
	else
	{
		for (int j = i - 1; j >= 0; j--)
			printf("%d", ans[j]);
		puts("");
	}
	return 0;
}

/*
 Solution

	Part.1  考虑每个串可能的答案：+某个数位单一的数 XXX（摩尔投票）  
			或者  
			偶数长 +0   奇数长 +0或者+1（讨论有无 '1' 出现发现不可能 +2）
	Part.2  考虑从右往左处理后缀的奇数长串
	Part.3  考虑 +1 不 +0 的条件：奇数位上有一个 '0'，看其左右侧的 0/1/2 分布
			首先意识到左右的消除是独立的，所以可以扫的时候维护右侧，只处理左侧。
			如果 1 的个数 c1 多于一半，或者 2 的个数 c2 多于一半，则无法消除。答案是 +1
	Part.4  现在只需要处理左侧。问题转变成了枚举左端点，右侧有一堆备选 '0'，如何判断其中有无合法的 '0' 满足 c1 < len / 2
			考虑如何判断。对于 c1 < len / 2 和 c2 < len / 2 这两个条件，它们是独立的，所以可以先只讨论 01 串
			我们对于每个 '0' 都维护一个 f: 初始 f 是 0，每次左移 i，f 可能 +1 也可能 -1，
			最后我们只需要统计 <0 的 f都有几个。
	Part.5  但是这样不好实现。考虑判断的相对性，我们可以记录一个全局变量 f，每次遇到 '0' 位置就把当前 f 的值对应的桶激活。
			最后只需要看一看当前的 f 的左侧（右侧）有没有激活的桶。
			意识到 c1 > len / 2 和 c2 > len / 2 不会同时发生，最后我们不需要把两组答案 and 起来
			只需要统计不满足条件的 '0' 点的个数，如果小于关键 '0' 的个数就说明有 '0' 是合法的。
	Part.6  最后答案的统计是前缀和式的高精度加法，用差分维护即可。
*/