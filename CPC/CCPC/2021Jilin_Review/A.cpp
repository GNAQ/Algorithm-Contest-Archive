#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
#include<random>
#include<ctime>
typedef long long ll;
using namespace std;



template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


ll fastpow(ll an, ll p, ll mod)
{
	ll ret = 1;
	for (;p;p>>=1,an=an*an%mod) if (p&1) ret=ret*an%mod;
	return ret;
}

bool Check(ll k, ll n, ll m)
{
	return fastpow(n,k,n*m-1)==1;
}

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ll,int> pli;
namespace pollard_rho {
    const int C=2307;
    const int S=10;
    mt19937 rd(time(0));
    vector<ll>ve;
    ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
    ll mul(ll a,ll b,ll mod){return (__int128)a*b%mod;}
    ll power(ll a,ll b,ll mod){
        ll res=1;a%=mod;
        while(b){
            if(b&1)res=mul(res,a,mod);
            a=mul(a,a,mod);
            b>>=1;
        }
        return res;
    }
    bool check(ll a,ll n){
        ll m=n-1,x,y;
        int j=0;
        while(!(m&1))m>>=1,j++;
        x=power(a,m,n);
        for(int i=1;i<=j;x=y,i++){
            y=mul(x,x,n);
            if(y==1&&x!=1&&x!=n-1)return 1;
        }
        return y!=1;
    }
    bool miller_rabin(ll n){
        ll a;
        if(n==1)return 0;
        if(n==2)return 1;
        if(!(n&1))return 0;
        for(int i=0;i<S;i++)if(check(rd()%(n-1)+1,n))return 0;
        return 1;
    }
    ll pollard_rho(ll n,int c){
        ll i=1,k=2,x=rd()%n,y=x,d;
        while(1){
            i++;x=(mul(x,x,n)+c)%n,d=gcd(y-x,n);
            if(d>1&&d<n)return d;
            if(y==x)return n;
            if(i==k)y=x,k<<=1;
        }
    }
    void findfac(ll n,int c){
        if(n==1)return ;
        if(miller_rabin(n)){
            ve.push_back(n);
            return ;
        }
        ll m=n;
        while(m==n)m=pollard_rho(n,c--);
        findfac(m,c);
        findfac(n/m,c);
    }
    vector<pli> solve(ll n){
        vector<pli>res;
        ve.clear();
        findfac(n,C);
        sort(ve.begin(),ve.end());
        for(auto x:ve){
            if(res.empty()||res.back().first!=x)res.push_back({x,1});
            else res.back().second++;
        }
        return res;
    }
}

ll GetPhi(ll v)
{
	ll ans = v;
	// ll lim = sqrt(v);
	// for (ll i=2;i<=lim;i++)
	// {
	// 	if (v%i==0)
	// 	{
	// 		ans-=ans/i;
	// 		while (v%i==0) v/=i;
	// 		lim = sqrt(v);
	// 	}
	// }
	// if (v>1) ans-=ans/v;
	vector<pli> res = pollard_rho::solve(v);
	for (auto u:res)
	{
		for (int i=1;i<=u.second;i++) ans-=ans/u.first;
	}
	return ans;
}

ll Solve(ll n, ll m)
{
	ll ans = GetPhi(n*m-1), tmp = ans;
	// ll lim = sqrt(ans);
	// for (ll w=2;w<=lim;w++)
	// 	if (!(tmp%w))
	// 	{
	// 		while (!(tmp%w)) tmp/=w;
	// 		while ( !(ans%w) && Check(ans/w, n, m) ) ans/=w;
	// 		lim=sqrt(tmp);
	// 	}
	// if (tmp>1 && Check(ans/tmp, n, m)) ans/=tmp;
		
	// printf("%lld\n", ans);
	
	vector<pli> res = pollard_rho::solve(tmp);
	for (auto u:res)
	{
		for (int i=1;i<=u.second;i++)
		{
			if (Check(ans/u.first, n, m)) ans/=u.first;
		}
	}
	
	return ans;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		ll n, m;
		readx(n); readx(m);
		printf("%lld\n", Solve(n, m));
	}
	
}