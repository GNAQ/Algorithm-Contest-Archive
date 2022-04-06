#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
string s;
stack<int> preA, nxtC;
int sol[400010][2], scnt;
bool vis[400010];

int main()
{
	cin >> n >> s; n *= 2;
	
	int cAB, cBC, cAC, cA=0, cB=0, cC=0;
	for (int i=0;i<n;i++)
	{
		if (s[i] == 'A') cA++;
		if (s[i] == 'B') cB++;
		if (s[i] == 'C') cC++;
	}
	
	cAB = (cA+cB-cC) / 2;
	cBC = (cB+cC-cA) / 2;
	cAC = (cA+cC-cB) / 2;
	if (cAB < 0 || cBC < 0 || cAC < 0)
	{
		puts("NO");
		return 0;
	}
	
	for (int i=n-1;i>=0;i--)
		if (s[i] == 'C') nxtC.push(i);
	
	int curB = 0;
	for (int i=0;i<n;i++) 
	{
		if (s[i] == 'B')
		{
			curB++;
			if (curB<=cBC) // B - C
			{
				sol[++scnt][0] = i;
				sol[scnt][1] = nxtC.top(); 
				nxtC.pop();
			}
			else // A - B
			{
				sol[++scnt][0] = i;
				sol[scnt][1] = preA.top();
				preA.pop();
			}
			vis[sol[scnt][1]] = vis[sol[scnt][0]] = 1;
		}
		if (s[i] == 'A')
			preA.push(i);
		if ((!nxtC.empty()) && i == nxtC.top())
			nxtC.pop();
	}
	
	stack<int> stk;
	for (int i=0;i<n;i++) if (!vis[i])
	{
		if (s[i] == 'A')
			stk.push(i);
		else
		{
			if (stk.empty())
			{
				puts("NO");
				return 0;
			}
			else
			{
				sol[++scnt][0] = stk.top();
				sol[scnt][1] = i;
				stk.pop();
			}
		}
	}
	
	puts("YES");
	for (int i=1;i<=scnt;i++)
		printf("%d %d\n", min(sol[i][0], sol[i][1]) + 1, max(sol[i][0], sol[i][1]) + 1);
	
	return 0;
}