#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

vector<string> vec;

int main()
{
	srand(time(0));
	
	vec.push_back("��");
	vec.push_back("���");
	vec.push_back("������");
	vec.push_back("std");
	vec.push_back("����");
	vec.push_back("����ʽ");
	vec.push_back("����");
	vec.push_back("����");
	vec.push_back("�ַ���");
	vec.push_back("��");
	vec.push_back("����");
	vec.push_back("̫ǿ��");
	vec.push_back("ɵ����");
	vec.push_back("����");
	
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