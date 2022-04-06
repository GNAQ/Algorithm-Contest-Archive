#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int t, n;
string s;
int sol[200010 * 2];
int lpos[300], nxt[300];

void Solve(int id)
{
	cin >> n >> s;
	
	bool ok = 0, ok1 = 1;
	// 一次
	for (int i=1;i<n;i++)
	{
		if (s[i] < s[i-1])
			ok1 = 0;
	}
	if (ok1)
	{
		for (int i=0;i<n;i++)
			printf("1");
		puts("");
		return;
	}
	
	// 两次
	for (int i=0;i<n;i++)
		lpos[s[i]] = i;
	for (int i=0;i<10;i++)
		for (int j=i+1;j<10;j++)
			if (lpos[j+'0'] != -1)
			{
				nxt[i+'0'] = j+'0';
				break;
			}
	for (int ww=0+'0';ww<9+'0';ww++)
	{
		// init
		for (int i=0;i<n;i++) sol[i] = 0;
		
		int pre = n-1;
		for (int i=n-1;i>=0;i--) 
			if (s[i] <= s[pre])
				pre = i;
		sol[pre] = 1;
		for (int i=pre+1;i<n;i++) 
			if (s[i] <= ww && (s[i] == s[pre] || (nxt[s[pre]] == s[i] && i > lpos[s[pre]])))
			{
				sol[i] = 1;
				pre = i;
			}
		
		for (int i=0;i<n;i++) 
			if (!sol[i] && s[i] >= ww)
			{
				pre = i;
				break;
			}
		sol[pre] = 2;
		for (int i=pre+1;i<n;i++) if (!sol[i])
		{
			if (s[i] >= s[pre])
			{
				sol[i] = 2;
				pre = i;
			}
		}
		int valid = 1;
		for (int i=0;i<n;i++) 
			if (!sol[i]) valid = 0;
		if (valid)
		{
			for (int i=0;i<n;i++)
				printf("%d", sol[i]);
			puts("");
			return;
		}
	}
	
	if (!ok) puts("-");
	return;
}

void Clear()
{
	for (int i=0;i<n+2;i++)
		sol[i] = 0;
	memset(nxt, -1, sizeof(nxt));
	memset(lpos, -1, sizeof(lpos));
}

int main()
{
	cin >> t;
	Clear();
	for (int tt = 1; tt <= t; tt++)
	{
		Solve(tt);
		Clear();
	}
	return 0;
}