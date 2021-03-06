#include<bits/stdc++.h>

using namespace std;

struct Node
{
	int pos,tp;
	
	bool operator<(const Node &other)const
	{
		return other.pos==pos?tp<other.tp:pos<other.pos;
	}
}nd[200010];

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(nd,0,sizeof(nd));
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>nd[i].pos;
			nd[i].tp=1;
		}
		for(int i=1;i<=m;i++)
		{
			cin>>nd[i+n].pos;	
			nd[i+n].tp=0;
		}
		sort(nd+1,nd+n+m+1);
		int nowpos=0,temp=0,ans=0;
		for(int i=1;i<=n+m;i++)
		{
			if(nd[i].tp&&nd[i].pos!=nowpos) temp++;
			if(!nd[i].tp) nowpos=nd[i].pos,temp=0;
			ans=max(ans,temp);
		}
		if(!ans) cout<<"Impossible\n";
		else cout<<ans<<'\n';
	}
	
	
}