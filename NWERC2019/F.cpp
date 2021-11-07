#include<bits/stdc++.h>

using namespace std;

map<int,int>mp;
vector<pair<int,int> >ans;
vector<int>ansval;

int fa[200010];

int find(int x)
{
	return fa[x]?fa[x]=find(fa[x]):x;
}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int m;
		cin>>m;
		for(int j=1;j<=m;j++)
		{
			int tmp;
			cin>>tmp;
			if(mp[tmp])
			{
				int temp=mp[tmp];
				int u,v;
				if((u=find(temp))!=(v=find(i)))
				{
					fa[u]=v;
					mp[tmp]=i;
					ans.emplace_back(make_pair(i,temp));
					ansval.emplace_back(tmp);
				}
			}
			else mp[tmp]=i;
		}
	}
	if(ans.size()==n-1) 
	{
		for(int i=0;i<ans.size();i++)
		{
			cout<<ans[i].first<<' '<<ans[i].second<<' '<<ansval[i]<<"\n";
		}
	}
	else cout<<"impossible\n";
}