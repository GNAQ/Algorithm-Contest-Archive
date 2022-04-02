#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	getline(cin, s);
	
	while (s.find(" ") != string::npos)
		s.replace(s.find(" "), 1, "");
	
	cout << s;
	
}