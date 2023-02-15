#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Class */
class Edge
{
    int head[MAXN];
    int to[MAXN * 2];
    int nxt[MAXN * 2];
    int degree[MAXN];
    int tot;
    void Add(int, int);
};

/* Declaration */
int main();

/* Variable */
Edge G;

/* Definition */
void Edge::Add(int _u, int _v)
{
    ++tot;
    to[tot] = _v;
    nxt[tot] = head[_u];
    ++degree[_u];
    head[_u] = tot;
    return;
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        int n;
        scanf("%d", &n);
        int x, y;
        for (int i = 1; i < n; ++i)
        {
            scanf("%d%d", &x, &y);
            G.Add(x, y);
            G.Add(y, x);
        }
    }
}
