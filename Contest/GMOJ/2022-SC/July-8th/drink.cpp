#include <stdio.h>
#include <cstring>

const int MAXN = 25, MAXM = 25;
const long long mod = 998244353;
struct Edge
{
    Edge();
    int head[MAXN];
    int nxt[MAXM * 2];
    int to[MAXM * 2];
    int tot;
    void Add(int x, int y);
};
int n, m;
Edge G1;
Edge G2;
int dy[MAXN];
int fdy[MAXN];
bool pd[MAXN];
void Dfs(int x);
void Check(int x);
bool vis[MAXN];
long long ans;
int main()
{
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        G1.Add(u, v);
        G1.Add(v, u);
    }
    for (int i = 1; i <= n - m - 1; ++i)
    {
        scanf("%d%d", &u, &v);
        G2.Add(u, v);
        G2.Add(v, u);
    }
    Dfs(1);
    printf("%lld", ans);
}

void Edge::Add(int x, int y)
{
    tot++;
    to[tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
    return;
}

Edge::Edge()
{
    tot = 0;
}

void Dfs(int x)
{
    if (x > n)
    {
        memset(vis, 0, sizeof(vis));
        Check(1);
        for (int i = 1; i <= n; ++i)
        {
            if (!vis[i]) return;
        }
        ++ans;
        ans %= mod;
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (pd[i]) continue;
        dy[x] = i;
        fdy[i] = x;
        pd[i] = true;
        Dfs(x + 1);
        pd[i] = false;
    }
    return;
}
void Check(int x)
{
    for (int i = G1.head[x]; i; i = G1.nxt[i])
    {
        if (!vis[G1.to[i]])
        {
            vis[G1.to[i]] = true;
            Dfs(G1.to[i]);
        }
    }
    for (int i = G2.head[dy[x]]; i; i = G2.nxt[i])
    {
        if (!vis[fdy[G2.to[i]]])
        {
            vis[fdy[G2.to[i]]] = true;
            Dfs(fdy[G2.to[i]]);
        }
    }
}
