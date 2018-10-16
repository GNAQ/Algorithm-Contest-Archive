#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

vector<string> vec;

int main()
{
	srand(time(0));
	
	vec.push_back("佬");
	vec.push_back("金光");
	vec.push_back("生成器");
	vec.push_back("std");
	vec.push_back("阿克");
	vec.push_back("多项式");
	vec.push_back("反演");
	vec.push_back("秒切");
	vec.push_back("字符串");
	vec.push_back("巨");
	vec.push_back("神仙");
	vec.push_back("太强了");
	vec.push_back("傻逼题");
	vec.push_back("拿牌");
	
	int n; cin>>n;
	while (n--)
	{
		int tmp=abs(rand())%vec.size();
		::Sleep(100);
		cout<<vec[tmp];
	}
	
	cout<<endl;
	system("pause");
}