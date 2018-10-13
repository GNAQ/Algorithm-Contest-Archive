#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long

namespace COMPLEX
{
	const double eps=1e-8;
	struct Complex
	{
		double r,i;
        Complex(double x_in=0.0,double y_in=0.0) { r=x_in; i=y_in; }
        Complex(){}
        
        Complex operator + (const Complex& B) { return Complex(this->r+B.r,this->i+B.i); }
        Complex operator - (const Complex& B) { return Complex(this->r-B.r,this->i-B.i); }
        Complex operator * (const Complex& B) { return Complex(this->r*B.r-this->i*B.i,this->r*B.i+this->i*B.r); }
	};
}

namespace FFT
{
	const double eps=1e-7;
    int rev[1000010]={0};
    bool rev_f=0; 
    int revt=0,len=0;
    
    void Init(int len_in,int revt_in)
    {
        len=len_in; revt=revt_in;
    }
    
    void btfl()
    {
        if (!rev_f)
        {
                rev_f=1; revt--;
                for (int i=0;i<len;i++) rev[i]=( rev[i>>1]>>1 | ((i&1)<<revt) );
        }
    }
}

int main()
{
	
}