#include <cstdio>

/* Constant */
const int MAXN = 2e5 + 5;
const long long INF = 1e15 + 7777;

/* Graph */
struct Graph
{
    int head[MAXN];
    int to[MAXN * 2];
    int nxt[MAXN * 2];
    int tot;
    void Add(int, int);
};

/* Declaration */
int main();
void Dfs(int, int, int);
void GetAns(int, int);
long long Min(long long, long long);

/* Variable */
long long ans[MAXN];
long long anss = INF;
int w[MAXN];
long long sz_w[MAXN];
Graph G;

/* Definition */
int main()
{
    freopen("plant.in", "r", stdin);
    freopen("plant.out", "w", stdout);

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &w[i]);
    }
    int _u, _v;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &_u, &_v);
        G.Add(_u, _v);
        G.Add(_v, _u);
    }
    Dfs(1, 0, 0);
    anss = ans[1];
    GetAns(1, 0);
    printf("%lld", anss);
    return 0;
}
void Dfs(int _x, int dep, int fa)
{
    sz_w[_x] = w[_x];
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == fa)
            continue;
        Dfs(G.to[i], dep + 1, _x);
        sz_w[_x] += sz_w[G.to[i]];
    }
    ans[1] += (long long) w[_x] * dep;
    return;
}
void GetAns(int _x, int fa)
{
    if (_x != 1)
    {
        ans[_x] = ans[fa] - sz_w[_x] + (sz_w[1] - sz_w[_x]);
        anss = Min(anss, ans[_x]);
    }
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == fa)
            continue;
        GetAns(G.to[i], _x);
    }
    return;
}
void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
