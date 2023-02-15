#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 55;
const int MAXM = 2605;
const long long INF = 1e17 + 5;
const int X = 1e4;

/* Class */
class Graph
{
    public:
        int head[MAXN * 2];
        int nxt[MAXM * 2];
        int to[MAXM * 2];
        long long f[MAXM * 2];
        int tot;
        void Add(int, int, long long);
        void Init();
};
void Graph::Add(int _u, int _v, long long _f)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    f[tot] = _f;
    head[_u] = tot;
    return;
}
void Graph::Init()
{
    tot = 1;
}

/* Declaration */
int main();

template<typename T> T Min(T, T);

void Bfs(int);
long long Dfs(int, int, int, long long);
long long GetMaxFlow(int, int);

/* Variable */
Graph FG;
Graph G;

int a[MAXN];
int b[MAXN];

int queue[MAXN * 2];

int d[MAXN * 2];
int num[MAXN * 2];
int cur[MAXN * 2];

bool pd[MAXN][MAXN];

int point_num;

/* Definition */
void Bfs(int s)
{
    queue[1] = s;
    int head = 0, tail = 1;

    for (int i = 0; i < point_num; ++i)
    {
        d[i] = point_num;
    }

    d[s] = 0;

    int now;
    while (head < tail)
    {
        ++head;
        now = queue[head];
        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (G.f[i])
                continue;
            if (d[G.to[i]] <= d[now] + 1)
                continue;
            d[G.to[i]] = d[now] + 1;
            ++num[d[G.to[i]]];
            ++tail;
            queue[tail] = G.to[i];
        }
    }
    return;
}
long long Dfs(int s, int now, int t, long long flow)
{
    if (now == t)
    {
        return flow;
    }
    long long f;
    long long ret = 0;
    bool ok = false;
    for (int i = cur[now]; i; i = G.nxt[i])
    {
        if (!G.f[i])
            continue;
        if (d[G.to[i]] != d[now] - 1)
            continue;
        ok = true;
        f = Dfs(s, G.to[i], t, Min(flow, G.f[i]));
        G.f[i] -= f;
        G.f[i ^ 1] += f;
        ret += f;
        flow -= f;
        cur[now] = i;
        if (!flow)
        {
            return ret;
        }
    }
    if (!ok)
    {
        int minn = point_num;
        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (!G.f[i])
                continue;
            minn = Min(minn, d[G.to[i]] + 1);
        }
        --num[d[now]];
        if (!num[d[now]])
        {
            d[s] = point_num;
        }
        d[now] = minn;
        ++num[d[now]];
    }
    return ret;
}
long long GetMaxFlow(int s, int t)
{
    memset(num, 0, sizeof(0));
    Bfs(point_num - 1);
    long long ret = 0;
    while (d[s] < point_num)
    {
        for (int i = 0; i < point_num; ++i)
        {
            cur[i] = G.head[i];
        }
        ret += Dfs(s, s, t, INF);
    }
    return ret;
}
int main()
{
    freopen("war.in", "r", stdin);
    freopen("war.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &b[i]);
    }
    point_num = n + m + 2;
    FG.Init();
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &pd[i][j]);
            if (pd[i][j])
            {
                FG.Add(i, j + m, INF);
                FG.Add(j + m, i, 0);
            }
        }
    }
    int _st, _ed;
    _st = FG.tot + 1;
    for (int i = 1; i <= n; ++i)
    {
        FG.Add(i + m, point_num - 1, a[i] * X);
        FG.Add(point_num - 1, i + m, 0);
    }
    _ed = FG.tot;
    long long lbound = 0, rbound = 2e8;
    long long t;
    long long f;
    bool pdd;
    while (lbound <= rbound)
    {
        pdd = false;
        t = (lbound + rbound) / 2;
        G = FG;
        for (int i = 1; i <= m; ++i)
        {
            G.Add(0, i, t * b[i]);
            G.Add(i, 0, 0);
        }
        f = GetMaxFlow(0, point_num - 1);
        for (int i = _st; i <= _ed; i += 2)
        {
            if (G.f[i])
            {
                pdd = true;
                lbound = t + 1;
                break;
            }
        }
        if (!pdd)
        {
            rbound = t - 1;
        }
    }
    printf("%f", (double)t / X);
    return 0;
}
template<typename T> T Min(T _a, T _b)
{
    return _a < _b ? _a : _b;
}
