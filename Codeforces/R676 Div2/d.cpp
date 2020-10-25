#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
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
		ll c1,c2,c3,c4,c5,c6;
		ll ex,ey;
		readx(ex); readx(ey);
		readx(c1); readx(c2); readx(c3);
		readx(c4); readx(c5); readx(c6);
		swap(ex,ey);
		ll ans=2100000000000000000LL;
		
		if (ex>=0 && ey>=0) //c2 c6 OK
			ans=min(ans, ex*c2+ey*c6);
		if ((ex-ey)>=0 && ey>=0) // c2 c1 OK
			ans=min(ans, ey*c1+(ex-ey)*c2);
		if ((ex-ey)>=0 && ey<=0) // c2 c4 OK
			ans=min(ans, (-ey)*c4+(ex-ey)*c2);
		if (ey<=0 && ex>=0) //c2 c3 OK
			ans=min(ans, ex*c2+(-ey)*c3);
		if ((ex-ey)<=0 && ey>=0 && ex>=0) // c1 c6 OK(?)
			ans=min(ans, (ey-ex)*c6+ex*c1);
		if (ey>=0 && (ex-ey)<=0) // c1 c5 OK(?)
			ans=min(ans, (ey-ex)*c5+ey*c1);
		if (ex>=0 && (ex-ey)>=0) //c1 c3 OK
			ans=min(ans, ex*c1+(ex-ey)*c3);
		if (ey>=0 && ex<=0) //c6 c5 OK
			ans=min(ans, ey*c6+(-ex)*c5);
		if (ex<=0 && (ex-ey)<=0) // c6 c4 OK
			ans=min(ans, (-ex)*c4+(ey-ex)*c6);
		if (ex<=0 && ey<=0) // c5 c3 OK
			ans=min(ans, (-ey)*c3+(-ex)*c5);
		if (ey<=0 && (ex-ey)<=0) // c5 c4 OK
			ans=min(ans, (ey-ex)*c5+(-ey)*c4);
		if (ex<=0 && (ey-ex)<=0) // c4 c3 OK
			ans=min(ans, (-ex)*c4+(ex-ey)*c3);
			
		printf("%lld\n",ans);
	}
	
}