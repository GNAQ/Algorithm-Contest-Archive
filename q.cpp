#pragma GCC target ("avx2")
#include <immintrin.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define __AVX__ 1
#define __AVX2__ 1
#define __SSE__ 1
#define __SSE2__ 1
#define __SSE2_MATH__ 1
#define __SSE3__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE_MATH__ 1
#define __SSSE3__ 1
# define iv __m256i
# define vm(x,y) _mm256_mul_epi32((x),(y))
# define va(x,y) _mm256_add_epi32((x),(y))
# define vs(x,y) _mm256_sub_epi32((x),(y))
# define sff(x,y) _mm256_shuffle_epi32((x),(y))
# define sr64(x,y) _mm256_srli_epi64((x),(y))
# define vmin(x,y) _mm256_min_epi32((x),(y))	
using namespace std;
namespace NTT{
	const int N=2097152+10;
	const int p=998244353;
	typedef  unsigned int uit;
	typedef  unsigned long long ll;
	inline ll po(ll a,ll pt)
	{
		ll r=1;
		for(;pt;pt>>=1,a=a*a%p)
			if(pt&1)r=r*a%p;
		return r;
	}
	inline iv VLod(const uit* __restrict__ A) {
        return _mm256_load_si256((const __m256i*) A);
    }
    inline void VSto(uit* __restrict__ A, __m256i v) {
        _mm256_store_si256((__m256i*) A, v);
    }
    iv mod,mu,mask;
	inline iv submul(iv a,iv b){ 
		iv x=vm(a,b);
		iv q3=sr64(vm(sr64(x,29),mu),31);
		return vs(x,vm(q3,mod));
	}
	inline iv Vmul(iv a,iv b){
		iv high=submul(sff(a,0xf5),sff(b,0xf5));
		iv low=submul(a,b);
		low=_mm256_blend_epi32(sff(high,0xb0),low,0x55);
		iv r=_mm256_and_si256(low,mask);
		r=vmin(r,vs(r,mod)); //???
		return vmin(r,_mm256_sub_epi32(r,mod));
	}
	inline iv Vadd(iv a,iv b){
		iv r=va(a,b);
		return vmin(r,vs(r,mod));	
	}
	inline iv Vsub(__m256i a,__m256i b){
		iv r=vs(va(a,mod),b);
		return vm(r,vs(r,mod));	
	}
	int rv[21][N];ll rt[2][30];uit vw[8];
	void initall(int d)
	{
		for(int j=0;j<=d-1;j++)
			for(int i=0;i<(1<<(j+1));i++)rv[j+1][i]=(rv[j+1][i>>1]>>1)|((i&1)<<j);
		for(int j=1,k=2;j<=d;k<<=1,j++)rt[0][j]=po(3,(p-1)/k);
		for(int j=1,k=2;j<=d;k<<=1,j++)rt[1][j]=po(332748118,(p-1)/k);
		mod=_mm256_set1_epi32(998244353);
		mu=_mm256_set1_epi32(1154949187);//288737297);
		mask=_mm256_set1_epi32((int)((1ll<<31)-1));
		vw[0]=1;
	}
	void ntt(uit *a,int d,int o){
		int n=1<<d;
		for(int i=0;i<n;i++) if(i<rv[d][i]) swap(a[i],a[rv[d][i]]);
		//printf("org a:");
		// for(int i=0;i<n;i++)printf("%d ",a[i]);printf("\n");
		for(int k=1,j=1;k<n&&k<8;k<<=1,j++)
		{
			//printf("j=%d_______________\n",j);
			for(int s=0;s<n;s+=(k<<1))
				for(int i=s,w=1;i<s+k;i++,w=w*rt[o][j]%p)
				{
					// printf("w=%d,a[%d]=%u,a[%d]=%u\n",w,i,a[i],i+k,a[i+k]);
					uit a1=(ll)w*a[i+k]%p;uit a0=a[i];
					a[i+k]=(a0+p-a1)%p;
					a[i]=(a0+a1)%p;
					// printf("a[%d]=%u,a[%d]=%u,a0=%u,a1=%u\n",
					// i,a[i],i+k,a[i+k],a0,a1);
				}	
		}
		for(int k=8,j=4;k<n;k<<=1,j++)
		{
			 printf("do vector acc j=%d\n",j);
			for(int t=1;t<8;t++)vw[t]=vw[t-1]*rt[o][j]%p;
			iv st=VLod(vw);
			iv mult=_mm256_set1_epi32(vw[7]*rt[o][j]%p);
			for(int s=0;s<n;s+=(k<<1))
			{
				iv cur=st;
				for(int i=s;i<s+k;i+=8)
				{ 
					iv a1=Vmul(VLod(a+i+k),cur);
					iv a0=VLod(a+i);
					VSto(a+i+k,vs(a0,a1));
					VSto(a+i,va(a0,a1));
					cur=vm(cur,mult);
				}
			}
		}
		if(o){ll iv=po(n,p-2);for(int i=0;i<n;i++)a[i]=a[i]*iv%p;}
	}
}
typedef unsigned int uit;
const int N=2097152+10;
const int p=998244353;	
uit a[N];uit b[N];
int n;int m;
int main()
{
	scanf("%d%d", &n, &m);
	for (int i=0;i<=n;i++)
	{
		scanf("%u", &a[i]);
	}
	for (int i=0;i<=m;i++)
	{
		scanf("%u", &b[i]);
	}
	
	int len = 1, w = 0;
	while (len <= n+m+1)
	{
		len*=2;
		w++;
	}

	// for (int i=0;i<len;i++)
	// 	printf("%u%c", a[i], " \n"[i==len-1]);
	// for (int i=0;i<len;i++)
	// 	printf("%u%c", b[i], " \n"[i==len-1]);
	
	NTT::initall(18);
	// printf("w=%d\n",w);
	NTT::ntt(a, w, 0); NTT::ntt(b, w, 0);
	
	for (int i=0;i<len;i++)
		printf("%u%c", a[i], " \n"[i==len-1]);
	for (int i=0;i<len;i++)
		printf("%u%c", b[i], " \n"[i==len-1]);
	
	for (int i=0;i<len;i++) a[i]=1LL*a[i]*b[i]%998244353LL;
	NTT::ntt(a, w, 1);
	
	for (int i=0;i<=n+m;i++)
		printf("%u%c", a[i], " \n"[i==n+m]);
}
