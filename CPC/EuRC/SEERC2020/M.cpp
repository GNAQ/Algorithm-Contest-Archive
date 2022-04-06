#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m, k;
int ans[500010];

int main()
{
	scanf("%d%d%d", &n, &k, &m);
	int u, v;
	for (int i=1;i<=m;i++)
		scanf("%d%d", &u, &v);
	int a;
	for (int i=1;i<=n*k;i++)
	{
		scanf("%d", &a);
		printf("%d%c", ++ans[a], " \n"[i==n*k]);
	}
}