#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int bas=233;
const int mod = 1e8+9;

int nowsec[110];
int powbas[110];
int l[20],r[20];

int nowval;

int ans = 0;

set<vector<int>> sx;

void dfs(int now)
{
	if(now==0) 
	{
		ans++;
		return;
	}
	int u=l[now],v=r[now];
	
	if(nowsec[u]>nowsec[v]) return;
	dfs(now-1);
	swap(nowsec[u],nowsec[v]);
	dfs(now-1);
	swap(nowsec[u],nowsec[v]);
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,k,q;
		cin>>n>>k>>q;
		for(int i=1;i<=k;i++) cin>>l[i]>>r[i];
		nowval=0;
		
		{
			vector<int> bas, now;
			bas.resize(n+1, 0);
			for (int i=1;i<=n;i++)
				bas[i] = i;
			
			for (int i=1;i<=n;i++)
			{
				now = bas;
				for (int j=i-1;j>=1;j--)
				{
					swap(now[j], now[j+1]);
					sx.insert(now);
				}
				now = bas;
				for (int j=i+1;j<=n;j++)
				{
					swap(now[j], now[j-1]);
					sx.insert(now);
				}
			}
			sx.insert(bas);
		}
		
		for (auto v: sx)
		{
			for (int i=1;i<v.size();i++)
				nowsec[i] = v[i];
			
			int pans = ans;
			dfs(k);
			cout << ans - pans << endl;
		}
		cout << ans << '\n';
		ans = 0;
		sx.clear();
	}
}