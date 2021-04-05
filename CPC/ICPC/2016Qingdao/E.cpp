#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Bignum {
//	friend istream &operator >> (istream &in, Bignum &x);
    friend ostream &operator << (ostream &out, const Bignum &x);
/*------构造、赋值等--------*/ 
    Bignum(const ll &x) {*this = x;}
    Bignum(const Bignum &b, bool sign) {*this = b;	this->sign = sign;}
    Bignum(const Bignum &b) {*this = b;}
    Bignum() {num.clear();	sign = 0;}
    Bignum operator = (int x) {
        num.clear();
        sign = (x < 0 ? (x = -x), 1 : 0);
        num.push_back(x%mod);
        x /= mod;
        if(x)	num.push_back(x);
        return *this;
    }
    Bignum operator = (ll x) {
        num.clear();
        if(x < 0) {
            sign = 1;
            x = -x;
        } else	sign = 0;
        while(x >= mod) {
            num.push_back(x%mod);
            x /= mod;
        }
        num.push_back(x);
        return *this;
    }
    Bignum operator = (const string &str) {
        num.clear();
        int i = str.size();
        if(str[0] == '-') {
            sign = 1;
        } else	sign = 0;
        while(i-sign >= width) {
            int x = 0;
            for(int j = i-width; j < i; j++) {
                x = x*10+(str[j]-'0');
            }
            num.push_back(x);
            i -= width;
        }
        if(i-sign) {
            int x = 0;
            for(int j = sign; j < i; j++) {
                x = x*10+(str[j]-'0');
            }
            num.push_back(x);
        }
        return *this;
    }
/*------关于大小的比较------*/
    bool operator < (const Bignum &b) const {
        if(sign^b.sign)	return sign;
        int size1 = num.size(), size2 = b.num.size();
        if(size1 == size2) {
            for(int i = size1-1; i >= 0; i--) {
                if(num[i] != b.num[i])	return (num[i] < b.num[i])^sign;
            }
        }
        return (size1 < size2)^sign;
    }
    bool operator > (const Bignum &b)  const { return b < *this;}
    bool operator == (const Bignum &b) const { return !(*this < b || *this > b);}
    bool operator <= (const Bignum &b) const { return !(*this > b);}
    bool operator >= (const Bignum &b) const { return !(*this < b);}
    bool operator != (const Bignum &b) const { return *this < b || *this > b;}
/*------加减乘除膜------------*/
    Bignum operator + (const Bignum &b) const {
        if((sign&b.sign) || !(sign|b.sign)) {
            return Bignum(add(b), sign&b.sign);
        } else if(!sign) {
            return sub(b);
        } else {
            return b.sub(*this);
        }
    }
    Bignum operator - (const Bignum &b) const {
        if((sign&b.sign) || !(sign|b.sign)) {
            Bignum c = sub(b);
            c.sign = ((c.num.size() == 1 && !c.num[0]) ? 0 : (c.sign^(sign&b.sign)));
            return c;
        } else if(!sign){
            return add(b);
        } else {
            return Bignum(add(b), 1);
        }
    }
    Bignum operator * (int x) {
        return mul(x);
    }
    Bignum operator / (int x) {
        return div(x, 0);
    }
    Bignum operator % (int x) {
        return div(x, 1);
    }
    Bignum operator * (const Bignum &b) const {
        return mul(b);
    }
/*------+=等----------------*/
    Bignum operator += (const Bignum &b) {
        return *this = *this + b;
    }
    Bignum operator -= (const Bignum &b) {
        return *this = *this - b;
    }
    Bignum operator *= (int b) {
        return *this = *this * b;
    }
    Bignum operator /= (int b) {
        return *this = *this / b;
    }
    Bignum operator %= (int b) {
        return *this = *this % b;
    }
    Bignum operator *= (const Bignum &b) {
        *this = *this * b;
    }
/*------变量----------------*/
//private:
    static const int mod = 100000000;
    static const int width = 8;
    vector <ll> num;
    bool sign;
/*------输出----------------*/ 
    void print() const {
        if(sign)	putchar('-');
        int size = num.size()-1;
        printf("%d", num[size]);
        for(int i = size-1; i >= 0; --i) {
            printf("%08d", num[i]);
        }
//		putchar('\n');
    }
/*------计算----------------*/ 
    Bignum add(const Bignum &b) const {
        Bignum c;
        int last = 0, sizea = num.size();
        int sizeb = b.num.size();
        int size = max(sizea, sizeb);
        for(int i = 0; i < size; ++i) {
            int x = last;
            if(i < sizea)	x += num[i];
            if(i < sizeb)	x += b.num[i];
            last = x/mod;
            c.num.push_back(x % mod);
        }
        return c;
    }
    Bignum sub(const Bignum &b) const {
        Bignum c;
        Bignum const *d;
        if(*this > b) {
            c = *this;	c.sign = 0;	d = &b;
        } else {
            c = b;	c.sign = 1;	d = this;
        }
        int size = c.num.size(), sized = d->num.size();
        for(int i = 0; i < sized; ++i) {
            c.num[i] -= d->num[i];
            if(c.num[i] < 0) {
                c.num[i] += mod;
                --c.num[i+1];
            }
        }
        while(!c.num[size-1] && size > 1)	--size;
        c.num.resize(size);
        if(size == 1 && c.num[0] == 0)	c.sign = 0;
        return c;
    }
    Bignum mul(int x) {
        Bignum c;
        c.sign = sign^(x<0);
        if(x < 0)	x = -x;
        int size = num.size();
        ll last = 0;
        for(int i = 0; i < size; ++i) {
            c.num.push_back((last + x * num[i]) % mod);
            last = (last + x * num[i]) / mod;
        }
        while(last) {
            c.num.push_back(last%mod);
            last /= mod;
        }
        return c;
    }
    Bignum div(int x, bool flag) {
        Bignum c;
        c.sign = sign^(x<0);
        if(x < 0)	x = -x;
        int size = num.size();
        c.num.resize(size);
        ll last = 0;
        for(int i = size-1; i >= 0; --i) {
            last = last * mod + num[i];
            if(last >= x) {
                c.num[i] = last / x;
                last %= x;
            }
        }
        while(c.num[size-1] == 0 && size > 1) {--size;}
        c.num.resize(size);
        return (flag == 0 ? c : Bignum(last*(sign ? -1 : 1)));
    }
    Bignum mul(const Bignum &b) const {
        int size1 = num.size(), size2 = b.num.size(), csize = size1+size2+2;
        Bignum c;	c.num.resize(csize+1, 0);
        c.sign = (sign^b.sign);
        for(int i = 0; i < size1; ++i) {
            for(int j = 0; j < size2; ++j) {
                c.num[i+j] += num[i]*b.num[j];
            }
        }
        for(int i = 0; i < csize; ++i) {
            if(c.num[i] >= mod) {
                c.num[i+1] += c.num[i]/mod;
                c.num[i] %= mod;
            }
        }
        while(!c.num[csize] && csize > 0)	--csize;
        c.num.resize(csize+1);
        return c;
    }
};
/*------读入输出----------------*/ 
istream &operator >> (istream &in, Bignum &x) {
    string s;
    if(!(in >> s))	return in;
    x = s;
    return in;
}
ostream &operator << (ostream &out, const Bignum &x) {
    x.print();
    return out;
}

Bignum gcd(Bignum &a, Bignum &b) {
    if(a.num.size() == 1 && a.num[0] == 0)	return b;
    if(b.num.size() == 1 && b.num[0] == 0)	return a;
    int fg = 0;
    if((a.num[0]&1) == 0) {
        a /= 2;
        ++fg;
    }
    if((b.num[0]&1) == 0) {
        b /= 2;
        ++fg;
    }
    if(fg == 1)	return gcd(a, b);
    if(fg == 2)	return gcd(a, b)*2;
    if(a > b) {
        a -= b;
        return gcd(b, a);
    }
    b -= a;
    return gcd(a, b);
}

struct Matrix
{
    Bignum a[3][3];
}res;

Bignum x0;

Matrix mul(Matrix c,Matrix b)
{
    Matrix temp;
    memset(temp.a,0,sizeof(temp.a)); 
    for(int i=1;i<=2;i++)
        for(int j=1;j<=2;j++)
            for(int k=1;k<=2;k++)
                temp.a[i][j]=(temp.a[i][j]+c.a[i][k]*b.a[k][j]);
    return temp; 
}

Matrix qpow(Matrix b,Bignum k)
{
    Matrix ans;
    for(int i=1;i<=2;i++)
        for(int j=1;j<=2;j++)
            if(i==j) ans.a[i][j]=1;
            else ans.a[i][j]=0;
    while(k!=0)
    {
        if(k%2==1) 
            ans=mul(ans,b);
        k/=2;
        b=mul(b,b);
    }
    return ans;
}
const int MAXN=2e5+100;
int vis[MAXN];
main()
{
	int T;cin>>T;
	while(T--)
	{
		int p;
		memset(res.a,0,sizeof res.a);
		res.a[1][1]=1;
		res.a[1][2]=1;
		res.a[2][1]=1;		
		Matrix ss;
		cin>>x0>>p;
		ss=qpow(res,x0+1);
		int x1=(ss.a[2][2]%p).num[0];
		int x00=(x0%p).num[0];
		vis[x00]=vis[x1]=1;
		while(1)
		{	
			
		}
	}
}