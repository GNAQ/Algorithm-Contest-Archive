#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int Ai[5][1010];
vector<pair<int, int>> mi[1010], ans;
int n;

void Is(int a, int b, int adep, int bdep)
{
	Ai[bdep][b] = Ai[adep][a];
	Ai[adep][a] = 0;
	ans.push_back({a, b});
}

void print(const vector<pair<int, int>> &r, int &emt, int val)
{
	int p1 = r[0].second, p2 = r[1].second, p3 = r[2].second;
	if (r[1].first == 1 && r[2].first == 1) // 1 1 1
	{
		Is(p1, emt, 1, 3); Is(p2, emt, 1, 2); Is(p3, emt, 1, 1);
		Is(p3, p2, 2, 1); Is(p3, p1, 3, 1);
		emt = p3;
	}
	else if (r[1].first == 1 && r[2].first == 2) // 1 1 2
	{
		if (p1 != p3 && p2 != p3)
		{
			Is(p1, emt, 1, 3); Is(p2, emt, 1, 2); Is(p3, p2, 1, 1);
			Is(p3, emt, 2, 1); Is(p3, p1, 3, 1);
			emt = p3;
		}
		else // p1 = p3
		{
			if (p2 == p3) 
				swap(p2, p1);
			Is(p1, emt, 1, 3); Is(p1, emt, 2, 2);
			Is(p2, emt, 1, 1); Is(p1, p2, 3, 1);
			emt = p1;
		}
	}
	else if (r[1].first == 2 && r[2].first == 2) // 1 2 2
	{
		if (p1 != p2 && p1 != p3)
		{
			Is(p1, emt, 1, 3); Is(p2, p1, 1, 1); Is(p2, emt, 2, 2);
			Is(p3, p2, 1, 2); Is(p3, emt, 2, 1); Is(p3, p2, 3, 1);
			emt = p3;
		}
		else // p1 = p3
		{
			if (p1 == p2)
				swap(p2, p3);
			Is(p1, emt, 1, 3); Is(p1, emt, 2, 2); Is(p2, p1, 1, 2);
			Is(p2, emt, 2, 1); Is(p2, p1, 3, 1);
			emt = p2;
		}
	}
	else if (r[1].first == 1 && r[2].first == 3) // 1 1 3
	{
		if (p1 != p3 && p2 != p3)
		{
			Is(p1, emt, 1, 3); Is(p2, emt, 1, 2); Is(p3, p1, 1, 1);
			Is(p3, p2, 2, 1); Is(p3, emt, 3, 1);
			emt = p3;
		}
		else // p1 = p3
		{
			if (p2 == p3)
				swap(p1, p2);
			Is(p2, emt, 1, 3); Is(p1, emt, 1, 2);
			Is(p1, p2, 2, 1); Is(p1, emt, 3, 1);
			emt = p1;
		}
	}
	else if (r[1].first == 2 && r[2].first == 3) // 1 2 3
	{
		if (p1 != p2 && p2 != p3 && p1 != p3)
		{
			Is(p1, emt, 1, 3); Is(p2, p1, 1, 1); Is(p2, emt, 2, 2);
			Is(p3, p2, 1, 2); Is(p3, p2, 2, 1); Is(p3, emt, 3, 1);
			emt = p3;
		}
		else if (p1 == p2)
		{
			Is(p1, emt, 1, 3); Is(p1, emt, 2, 2); Is(p3, p1, 1, 2);
			Is(p3, p1, 2, 1); Is(p3, emt, 3, 1);
			emt = p3;
		}
		else if (p2 == p3)
		{
			Is(p1, emt, 1, 3); Is(p2, p1, 1, 1);
			Is(p2, emt, 2, 2); Is(p2, emt, 3, 1);
			emt = p2;
		}
		else if (p1 == p3)
		{
			Is(p1, emt, 1, 3); Is(p2, p1, 1, 1);
			Is(p2, emt, 2, 2); Is(p1, p2, 1, 2); 
			Is(p1, p2, 2, 1); Is(p1, emt, 3, 1);
			emt = p1;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=3;i++)
	{
		for (int j=1;j<=n;j++)
		{
			scanf("%d", &Ai[i][j]);
			mi[Ai[i][j]].push_back({i, j});
		}
	}
	
	int emt = n + 1;
	for (int loop=1;loop<=n;loop++)
	{
		for (int i=1;i<=n;i++) 
		{
			if (mi[i][0].second == mi[i][1].second && mi[i][1].second == mi[i][2].second)
				continue;
			sort(mi[i].begin(), mi[i].end());
			if ((mi[i][0].first + mi[i][1].first + mi[i][2].first <= 6) && (mi[i][0].first != 2))
			{
				print(mi[i], emt, i);
				break;
			}
		}
		
		for (int i=1;i<=n;i++)
			mi[i].clear();
		for (int i=1;i<=3;i++)
			for (int j=1;j<=n+1;j++)
				mi[Ai[i][j]].push_back({i, j});
	}
	
	if (emt != n + 1)
	{
		Is(n+1, emt, 1, 3);
		Is(n+1, emt, 2, 2);
		Is(n+1, emt, 3, 1);
	}
	
	printf("%d\n", ans.size());
	for (int i=0;i<ans.size();i++)
		printf("%d %d\n", ans[i].first, ans[i].second);
}