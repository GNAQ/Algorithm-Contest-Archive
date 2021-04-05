#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll inf=0x3f3f3f3f3f3f3f3f;

struct Node
{
	ll mx[3],mn[3];
	int id,ls,rs;
	int d[3];
	
	const int& operator[](int x) const {return d[x];}
    int& operator[](int x) { return d[x]; }
}p[200010],t[200010];

int root,cur;
pair<ll,int>ans;

bool cmp(const Node &a,const Node &b)
{
	return a.d[cur]<b.d[cur];
}

void update(int x)
{
	int l=t[x].ls,r=t[x].rs;
	for(int i=0;i<3;i++)
	{
		t[x].mn[i]=t[x].mx[i]=t[x][i];
		if(l)
		{
			t[x].mn[i]=min(t[x].mn[i],t[l].mn[i]);
			t[x].mx[i]=max(t[x].mx[i],t[l].mx[i]);
		}
		if(r)
		{
			t[x].mn[i]=min(t[x].mn[i],t[r].mn[i]);
			t[x].mx[i]=max(t[x].mx[i],t[r].mx[i]);
		}
	}
}

int n,m;

int build(int l,int r,int now)
{
	cur=now;
	int mid=(l+r)>>1;
	
	nth_element(t+l,t+mid,t+r+1,cmp);
	
	t[mid].ls=t[mid].rs=0;
	for(int i=0;i<3;i++)
	{
		t[mid].mx[i]=t[mid].mn[i]=t[mid][i];
	}
	if(l<mid) t[mid].ls=build(l,mid-1,(now+1)%3);
	if(r>mid) t[mid].rs=build(mid+1,r,(now+1)%3);
	update(mid);
	return mid;
}

ll x,y,z;

ll sqr(ll x){return x*x;}

ll dis(int k) //
{
	ll res=0;
	if(z<t[k].mn[2]) return inf;
	if(x<t[k].mn[0]) res+=sqr(t[k].mn[0]-x);
	if(x>t[k].mx[0]) res+=sqr(x-t[k].mx[0]);
	if(y<t[k].mn[1]) res+=sqr(t[k].mn[1]-y);
	if(y>t[k].mx[1]) res+=sqr(y-t[k].mx[1]);
	return res;
}

void query(int k)
{
	pair<ll,int> dl=make_pair(inf,1),dr=make_pair(inf,1);
	int l=t[k].ls,r=t[k].rs;
	
	// cout<<"------"<<k<<"------\n";
	// cout<<t[k].id<<'\n';
	// cout<<t[l].id<<' '<<t[r].id<<"\n";
	
	ll d0=inf;
	if(z>=t[k].d[2]) d0=sqr(t[k][0]-x)+sqr(t[k][1]-y);
	ans=min(ans,make_pair(d0,t[k].id));
	if(l) dl=make_pair(dis(l),t[l].id);
	//if(dl<ans) query(l);
	if(r) dr=make_pair(dis(r),t[r].id);
	//if(dr<ans) query(r);
	if(dl<dr)
	{
		if(dl<ans) query(l);
		if(dr<ans) query(r);
	}
	else
	{
		if(dr<ans) query(r);
		if(dl<ans) query(l);
	}
	
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>t[i][0]>>t[i][1]>>t[i][2];
			t[i].id=i;
			p[i]=t[i];
		}
		root=build(1,n,0);
		for(int i=1;i<=m;i++)
		{
			ans=make_pair(inf,0);
			cin>>x>>y>>z;
			query(root);
			int id=ans.second;
			cout<<p[id][0]<<" "<<p[id][1]<<" "<<p[id][2]<<'\n';
		}
	}
}


