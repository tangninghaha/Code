#include <stdio.h>
#include <cstring>
const int MAXM = 1e5 + 5, MAXN = 2e5 + 5, MAXX = 5e5 + 5, N = 2e5, MAXQ = 1e7;
int l[MAXM], r[MAXM];
int head[MAXN], nxt[MAXX], to[MAXX], diss[MAXX], tot;
int num[MAXN];
void Add(int u, int v, int w);
int queue[MAXQ], dis[MAXN];
void SPFA();
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &l[i], &r[i]);
        Add(l[i] - 1, r[i], 1);
        Add(r[i], l[i] - 1, -1);
    }
    for (int i = 1; i < n; ++i)
    {
        Add(i, i + 1, 1);
        Add(i + 1, i, 0);
    }
    memset(dis, 127 / 3, sizeof(dis));
    SPFA();
    return 0;
}
void Add(int u, int v, int w)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    diss[tot] = w;
    head[u] = tot;
    return;
}
void SPFA()
{
    int head_bound = 0, tail_bound = 1;
    queue[1] = 1;
    dis[1] = 0;
    while (head_bound < tail_bound)
    {
        ++head_bound;
        int now = queue[head_bound];
        for (int i = head[now]; i; i = nxt[i])
        {
            if (dis[now] + diss[i] < dis[to[i]])
            {
                dis[to[i]] = diss[i] + dis[now];
                ++tail_bound;
                queue[tail_bound] = to[i];
                ++num[to[i]];
                if (num[to[i]] >= N)
                {
                    printf("-1");
                    return;
                }
            }
        }
    }
    printf("%d", dis[n]);
    return;
}
