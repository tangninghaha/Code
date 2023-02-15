#include <stdio.h>
const int MAXN = 1e4 + 1, MAXM = 4 * MAXN;
bool vis[MAXM];
int ans;
int max(int a, int b);
struct Graph
{
    int head[MAXN];
    int nxt[MAXM];
    int to[MAXM];
    int tot;
    void Add(int x, int y);
};
Graph g;
void Dfs(int x, int len);
int main()
{
    g.tot = 1;
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        g.Add(u, v);
        g.Add(v, u);
    }
    for (int i = 1; i <= n; ++i)
    {
        Dfs(i, 0);
    }
    printf("%d", ans);
    return 0;
}

void Dfs(int x, int len)
{
    if (x == 1)
    {
        ans = max(ans, len);
    }
    for (int i = g.head[x]; i; i = g.nxt[i])
    {
        if (!vis[i])
        {
            vis[i] = true;
            vis[i ^ 1] = true;
            Dfs(g.to[i], len + 1);
            vis[i] = false;
            vis[i ^ 1] = false;
        }
    }
    return;
}
void Graph::Add(int x, int y)
{
    ++tot;
    nxt[tot] = head[x];
    to[tot] = y;
    head[x] = tot;
    return;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
