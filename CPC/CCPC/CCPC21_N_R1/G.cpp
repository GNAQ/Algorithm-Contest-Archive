#include<bits/stdc++.h>
#define int long long
using namespace std;

int vec[60][100001];
int siz[60];

int calc(int x)
{
	int res=0;
	for(;x;x/=10) res+=x%10;
	return res;
}

void pre()
{
	for(int i=1;i<=1000000;i++)
		vec[calc(i)][++siz[calc(i)]]=i;
}

int A,B,C,D;
int js(int x,int i)
{
	return A*x*x*i+B*x*x+C*x*i*i+D*x*i; 
}

signed main()
{
	pre();
	int T;cin>>T;
	while(T--)
	{
		int N;
		int ans=1e18;
		cin>>A>>B>>C>>D>>N;
		for(int i=1;i<=55;i++)
		{
			if(!siz[i]) continue;
			if(vec[i][1]>N) continue;
			
			int R=upper_bound(vec[i]+1,vec[i]+siz[i]+1,N)-vec[i]-1;
			ans=min(ans,min(js(vec[i][1],i),js(vec[i][R],i)));
			
			// cerr << "!!" << ans << endl;
			
			if(A==0&&B==0) continue;
			double dcz=-1*(C*i*i+D*i);dcz/=2.0*(A*i+B);
			
			// cerr << "DZC" << i << " " << dcz << endl;
			
			if(dcz>vec[i][1]&&dcz<vec[i][R])
			{
				int pos=lower_bound(vec[i]+1,vec[i]+siz[i]+1,dcz)-vec[i];
				// cerr << "#" << i << " " << vec[i][pos] << " " << vec[i][pos-1] << endl;
				if(pos!=1) ans=min(ans,min(js(vec[i][pos],i),js(vec[i][pos-1],i)));
				else ans=min(ans,js(vec[i][pos],i));
			}
		}
		printf("%lld\n",ans);
	}
}

/*
清size
特判 A=B=0

*/