#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m;
struct ed
{
    int pre, to, cap;
} edge[200010];
int at = 1, ptr[100010];
int ss, tt, MAX_NODE;

void Is(int fx, int tx, int cx)
{
    edge[++at].pre = ptr[fx];
    edge[at].to = tx;
    edge[at].cap = cx;
    ptr[fx] = at;
    edge[++at].pre = ptr[tx];
    edge[at].to = fx;
    ptr[tx] = at;
}

int lvl[100010], cur[100010];
queue<int> que;
int BFS()
{
    int u;
    for (int i = 0; i <= MAX_NODE; i++)
        lvl[i] = 0;
    lvl[ss] = 1;
    que.push(ss);
    while (!que.empty())
    {
        u = que.front();
        que.pop();
        for (int e = ptr[u]; e; e = edge[e].pre)
            if (!lvl[edge[e].to] && edge[e].cap)
            {
                lvl[edge[e].to] = lvl[u] + 1;
                que.push(edge[e].to);
            }
    }
    if (!lvl[tt])
        return false;
    for (int i = 0; i <= MAX_NODE; i++)
        cur[i] = ptr[i];
    return true;
}

int DFS(int now, int minf)
{
    if (!minf || now == tt)
        return minf;
    int needf, sumf = 0;
    
    for (int e = cur[now]; e; e = edge[e].pre)
        if (lvl[edge[e].to] == lvl[now] + 1)
        {
            cur[now] = e;
            if (needf = DFS(edge[e].to, min(minf, edge[e].cap)))
            {
                sumf += needf;
                minf -= needf;
                edge[e].cap -= needf;
                edge[e ^ 1].cap += needf;
                if (!minf) break; // 这个地方涉及当前弧优化
            }
        }
    return sumf;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &ss, &tt);
    MAX_NODE = n + 2;
    int u, v, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &c);
        Is(u, v, c);
    }

    int ans = 0;
    while (BFS())
        ans += DFS(ss, 2 * 1e9);
    printf("%d\n", ans);
    return 0;
}