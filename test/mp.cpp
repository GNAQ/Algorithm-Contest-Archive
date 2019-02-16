#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<ctime>
typedef long long ll;
using namespace std;

ll mod,T;
pair<ll,int> ask[100010];
int ans[100010];

// int a[] = { 1, 1, 2, 3, 6, 10, 19, 33, 61, 108, 197, 352 };
// a(n) = 5*a(n-2) - 6*a(n-4) + a(n-6)
// a(n) is the lefttop element of the n-th power of the matrix {(1,1,0) (1,0,1) (0,1,0)}
// ↑ from OEIS.org http://oeis.org/A028495
// sol sketch (GNAQ)
// 把询问离线
// 然后排序矩乘
// sol sketch (std)
// 

inline char gc()
{
    static char BUFF[20000],*S=BUFF,*T=BUFF;
    return S==T&&(T=(S=BUFF)+fread(BUFF,1,20000,stdin),S==T)?EOF:*S++;
}
template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; char ch=0;
	while (ch<'0' || ch>'9') ch=gc();
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=gc(); }
}
template<typename inp_typ>
inline void writex(inp_typ x)
{
    if(x>9) writex(x/10);
    putchar(x%10+'0');
}

namespace POW
{
	struct Matrix
	{
		ll a[4][4];
		
		ll* operator [] (int inp_addr) { return this->a[inp_addr]; }
		Matrix() { memset(a,0,sizeof a); }
		Matrix operator * (const Matrix& B) const
		{
			Matrix C;
			for (int i=1;i<=3;i++) 
				for (int j=1;j<=3;j++)
					for (int k=1;k<=3;k++)
						C[i][j]=(C[i][j]+this->a[i][k]*B.a[k][j])%mod;
			return C;
		}
	};
	
	Matrix fastpow(Matrix an,ll p)
	{
		Matrix ret=an; p--;
		for (;p;p>>=1,an=an*an) if (p&1) ret=ret*an;
		return ret;
	}
};

bool cmp_val(pair<ll,int>& a1,pair<ll,int>& a2)
{
	return a1.first<a2.first;
}

int main()
{
	char inp_file[20];
	scanf("%s",inp_file);
	freopen(inp_file,"r",stdin);
	freopen("dat.out","w",stdout);
	
	double str_time=clock();
	
	readx(T); readx(mod);
	for (int i=1;i<=T;i++) { readx(ask[i].first); ask[i].second=i; }
	sort(ask+1,ask+T+1,cmp_val);
	
	POW::Matrix Mt_tmp;
	Mt_tmp[1][1]=1; Mt_tmp[1][2]=1; Mt_tmp[1][3]=0;
	Mt_tmp[2][1]=1; Mt_tmp[2][2]=0; Mt_tmp[2][3]=1;
	Mt_tmp[3][1]=0; Mt_tmp[3][2]=1; Mt_tmp[3][3]=0;
	const POW::Matrix Mt=Mt_tmp;
	
	POW::Matrix ans_mat;
	ans_mat[1][1]=ans_mat[2][2]=ans_mat[3][3]=1;
	
	int pos=1;
	while (ask[pos].first<=2)
	{
		ans[ask[pos].second]=1;
		pos++;
	}
	ask[pos-1].first=1;
	for (int i=pos;i<=T;i++)
	{
		if (ask[i].first-ask[i-1].first>0)
			ans_mat=ans_mat*fastpow(Mt,ask[i].first-ask[i-1].first);
		ans[ask[i].second]=ans_mat[1][1];
	}
	
	for (register int i=1;i<=T;i++) { writex(ans[i]); putchar(' '); }
	putchar('\n');
	
	double end_time=clock();
	cerr<<(end_time-str_time)/CLOCKS_PER_SEC<<endl;
	
}