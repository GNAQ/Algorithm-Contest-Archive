#include<bits/stdc++.h>

using namespace std;

const int MAXN=100010;

typedef long long ll;

int read()
{
	int ans=0;
	char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans;
}

int ch[MAXN<<5][2],siz[MAXN<<5],cnt=1;
void insert(int v,int p)
{
	int x=1;
	for(int i=31;i>=0;i--)
	{
		int& nxt=ch[x][(v>>i)&1];
		if(!nxt) nxt=++cnt;
		++siz[x],x=nxt;
	}
	++siz[x];
}

int nowx=0;

int query(int v,int k)
{
	int ans=0;
	int x=1;
	for(int i=31;i>=0;i--)
	{
		int d=(v>>i)&1;
		if(ch[x][d]&&k<=siz[ch[x][d]]) x=ch[x][d];
		else k-=siz[ch[x][d]],x=ch[x][d^1],ans|=1<<i;
	}
	return ans;
}

typedef pair<int,int>pi;
priority_queue<pi,vector<pi>,greater<pi> >q;
int rk[MAXN];
int a[MAXN];

int n;

pi querymin()
{
	pi t=q.top();q.pop();
    if(rk[t.second]==n) return make_pair(t.first,t.second);
	q.push(make_pair(query(a[t.second],++rk[t.second]),t.second));
    return make_pair(t.first,t.second);
}

int fa[200010], ans;
int vis[200010];
map<int, vector<int> > cnts;

int Find(int e)
{
	if (e!=fa[e]) fa[e]=Find(fa[e]);
	return fa[e];
}

void Merge(int ai, int bi)
{
	fa[Find(bi)]=Find(ai);
}

void Solve()
{
	scanf("%d", &n); ans = 1e9+1e8;
	for (int i=1;i<=2*n;i++) fa[i]=i;
    for(int i=1;i<=n;i++) 
	{
		scanf("%d", &a[i]);
		cnts[a[i]].push_back(i);
	}
	
	for(int i=1;i<=n;i++) 
	{
		if (cnts[a[i]].size()==1)
			insert(a[i],i);
		else if (cnts[a[i]].size()==2)
			if (i == cnts[a[i]][0])
				insert(a[i], i);
	}
	
	for (auto v:cnts)
	{
		if (v.second.size() >= 3)
		{
			printf("0\n");
			for (int i=1;i<=n;i++) printf("1");
			puts("");
			return;
		}
		if (v.second.size() == 2)
		{
			ans = min(ans, query(a[v.second[0]], 2));
		}
	}
	
	for(int i=1;i<=n;i++) 
		q.push(make_pair(query(a[i],rk[i]=2),i));
	
	while (1)
	{
		pair<int, int> ret = querymin();
		
		if (ans < ret.first)
		{
			break;
		}
		
		int li, ri;
		li = ret.second;
		ri = ret.first ^ a[li];
		ri = cnts[ri][0];
		if (a[li]>a[ri]) continue;
		
		if (Find(li)==Find(ri))
		{
			ans = ret.first;
			break;
		}
		
		Merge(li, ri+n);
		Merge(ri, li+n);
	}
	
	cout << ans << endl;
	
	for (int i=1;i<=n;i++)
	{
		if (!vis[Find(i+n)] && !vis[Find(i)])
		{
			vis[Find(i+n)]=2;
			vis[i+n]=2;
			vis[i]=1;
			vis[Find(i)]=1;
		}
		else if (vis[Find(i+n)])
		{
			vis[i]=(vis[Find(i+n)]==2)?1:2;
		}
		else if (vis[Find(i)])
		{
			vis[i]=vis[Find(i)];
			vis[i+n]=vis[Find(i+n)]=(vis[i]==2)?1:2;
		}
	}
	map<int, int> mapx;
	for (int i=1;i<=n;i++) 
	{
		if (mapx.find(a[i])==mapx.end())
			mapx[a[i]]=vis[i];
		else
			vis[i]=(mapx[a[i]] == 2)?1:2;
		printf("%d", vis[i]);
	}
	puts("");
	return;
}

void Clear()
{
	cnts.clear();
	for (int i=1;i<=2*n;i++) vis[i]=0;
	for (int i=1;i<=cnt;i++) ch[i][0]=ch[i][1]=0;
	for (int i=1;i<=cnt;i++) siz[i]=0;
	cnt=1;
	while(!q.empty()) q.pop();
	
}

int main()
{
    int T; scanf("%d", &T);
	while (T--)
	{
		Solve();
		Clear();
	}
}