#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int f[3010][3010], f2[3010][3010];
int h[3010], n;
int r[3010], l[3010];

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=n;i++)
		scanf("%d", &h[i]);
	
	for (int i=1;i<=n;i++)
	{
		l[i] = r[i] = i;
		while (l[i] && h[l[i]-1] > h[i]) 
			l[i]--;
		while (r[i] < n && h[r[i]+1] > h[i])
			r[i]++;
	}
	
	for (int i=1;i<=n;i++)
	{
		for (int j=l[i];j<=r[i];j++)
		{
			
		}
	}
	
}