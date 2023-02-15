#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXN * 2];
        int to[MAXN * 2];
        int tot;
        void Add(int, int);
};
void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}

/* Declaration */
int main();
void Dfs1(int, int, int);
void Dfs2(int);
int Max(int, int);
int Min(int, int);

/* Variable */
int dep[MAXN];
int root;
int root_jl;
int fa[MAXN];

int f[MAXN];
int g[MAXN][2];

Graph G;

/* Definition */
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int _u, _v;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &_u, &_v);
        G.Add(_u, _v);
        G.Add(_v, _u);
    }
    root_jl = n + 1;
    Dfs1(1, 0, 0);
    for (int i = 1; i <= n; ++i)
        f[i] = 0;
    Dfs2(root);
    int lbound = 1, rbound = n;
    int num = 0;
    int ans = 1 << 30;
    while (lbound <= rbound)
    {
        num = 0;
        int mid = lbound + rbound >> 1;
        for (int i = 1; i <= n; ++i)
        {
            if (f[i] - dep[i] > mid)
                ++num;
        }
        if (num <= k)
        {
            ans = Min(ans, mid);
            rbound = mid - 1;
        }
        else
        {
            lbound = mid + 1;
        }
    }
    printf("%d", ans);
    return 0;
}
void Dfs1(int _x, int _fa, int _dep)
{
    bool ok = false;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == _fa)
            continue;
        ok = true; 
        Dfs1(G.to[i], _x, _dep + 1);
        if (g[G.to[i]][0] > g[_x][0])
            g[_x][0] = g[G.to[i]][0];
        else if (g[G.to[i]][0] > g[_x][1])
            g[_x][1] = g[G.to[i]][0];
        d = Max(d, g[_x][0] + g[_x][1]);
    }
    return;
}
void Dfs2(int _x)
{
    dep[_x] = dep[fa[_x]] + 1;
    f[_x] = dep[_x];
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == fa[_x])
            continue;
        fa[G.to[i]] = _x;
        Dfs2(G.to[i]);
        f[_x] = Max(f[_x], f[G.to[i]]);
    }
    return;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
