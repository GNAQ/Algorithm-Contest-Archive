#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int inf=0x3f3f3f3f;
 
int tr[200010][10],n,m,rt,tot;
ll sum[200010],tag[200010],powten[11];
 
void init()
{
    for(int i=1;i<=tot;i++)
    {
        memset(tr[i],0,sizeof(tr[i]));
        sum[i]=tag[i]=0;
    }
    tot=rt=1;
}
 
ll add_val(ll x,ll y)
{
    if(x==0||y==0) return x|y;
    ll res=0;
    for(int i=0;i<10;i++,x/=10,y/=10)
    {
        res+=(x%10+y%10)%10*powten[i];
    }
    return res;
}
 
void pushdown(int now)
{
    if(tag[now]==0) return;
    for(int i=0;i<=9;i++)
    {
        if(!tr[now][i]) continue;
        int vs=tr[now][i];
        if(tag[now]>10) sum[vs]=0;
        else
        {
            sum[vs]/=powten[tag[now]];
            tag[vs]+=tag[now];
        }
    }
    tag[now]=0;
}
 
void add(int now,int x)
{
    sum[now]=add_val(sum[now],x);
    for(int i=9;i>=0;i--)
    {
        pushdown(now);
        int c=x/powten[i]%10;
        if(tr[now][c]==0) tr[now][c]=++tot;
        now=tr[now][c];
        sum[now]=add_val(sum[now],x);
    }
}
 
void shift()
{
    tr[++tot][0]=rt;
    sum[tot]=sum[rt]/10;
    rt=tot;
    tag[tot]++;
}
 
ll query_sum(ll x)
{
    ll res=0;
    int now=rt;
    for(int i=9;i>=0;i--)
    {
        pushdown(now);
        int c=x/powten[i]%10,j=9;
        while(tr[now][(j+10-c)%10]==0) j--;
        res+=j*powten[i];
        now=tr[now][(j+10-c)%10];
    }
    return res;
}
 
ll get(int dep,int now,ll l,ll r,ll x,ll y)
{
    if(y<l||x>r) return 0;
    if(l>=x&&r<=y) return sum[now];
    pushdown(now);
    ll res=0;
    for(int i=0;i<10;i++)
    {
        if(!tr[now][i]) continue;
        ll nl=l+powten[dep]*i,nr=l+powten[dep]*(i+1)-1;
        res=add_val(res,get(dep-1,tr[now][i],nl,nr,x,y));
    }
    return res;
}
 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    powten[0]=1;
    for(int i=1;i<=10;i++) powten[i]=powten[i-1]*10;
    int T;
    cin>>T;
    for(int o=1;o<=T;o++)
    {
        cout<<"Case #"<<o<<": "<<'\n';
        cin>>n>>m;
        init();
        for(int i=1;i<=n;i++)
        {
            int tmp;
            cin>>tmp;
            add(rt,tmp);
        }
        while(m--)
        {
            string opt;
            cin>>opt;
            if(opt[0]=='S'&&opt[1]=='h') shift();
            else if(opt[0]=='A')
            {
                int x;
                cin>>x;
                add(rt,x);
            }
            else if(opt[0]=='Q')
            {
                int x;
                cin>>x;
                cout<<query_sum(x)<<'\n';
            }
            else if(opt[0]=='S')
            {
                int l,r;
                cin>>l>>r;
                cout<<get(9,rt,0,powten[10] - 1,l,r)<<'\n';
            }
        }
    }
}