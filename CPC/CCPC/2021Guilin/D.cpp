#include<bits/stdc++.h>

using namespace std;

set<pair<int,int> >s;
int a[10010],b[10010];

int k;
int ansx[5000010],ansy[5000010];

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		k=0;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		bool fg=1;
		for(int i=1;i<=n;i++)
		{
			int posa=0,posb=0;
			for(int j=1;j<=n;j++)
			{
				if(a[j]==i) posa=j;
				if(b[j]==i) posb=j;
			}
			if(posb>posa) 
			{
				fg=0;
				break;
			}
			for(int j=posb;j<posa;j++) if(a[j]>i) s.insert(make_pair(a[j],j));
			while(!s.empty())
			{
				auto now=*s.begin();
				for(int j=now.second;j<posa;j++) if(a[j]>i) s.erase(make_pair(a[j],j));
				ansx[++k]=now.second;
				ansy[k]=posa;
				swap(a[now.second],a[posa]);
				posa=now.second;
			}
		}
		if(fg==0) cout<<"-1"<<'\n';
		else
		{
			cout<<k<<"\n";
			for(int i=1;i<=k;i++) cout<<ansx[i]<<' '<<ansy[i]<<'\n';	
		}
	}
}