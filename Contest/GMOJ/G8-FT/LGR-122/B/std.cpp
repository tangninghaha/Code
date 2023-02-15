#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 5005;

/* class */
struct Graph
{
    int head[MAXN];
    int to[MAXN * 2];
    int nxt[MAXN * 2];
    int tot;
    void Add(int _u, int _v);
};

/* Declaration */
void Dfs(int _x);
int main();
long long Sovle();
long long Min(long long, long long);

/* Variable */
int f[MAXN];
int n;
Graph G;

int fa[MAXN];
int size[MAXN];

long long g[MAXN];
int p[MAXN];
int temp_p[MAXN];

/* Definition */
void Dfs(int _x)
{
    memset(p, 127 / 3, sizeof(p));
    int sz = 1;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == fa[_x])
            continue;
        fa[G.to[i]] = _x;
        Dfs(G.to[i]);
        sz += size[G.to[i]];
        for (int j = 0; j <= sz; ++j) //总个数
        {
            for (int k = 0; k <= size[G.to[i]]; ++k) //当前儿子留下个数
            {
                if (k > j)
                    break;
                p[j] = Min(p[j - k] + temp_p[k] + g[G.to[i]], p[j]);
            }
        }
    }
    size[_x] = sz;
    for (int i = 0; i <= size[_x]; ++i)
    {
        g[i] = Min(g[i], p[i] + f[size[i] - i]);
        temp_p[i] = p[i];
    }
    return;
}
long long Sovle()
{
    Dfs(1);
    return g[1];
}
void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
    {
        scanf("%d", &f[i]);
    }
    int _u, _v;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &_u, &_v);
        G.Add(_u, _v);
        G.Add(_v, _u);
    }
    printf("%lld", Sovle());
    return 0;
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
