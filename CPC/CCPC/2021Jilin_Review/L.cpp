#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
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

struct __Trie
{
	int v, ch[2];
}t[6000010];
int tcnt, rt;

void Ins(int val)
{
	int pos = rt;
	for (int i=30;i>=0;i--)
	{
		// cout << "POS = " << pos << endl;
		int flag = val & (1<<i);
		if (t[pos].ch[flag]==0)
		{
			tcnt++;
			t[pos].ch[flag] = tcnt;
			pos = tcnt;
			t[pos].v = i;
		}
		else pos = t[pos].ch[flag];
	}
}

void Solve()
{
	rt = 1; tcnt = 1;
	t[1].v=31;
	
	int n; readx(n);
	for (int i=1;i<=n;i++)
	{
		int tmp; readx(tmp);
		Ins(tmp);
	}
	for (int i=1;i<=tcnt;i++)
		if (t[i].v==1)
		{
			if (t[i].ch[0]!=0 && t[i].ch[1]!=0)
			{
				puts("Yes");
				return;
			}
		}
	puts("No");
	return;
}

void Clear()
{
	for (int i=1;i<=tcnt;i++)
		t[i].ch[0]=t[i].ch[1]=t[i].v=0;
	tcnt=1;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	return 0;
}