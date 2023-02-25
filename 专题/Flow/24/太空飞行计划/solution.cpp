#include <cstdio>

/* Constant */
const int MAXN = 105;
const int MAXM = 10005;
const int INF = 1 << 30;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXM * 2];
        int to[MAXM *2];
        int f[MAXM * 2];
        int tot;
        void Add(int, int, int);
        Graph();
};
Graph::Graph()
{
    tot = 1;
}
void Graph::Add(int _x, int _y, int _f)
{
    ++tot;
    nxt[tot] = head[_x];
    to[tot] = _y;
    f[tot] = _f;
    head[_x] = tot;
    return;
}

/* Declaration */
int main();

void Bfs(int, int);
int Dfs(int, int, int, int);
int GetMaxFlow(int, int);

int Min(int, int);

/* Variable */
Graph G;

int d[MAXN];
int num[MAXN];
int cur[MAXN];

int queue[MAXN];

bool pd[MAXN];

/* Definitino */
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    int x;
    int sum = 0;
    char cha;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        sum += x;
        G.Add(0, i, x);
        G.Add(i, 0, 0);
        cha = getchar();
        while (cha != '\n')
        {
            x = 0;
            cha = getchar();
            while ((cha < '0' || cha > '9') && cha != '\n')
                cha = getchar();
            while (cha >= '0' && cha <= '9')
            {
                x = x * 10 + cha - '0';
                cha = getchar();
            }
            G.Add(i, x + n, INF);
            G.Add(x + n, i, 0);
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &x);
        G.Add(n + i, n + m + 1, x);
        G.Add(n + m + 1, n + i, 0);
    }
    int ans = sum - GetMaxFlow(0, n + m + 1);
    bool pd = false;
    for (int i = 1; i <= n; ++i)
        if (d[i] != n + m + 2)
        {
            if (pd)
                printf(" ");
            pd = true;
            printf("%d", i);
        }
    printf("\n");
    pd = false;
    for (int i = n + 1; i <= n + m; ++i)
        if (d[i] != n + m + 2)
        {
            if (pd)
                printf(" "); 
            pd = true;
            printf("%d", i - n);
        }
    printf("\n");
    printf("%d\n", ans);
    return 0;
}
int Dfs(int s, int t, int now, int flow)
{
    if (now == t)
        return flow;
    int f;
    int ret = 0;
//    bool ok = false;
    for (int i = cur[now]; i; i = G.nxt[i])
    {
        if (!G.f[i])
            continue;
        if (d[G.to[i]] != d[now] + 1)
            continue;
//        ok = true;
        f = Dfs(s, t, G.to[i], Min(flow, G.f[i]));
        cur[now] = i;
        ret += f;
        flow -= f;
        G.f[i] -= f;
        G.f[i ^ 1] += f;
        if (!flow)
            return ret;
    }
//    if (ok)
    return ret;
//    int minn = t + 1;
//    for (int i = G.head[now]; i; i = G.nxt[i])
//        if (G.f[i])
//            minn = Min(minn, d[G.to[i]] + 1);
//    --num[d[now]];
//    if (!num[d[now]])
//        d[s] = t + 1;
//    d[now] = minn;
//    ++num[d[now]];
    return ret;
}
void Bfs(int s, int t)
{
    for (int i = s; i <= t; ++i)
    {
        d[i] = t + 1;
    }
    d[s] = 0;
    int head = 0;
    int tail = 1;
    queue[1] = s;
    int now;
    while (head < tail)
    {
        ++head;
        now = queue[head];
//        ++num[d[now]];
        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (!G.f[i])
                continue;
            if (d[G.to[i]] > d[now] + 1)
            {
                d[G.to[i]] = d[now] + 1;
                ++tail;
                queue[tail] = G.to[i];
            }
        }
    }
    return;
}
int GetMaxFlow(int s, int t)
{
    int ret = 0;
    while (d[t] <= t)
    {
        Bfs(s, t);
        for (int i = s; i <= t; ++i)
            cur[i] = G.head[i];
        ret += Dfs(s, t, s, INF);
    }
    return ret;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
