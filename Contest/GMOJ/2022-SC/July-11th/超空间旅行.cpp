#include <stdio.h>
#include <cmath>
const int MAXN = 505, MAXM = 10005;
int head[MAXN], nxt[MAXM], to[MAXM], tot;
struct E
{
    bool x;
    int num;
};
E dis[MAXM];
E Read();
void Add(int x, int y, E diss);
void Dfs(int x, int ed, int num_x, int cnst);
bool vis[MAXN];
int minb = 1000000010, cnstb = 0;
bool pd, ifans;
int min(int a, int b);
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        Add(u, v, Read());
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        pd = false;
        ifans = false;
        minb = 1000000010, cnstb = 1000000010;
        scanf("%d%d", &u, &v);
        Dfs(u, v, 0, 0);
        if (!ifans) printf("0 0\n");
        else if (pd) printf("%d %d\n", ceil(1.0 * cnstb / minb), 0);
        else printf("inf\n");
    }
    return 0;
}
void Dfs(int x, int ed, int num_x, int cnst)
{
    if (x == ed)
    {
        if (num_x == 0)
        {
            cnstb = min(cnstb, cnst);
            pd = true;
            return;
        }
        ifans = true;
        minb = min(num_x, minb);
        return;
    }
    for (int i = head[x]; i; i = nxt[i])
    {
        if (!vis[to[i]])
        {
            vis[to[i]] = true;
            Dfs(to[i], ed, num_x + dis[i].x, cnst + dis[i].num);
            vis[to[i]] = false;
        }
    }
}
E Read()
{
    E ret;
    char cha;
    cha = getchar();
    while ((cha < '0' || cha > '9') && (cha != 'x'))
    {
        cha = getchar();
    }
    if (cha == 'x')
    {
        ret.x = true;
        ret.num = 0;
        return ret;
    }
    ret.x = false;
    while (cha >= '0' && cha <= '9')
    {
        ret.num = ret.num * 10 + cha - '0';
        cha = getchar();
    }
    return ret;
}
void Add(int x, int y, E diss)
{
    ++tot;
    to[tot] = y;
    nxt[tot] = head[x];
    dis[tot] = diss;
    head[x] = tot;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
