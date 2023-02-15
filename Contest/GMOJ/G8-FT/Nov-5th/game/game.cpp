#include <cstdio>
#include <algorithm> 
#include <ctime>

/* Constant */
const int MAXN = 5e5 + 5;
const long long BASE = 13331;
const int N = 5e5 + 5;

/* Class */
struct Graph
{
    int head[MAXN];
    int to[2 * MAXN];
    int nxt[2 * MAXN];
    long long dis[2 * MAXN];
    int tot;
    void Add(int, int, long long);
    void Init();
};

/* Declaration */
int main();
void Dfs(int, int, long long);

template <typename T>void Qsort(int, int, T *);
template <typename T>void Swap(T&, T&);

/* Variable */
Graph G;
long long w[N + 1];
long long d[MAXN];
std::pair<int, int> z_tmp[MAXN];

/* Definition */
int main()
{
    srand(time(0));
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout); 
    int n;
    int t;
    w[0] = 1;
    for (int i = 1; i <= N; ++i)
    {
        w[i] = w[i - 1] * BASE;
//        w[i] %= mod;
    }
    scanf("%d", &t);
    int x, y, z;
    long long ans;
    int last = 0, sum = 0;
    for (int fot = 1; fot <= t; ++fot)
    {
        G.Init();
        scanf("%d", &n);
        ans = (long long)n * (n - 1) / 2;
        for (int i = 1; i < n; ++i)
        {
            scanf("%d%d%d", &x, &y, &z);
            z_tmp[i].first = z;
            z_tmp[i].second = i;
            G.Add(x, y, 0);
            G.Add(y, x, 0);
        }
        Qsort(1, n - 1, z_tmp);
        z_tmp[0].first = -1;
        int last_lsh = 0, sum_lsh = 0;
        for (int i = 1; i < n; ++i)
        {
            if (z_tmp[i].first != z_tmp[last_lsh].first)
            {
                ++sum_lsh;
                last_lsh = i;
            }
            G.dis[2 * z_tmp[i].second - 1] = w[sum_lsh];
            G.dis[2 * z_tmp[i].second] = w[sum_lsh];
        }
        Dfs(1, 0, 0);
//        for (int i = 1; i <= n; ++i)
//        {
//            for (int j = i + 1; j <= n; ++j)
//            {
//                if (!(d[i] ^ d[j]))
//                {
//                    --ans;
//                }
//            }
//        }
        last = 0;
        sum = 0;
       	Qsort(1, n, d);
        for (int i = 1; i <= n; ++i)
        {
            if (d[i] == d[last])
            {
                ++sum;
            }
            else
            {
                ans -= (long long)sum * (sum - 1) / 2;
                sum = 1;
                last = i;
            }
        }
        if (last != n)
            ans -= (long long)sum * (sum - 1) / 2;
        printf("%lld\n", ans);
    }
    return 0;
}
void Dfs(int _x, int fa, long long nw)
{
    d[_x] = nw;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa)
        {
            Dfs(G.to[i], _x, nw ^ G.dis[i]);
        }
    }
    return;
}
void Graph::Add(int _u, int _v, long long _dis)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    dis[tot] = _dis;
    head[_u] = tot;
    return;
}
void Graph::Init()
{
    tot = 0;
    for (int i = 0; i < MAXN; ++i)
    {
        head[i] = 0;
    }
}
template <typename T>void Qsort(int l, int r, T *_a)
{
    int i = l, j = r;
    T mid = _a[(l + r) >>1];
    while (i <= j)
    {
        while (_a[i] < mid)
            ++i;
        while (_a[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(_a[i], _a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r, _a);
    if (l < j)
        Qsort(l, j, _a);
    return;
}
template <typename T>void Swap(T& _a, T& _b)
{
    T tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
