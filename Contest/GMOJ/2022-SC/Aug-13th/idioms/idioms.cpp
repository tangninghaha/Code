#include <cstdio>

/* Constant */
const int MAXN = 5e5 + 5, MAXM = 5e5 + 5;
const int INF = 1e8 + 5;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXM];
        int to[MAXM];
        int tot;
        void Add(int, int);
};

/* Declaration */
void Dfs(int, bool);
int main();
void FileIO();

/* Variable */
int f[MAXN][2];
bool vis[MAXN][2];
bool pd[MAXN][2];
Graph g;

/* Definition */
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        g.Add(u, v);
    }
    for (int i = 1; i <= n; ++i)
    {
        Dfs(i, 0);
    }
    for (int i = 1; i <= n; ++i)
    {
        printf("%d\n", f[i][0] == INF ? -1 : f[i][0]);
    }
    return 0;
}
void Dfs(int x, bool pl)
{
    if (vis[x][pl])
        return;
    int n_ans;
    if (!pl)
        n_ans = INF;
    else
        n_ans = 0;
    pd[x][pl] = true;
    vis[x][pl] = true;
    for (int i = g.head[x]; i; i = g.nxt[i])
    {
        if (pl == 0)
        {
            Dfs(g.to[i], !pl);
            if (f[g.to[i]][1] < n_ans)
            {
                n_ans = f[g.to[i]][1] + 1;
            }
        }
        else
        {
            Dfs(g.to[i], !pl);
            if (pd[g.to[i]][0])
            {
                n_ans = INF;
            }
            if (f[g.to[i]][0] > n_ans)
            {
                n_ans = f[g.to[i]][0] + 1;
            }
        }
    }
    if (!pl && !g.head[x])
    {
        f[x][pl] = 0;
    }
    else if (pl && !g.head[x])
    {
        f[x][pl] = 0;
    }
    else
    {
        f[x][pl] = n_ans;
    }
    pd[x][pl] = false;
    return;
}
void FileIO()
{
    freopen("idioms.in", "r", stdin);
    freopen("idioms.out", "w", stdout);
    return;
}
void Graph::Add(int u, int v)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    head[u] = tot;
    return;
}
