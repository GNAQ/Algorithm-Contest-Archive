#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool ok[200010];
int a[200010];
vector<int> divs[100010];
int n;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Sieve(int val, int lowbnd)
{
	for (auto v: divs[val])
		if (v >= lowbnd) ok[v] = false;
}

void init()
{
	memset(ok, 1, sizeof(ok));
	for (int i = 1; i <= 100001; i++) // that's O(NlogN)
		for (int j = i; j <= 100001; j += i)
			divs[j].push_back(i);
	
}

void DFA(int dir)
{
	int prev = -1, prev2 = -1; // A[prev2] > A[prev] < A[i];
	int vbegin = -1; // v-shape beginpos
	int state = 0; // 0=initial  /  1=up  /  2=up|down  /  3=down  /  4=illegal
	if (a[1] != -1) prev = 1;
	for (int i = 2; i <= n; i++)
	{
		int pval = (prev == -1 ? a[i] : a[prev]);
		if (a[i] == pval || a[i] == -1)
		{
			switch (state)
			{
				case 0:
					state = 1;
					break;
				case 1: case 2:
					state = 2;
					break;
				case 3:
					state = 3;
					break;
			}
		}
		else if (a[i] > pval)
		{
			switch (state)
			{
				case 3: case 4:
					state = 4;
					break;
				case 0: case 1: case 2:
					state = 1;
					break;
			}
		}
		else if (a[i] < pval)
		{
			switch (state)
			{
				case 1: case 2: case 3:
					state = 3;
					break;
				case 0: case 4:
					state = 4;
					break;
			}
		}
		
		if (state != 2 && state != 3) // this is an invalid endpos
		{
			if (dir == 1)
			{
				Sieve(i, i);
			}
			if (dir == -1)
			{
				Sieve(n - i, i);
			}
		}
		
		if (dir == 1 && a[i] != -1 && a[i-1] != -1)
		{
			if (a[i] < a[i - 1])
				Sieve(i - 2, 0);
			if (a[i] > a[i - 1])
				Sieve(i, 0);
		}
		
		if (a[i] != -1) // V shape
		{
			if (prev != -1)
			{
				if (a[prev] > a[i])
					prev2 = prev;
				else if (a[prev] < a[i] && prev2 != -1)
					vbegin = prev2;
			}
			prev = i;
		}
		if (vbegin != -1)
		{
			if (dir == 1)
				Sieve(i, i - vbegin + 1);
			if (dir == -1)
				Sieve(n - i, i);
		}
	
		// printf("i = %d, state = %d, prev = %d, prev2 = %d\n", i, state, prev, prev2);
	}
}

int main()
{
	init();
	readx(n);
	for (int i = 1; i <= n; i++)
		readx(a[i]);
	DFA(1);
	reverse(a+1, a+n+1);
	DFA(-1);
	bool ans = false;
	for (int i = 3; i <= n; i++)
		ans |= ok[i];
	printf("%c\n", "NY"[ans]);
	return 0;
}

/*
Solution:

是经典 DFA + 筛法的杂题，以下抄录自题解：

考虑弱化的情况，如果不计尾段，n 长的数组被均匀分成了 k 段，如何判断？

则我们只需要考虑单段如何判断。构造一个四个状态的 DFA 即可。

状态： 0 开头  /  1 往上走  /  2 往上或往下走  /  3 往下走  /  4 该段不合法

则我们考虑如何筛掉所有不合法的方案。

这包括三种情况。首先，我们不能让任何段包含 V 形。其次，我们不能让一个段的开头包含 \。最次，我们不能让一个段的结束包含 /。

筛去这三种情况，我们还要 de 掉所有的不合法的末尾。这可以通过运行 DFA 并且 de 掉所有非 state = 2 / 3 的位置 i 解决

注意必须要保证 de 掉的长度因子 >= 末尾段的长度。

*/