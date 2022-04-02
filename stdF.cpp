#include <iostream>
#include <cstdio>
#include <cstring>

#define ll long long

using namespace std;

template <typename T>
inline void read(T &s)
{
    s = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    s *= f;
}

const int N = 4e6 + 99;
struct E
{
    int tot, head[N], nxt[N], to[N];
    void add(int x, int y)
    {
        tot++;
        nxt[tot] = head[x];
        to[tot] = y;
        head[x] = tot;
    }
} G;

int Time, dfn[N], low[N];
int top, stc[N];
int Color, co[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++Time;
    stc[++top] = u;
    for (int i = G.head[u]; i; i = G.nxt[i])
    {
        int v = G.to[i];
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (!co[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        co[u] = ++Color;
        while (stc[top] != u)
            co[stc[top--]] = Color;
        top--;
    }
}
// r前缀
// r->0
// r<-1
int op[N], vis[N], l[N], r[N];
int main()
{
    int k1, n, m, k2;
    read(k1);
    read(n);
    read(m);
    read(k2);
    while (k1--)
    {
        int x, y;
        read(x);
        read(y);
        G.add(x, y + n);
        G.add(y, x + n);
    }
    for (int i = 1; i <= n; i++)
    {
        read(l[i]);
        read(r[i]);
        G.add(2 * n + r[i], i);
        G.add(i + n, 2 * n + m + r[i]);
        if (l[i] != 1)
            G.add(i + n, 2 * n + l[i] - 1), G.add(2 * n + m + l[i] - 1, i);
    }
    for (int i = 1; i <= m; i++)
    {
        if (i != 1)
            G.add(2 * n + i, 2 * n + i - 1);
        if (i != m)
            G.add(2 * n + m + i, 2 * n + m + i + 1);
    }
    while (k2--)
    {
        int x, y;
        read(x);
        read(y);
        G.add(x + n, y);
        G.add(y + n, x);
    }

    for (int i = 1; i <= 2 * n + 2 * m; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (co[i] == co[i + n])
            return printf("-1\n"), 0;
    for (int i = 1; i <= n; i++)
        op[co[i]] = co[i + n], op[co[i + n]] = co[i];
    for (int i = 1; i <= Color; i++)
        if (!vis[i])
            vis[i] = 1, vis[op[i]] = -1;
    int maxl = 0, ans = 0;
    ;
    for (int i = 1; i <= n; i++)
        if (vis[co[i + n]] == 1)
            maxl = max(maxl, l[i]), ans++;
    printf("%d %d\n", ans, maxl);
    for (int i = 1; i <= n; i++)
        if (vis[co[i + n]] == 1)
            printf("%d ", i);

    return 0;
}
