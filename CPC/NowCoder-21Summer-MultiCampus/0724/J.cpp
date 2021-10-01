#include<bits/stdc++.h>
typedef long long ll;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace GenHelper
{
    unsigned z1,z2,z3,z4,b,u;
    unsigned get()
    {
        b=((z1<<6)^z1)>>13;
        z1=((z1&4294967294U)<<18)^b;
        b=((z2<<2)^z2)>>27;
        z2=((z2&4294967288U)<<2)^b;
        b=((z3<<13)^z3)>>21;
        z3=((z3&4294967280U)<<7)^b;
        b=((z4<<3)^z4)>>12;
        z4=((z4&4294967168U)<<13)^b;
        return (z1^z2^z3^z4);
    }
    bool read() {
      while (!u) u = get();
      bool res = u & 1;
      u >>= 1; return res;
    }
    void srand(int x)
    {
        z1=x;
        z2=(~x)^0x233333333U;
        z3=x^0x1234598766U;
        z4=(~x)+51;
      	u = 0;
    }
}
// using namespace GenHelper;
bool edge[8005][8005];
int cnts[8010];

int main() 
{
	int n, seed; 
	readx(n); readx(seed);
	GenHelper::srand(seed);
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			edge[j][i] = edge[i][j] = GenHelper::read();
			
		}
	}
	
	
	ll ans = 0;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) 
		{
			if (j!=i)
			{
				cnts[i]+=edge[i][j];
			}
		}
		ans += 1LL * cnts[i] * (n - 1 - cnts[i]);
	}
	
	ans /= 2LL;
	
	printf("%lld\n", 1LL * n * (n-1) * (n-2) / 6 - ans);
	
 	return 0;
}