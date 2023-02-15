#include <cstdio>

/* Constant */
const int MAXN = 2e5 + 5;
const int MAXM = 5e5 + 5;
const long long INF = 1e15 + 5;

/* Class */
struct Graph
{
    int head[MAXN];
    int nxt[MAXM * 2];
    int to[MAXM * 2];
    int value[MAXM * 2];
    int tot;
    void Add(int, int, int);
};
struct Heap
{
    long long a[MAXN];
    int bh[MAXN];
    int rk[MAXN];
    void Up(int);
    void Down(int);
    void Pop();
    int size;
};

/* Declaration */
long long Min(long long, long long);
template<typename T> void Swap(T&, T&);
int main();
void Dij(int, int, int);

/* Variable */
bool pd[MAXN];
Heap H;
long long dis[MAXN][2];
Graph G;

/* Definition */
void Graph::Add(int _u, int _v, int _value)
{
    ++tot;
    to[tot] = _v;
    nxt[tot] = head[_u];
    value[tot] = _value;
    head[_u] = tot;
    return;
}

int main()
{
    freopen("monogatari.in", "r", stdin);
    freopen("monogatari.out", "w", stdout);
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int u, v, w;
    for (int i = 1; i < m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        G.Add(u, v, w);
        G.Add(v, u, w);
    }
    scanf("%d%d", &u, &v);
    Dij(1, n, 0);
    Dij(n, n, 1);
    int x;
    long long ans;
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &x);
        ans = Min(Min(dis[n][0], dis[u][0] + x + dis[v][1]), dis[v][0] + x + dis[u][1]);
        if (ans >= INF)
            printf("+Inf\n");
        else
            printf("%lld\n", ans);
    }
    return 0;
}
void Dij(int s, int n, int k)
{
    for (int i = 1; i <= n; ++i)
    {
        dis[i][k] = INF;
    }
    dis[s][k] = 0;
    H.size = n;
    for (int i = 1; i <= n; ++i)
    {
        H.bh[i] = i;
        H.a[i] = dis[i][k];
        H.rk[i] = i;
        pd[i] = false;
    }
    Swap(H.a[s], H.a[1]);
    Swap(H.bh[s], H.bh[1]);
    Swap(H.rk[s], H.rk[1]);
    int now;
    for (int i = 1; i <= n; ++i)
    {
        now = H.bh[1];
        H.Pop();
        pd[now] = true;
        for (int j = G.head[now]; j; j = G.nxt[j])
        {
            if (dis[G.to[j]][k] > dis[now][k] + G.value[j] && !pd[G.to[j]])
            {
                dis[G.to[j]][k] = dis[now][k] + G.value[j];
                H.a[H.rk[G.to[j]]] = dis[G.to[j]][k];
                H.Up(H.rk[G.to[j]]);
            }
        }
    }
    return;
}
void Heap::Up(int _x)
{
    int nxt = _x / 2;
    while (nxt && a[_x] < a[nxt])
    {
        Swap(a[_x], a[nxt]);
        Swap(bh[_x], bh[nxt]);
        rk[bh[_x]] = _x;
        rk[bh[nxt]] = nxt;
        _x = nxt;
        nxt = _x / 2;
    }
    return;
}
void Heap::Down(int _x)
{
    int nxt = _x * 2;
    while ((nxt <= size && a[nxt] < a[_x])
           || (nxt + 1 <= size && a[nxt + 1] < a[_x]))
    {
        if (a[nxt + 1] < a[nxt] && nxt + 1 <= size)
            ++nxt;
        Swap(a[_x], a[nxt]);
        Swap(bh[_x], bh[nxt]);
        rk[bh[_x]] = _x;
        rk[bh[nxt]] = nxt;
        _x = nxt;
        nxt = _x * 2;
    }
    return;
}
void Heap::Pop()
{
    Swap(a[1], a[size]);
    Swap(bh[1], bh[size]);
    rk[bh[1]] = 1;
    rk[bh[size]] = size;
    --size;
    Down(1);
    return;
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
template<typename T> void Swap(T& _a, T& _b)
{
    T t = _a;
    _a = _b;
    _b = t;
    return;
}

