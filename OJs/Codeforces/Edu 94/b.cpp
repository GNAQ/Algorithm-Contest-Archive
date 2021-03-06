#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
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

int main()
{
	int T; readx(T);
	while (T--)
	{
		int p,f,cnt_s,cnt_w,s,w;
		readx(p); readx(f); readx(cnt_s); readx(cnt_w);
		readx(s); readx(w);
		
		if (s>w) 
		{
			swap(s,w);
			swap(cnt_s,cnt_w);
		}
		if ((p/s+f/s)<cnt_s)
		{
			printf("%d\n",p/s+f/s);
			continue;
		}
		
		int ans=cnt_s;
		
		if (p<f) swap(p,f);
		// enum the bigger nums
		for (int i=0;i<=cnt_w;i++)
		{
			int pi=p, fi=f, tmp=0, rem_s=cnt_s, rem_w=cnt_w, x;
			if (i*w>p) break;
			
			// take w for p
			tmp+=i;
			rem_w-=i;
			pi-=i*w;
			
			// take s for p
			tmp+=(x=min(pi/s,rem_s)); // notice!
			rem_s-=min(pi/s,rem_s);
			// pi-=min( (pi/s)*s, cnt_s*s );
			
			// take rest s for f
			tmp+=(x=min(rem_s, fi/s));
			rem_s-=x;
			fi-=x*s;
			
			// greedily take w for f 
			tmp+=min(rem_w, fi/w);
			
			ans=max(ans, tmp);
		}
		
		printf("%d\n",ans);
	}
	return 0;
}