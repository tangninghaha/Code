#include <cstdio>

/* Constant */
const int MAXN = 25;
const int MAXM = MAXN * MAXN * 2 * 6;
const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
const int INF = 1e9 + 7;

/* Class */
class Graph
{
    public:
        int head[MAXN * MAXN * 2];
        int nxt[MAXM];
        int to[MAXM];
        int f[MAXM];
        int tot;
        void Add(int, int, int);
        Graph();
};
void Graph::Add(int _u, int _v, int _f)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    f[tot] = _f;
    head[_u] = tot;
    return;
}
Graph::Graph()
{
    tot = 1;
    return;
}

/* Declaration */
int main();
int Read();

void Bfs(int, int);
int Dfs(int, int, int);
int GetMaxFlow(int, int);
void Upload(int);

int Min(int, int);

/* Variable */
int n, m;
int profit[MAXN][MAXN];
int cost[MAXN][MAXN];

Graph G;
int d[MAXN * MAXN * 2];
int queue[MAXN * MAXN * 2];
int point_num;
int cur[MAXN * MAXN * 2];

/* Definition */
int main()
{
    freopen("revolution.in", "r", stdin);
    freopen("revolution.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cost[i][j] = Read();
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            profit[i][j] = Read();
            sum += profit[i][j];
        }
    }
    int bh;
    int nxt, nx, ny;
    int ed = n * m * 2 + 1;
    int num = n * m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            bh = (i - 1) * m + j;
            if ((i & 1) ^ (j & 1))
            {
                G.Add(bh, ed, cost[i][j]);
                G.Add(ed, bh, 0);
                G.Add(bh + num, bh, profit[i][j]);
                G.Add(bh, bh + num, 0);
                for (int t = 0; t < 4; ++t)
                {
                    nx = i + dx[t];
                    ny = j + dy[t];
                    nxt = (nx - 1) * m + ny;
                    if (nx <= 0 || ny <= 0 || nx > n || ny > m)
                        continue;
                    G.Add(nxt, bh + num, INF);
                    G.Add(bh + num, nxt, 0);
                }
            }
            else
            {
                G.Add(0, bh, cost[i][j]);
                G.Add(bh, 0, 0);
                G.Add(bh, bh + num, profit[i][j]);
                G.Add(bh + num, bh, 0);
                for (int t = 0; t < 4; ++t)
                {
                    nx = i + dx[t];
                    ny = j + dy[t];
                    nxt = (nx - 1) * m + ny;
                    if (nx <= 0 || ny <= 0 || nx > n || ny > m)
                        continue;
                    G.Add(bh + num, nxt, INF);
                    G.Add(nxt, bh + num, 0);
                }
            }
        }
    }
    point_num = ed + 1;

    printf("%d", sum - GetMaxFlow(0, ed));
    return 0;
}
int Read()
{
    char cha = getchar();
    while (!(cha >= '0' && cha <= '9') && !(cha >= 'a' && cha <= 'z') && !(cha >= 'A' && cha <= 'Z'))
        cha = getchar();
    if (cha >= '0' && cha <= '9')
        return cha - '0';
    if (cha >= 'a' && cha <= 'z')
        return cha - 'a' + 10;
    if (cha >= 'A' && cha <= 'Z')
        return cha - 'A' + 36;
    return 0;
}

void Bfs(int s, int t)
{
    int head = 0, tail = 1;
    for (int i = 0; i < point_num; ++i)
    {
        d[i] = point_num;
        cur[i] = G.head[i];
    }
    queue[1] = s;
    d[s] = 0;
    int now;
    while (head < tail)
    {
        ++head;
        now = queue[head];
        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (!G.f[i])
                continue;
            if (d[G.to[i]] <= d[now] + 1)
                continue;
            d[G.to[i]] = d[now] + 1;
            ++tail;
            queue[tail] = G.to[i];
        }
    }
    return;
}
int Dfs(int _x, int t, int flow)
{
    if (_x == t)
    {
        return flow;
    }
    int ret = 0;
    int f;
    for (int i = cur[_x]; i; i = G.nxt[i])
    {
        if (G.f[i] > 0 && d[G.to[i]] == d[_x] + 1)
        {
            f = Dfs(G.to[i], t, Min(flow, G.f[i]));
            flow -= f;
            ret += f;
            G.f[i] -= f;
            G.f[i ^ 1] += f;
            cur[_x] = i;
            if (!flow)
            {
                return ret;
            }
        }
    }
    return ret;
}
int GetMaxFlow(int s, int t)
{
    int max_flow = 0;
    while (d[t] < point_num)
    {
        Bfs(s, t);
        max_flow += Dfs(s, t, INF);
    }
    return max_flow;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
