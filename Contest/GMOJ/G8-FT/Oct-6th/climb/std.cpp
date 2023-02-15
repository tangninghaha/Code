#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int mod = 1e9 + 7;

/* Class */
struct Graph
{
    int head[MAXN];
    int nxt[MAXN];
    int to[MAXN];
    int tot;
    void Add(int, int);
};

/* Declaration */
void Dfs(int _x);
int main();
void Init();
void Clear(int);
int Max(int, int);

/* Variable */
int n;
int f[35][2];
int rt[35][2];
long long ans = 0;
long long twom[MAXN];
Graph G;
int a[MAXN];

/* Definition */
void Dfs(int _x)
{
    int size = 0;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        ++size;
        Dfs(G.to[i]);
    }
    int son, k, son_value;
    int k_last = 0;

    son = _x;
    son_value = a[son];
    k = 0;
    while (son_value)
    {
        son_value >>= 1;
        ++k;
    }
    k_last = Max(k, k_last);
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        son = G.to[i];
        son_value = a[son];
        k = 0;
        while (son_value)
        {
            son_value >>= 1;
            ++k;
        }
        k_last = Max(k, k_last);
    }

    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        son = G.to[i];
        son_value = a[son];
        k = 0;
        for (int j = 1; j <= k_last; ++j)
        {
            ++f[++k][son_value & 1];
            son_value >>= 1;
        }
    }
    if (_x != 1)
    {
        son = _x;
        son_value = a[son];
        k = 0;
        for (int j = 1; j <= k_last; ++j)
        {
            ++f[++k][son_value & 1];
            son_value >>= 1;
        }
        k_last = Max(k, k_last);
    }
    else
    if (_x == 1)
    {
        son = _x;
        son_value = a[son];
        k = 0;
        for (int j = 1; j <= k_last; ++j)
        {
            ++rt[++k][son_value & 1];
            son_value >>= 1;
        }
        k_last = Max(k, k_last);
    }
    long long sum = 0;
    for (int i = 1; i <= k_last; ++i)
    {
        if ((!f[i][1]) && (!rt[i][1]))
            continue;
        if (!f[i][1])
            sum += twom[f[i][0]] * twom[i - 1];
        else
        sum += (twom[f[i][1] - 1 + f[i][0]]) * twom[i - 1];
        sum %= mod;
    }
    sum -= a[_x];
    sum = (sum % mod + mod) % mod;
    if (_x != 1)
    {
        for (int i = G.head[_x]; i; i = G.nxt[i])
        {
            sum -= a[G.to[i]];
            sum = (sum % mod + mod) % mod;
        }
        Clear(k_last);
    }
    ans += sum * twom[n - 1 - size - (_x != 1)];
    ans %= mod;
    return;
}
void Init()
{
    twom[0] = 1;
    for (int i = 1; i <= 1e5; ++i)
    {
        twom[i] = twom[i - 1] << 1;
        twom[i] %= mod;
    }
    return;
}
int main()
{
    Init();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    int fa;
    for (int i = 2; i <= n; ++i)
    {
        scanf("%d", &fa);
        G.Add(fa, i);
    }
    Dfs(1);
    printf("%lld", ans);
    return 0;
}
void Clear(int sz)
{
    for (int i = 1; i <= sz; ++i)
    {
        f[i][0] = f[i][1] = 0;
    }
}

int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}
