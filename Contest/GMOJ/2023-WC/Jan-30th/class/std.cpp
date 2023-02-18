#include <cstdio>

/* Constant */
const int N = 2500;
const int mod = 1e9 + 7;

/* Class */
class Graph
{
    public:
        int head[N + 1];
        int nxt[2 * N + 1];
        int to[2 * N + 1];
        int dis[2 * N + 1];
        int tot;
        void Add(int, int, int);
};
void Graph::Add(int _u, int _v, int _dis)
{
    ++tot;
    to[tot] = _v;
    nxt[tot] = head[_u];
    dis[tot] = _dis;
    head[_u] = tot;
    return;
}

/* Declaration */
int main();
int Min(int, int);

void Dfs(int, int, int);

/* Variable */
int size[N + 1];
int c[2 * N + 1][2 * N + 1];
long long pow[2 * N + 1][2 * N + 1];
int n, m;

long long ans = 0;

Graph G;

/* Definition */
int main()
{
    freopen("class.in", "r", stdin);
    freopen("class.out", "w", stdout);
    scanf("%d%d", &n, &m);
    int m2 = 2 * m;
    c[0][0] = 1;
    for (int i = 1; i <= m2; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
        {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
            c[i][j] %= mod;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        pow[i][0] = 1;
        for (int j = 1; j <= m2; ++j)
        {
            pow[i][j] = pow[i][j - 1] * i;
            pow[i][j] %= mod;
        }
    }
    int u, v, w;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        G.Add(u, v, w);
        G.Add(v, u, w);
    }

    Dfs(1, 0, 0);
//    ans *= 2;
//    ans %= mod;
    printf("%lld", ans);
    return 0;
}
void Dfs(int now, int fa, int from_dis)
{
    size[now] = 1;
    long long sum;
    for (int i = G.head[now]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa)
        {
            Dfs(G.to[i], now, G.dis[i]);
            size[now] += size[G.to[i]];
        }
    }
    if (!from_dis)
        return;
    for (int j = 1; j <= 2 * m; ++j)
    {
        sum = ((((((((long long)c[2 * m][j] * from_dis) % mod) * Min(j, 2 * m - j)) % mod) * pow[size[now]][j]) % mod) * pow[n - size[now]][2 * m - j]) % mod;
        ans += sum;
        ans %= mod;
//        sum = (((((((c[2 * m][j] * from_dis) % mod) * j) % mod) * pow[size[now]][2 * m - j]) % mod) * pow[n - size[now]][j]) % mod;
//        ans += sum;
//        ans %= mod;
    }
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
