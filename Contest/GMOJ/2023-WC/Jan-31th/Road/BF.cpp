#include <cstdio>

/* Constant */
const int N = 5e4;

/* Class */
class Graph
{
    public:
        int head[N + 1];
        int nxt[2 * N + 1];
        int to[2 * N + 1];
        int tot;
        void Add(int _u, int _v)
        {
            ++tot;
            nxt[tot] = head[_u];
            to[tot] = _v;
            head[_u] = tot;
            return;
        }
};

/* Declaration */
int main();
void Init(int);
int GetLca(int, int);
int GetAns(int, int);

int Min(int, int);
int Max(int, int);

/* Variable */
int c[N + 1];
int dep[N + 1];
int fa[N + 1];
int z[N + 1];

Graph G;

/* Definition */
int main()
{
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    int x, y;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &x, &y);
        G.Add(x, y);
        G.Add(y, x);
    }
    Init(1);
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d%d", &x, &y);
        printf("%d\n", GetAns(x, y));
    }
    return 0;
}
void Init(int _x)
{
    dep[_x] = dep[fa[_x]] + 1;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == fa[_x])
            continue;
        fa[G.to[i]] = _x;
        Init(G.to[i]);
    }
    return;
}
int GetLca(int _x, int _y)
{
    while (dep[_x] != dep[_y])
        if (dep[_x] > dep[_y])
            _x = fa[_x];
        else
            _y = fa[_y];
    while (_x != _y)
    {
        _x = fa[_x];
        _y = fa[_y];
    }
    return _x;
}
int GetAns(int _x, int _y)
{
    int lca = GetLca(_x, _y);
    int minn = c[_x];
    int ans = 0;
    while (_x != fa[lca])
    {
        minn = Min(minn, c[_x]);
        ans = Max(ans, c[_x] - minn);
        _x = fa[_x];
    }
    int top = 0;
    while (_y != lca)
    {
        ++top;
        z[top] = _y;
        _y = fa[_y];
    }
    _y = z[top];
    while (top)
    {
        minn = Min(minn, c[_y]);
        ans = Max(ans, c[_y] - minn);
        --top;
        _y = z[top];
    }
    return ans;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
