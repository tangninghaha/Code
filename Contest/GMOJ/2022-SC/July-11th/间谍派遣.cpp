#include <stdio.h>
#define INF 1000000010
const int MAXN = 1005, MAXM = MAXN * MAXN;
int a[MAXM], b[MAXM];
int dis[MAXM], tot;
int fa[MAXN];
int gf(int x);
bool pd[MAXM];
void swap(int &a, int &b);
void Qsort(int l, int r);
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i)
    {
        fa[i] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            ++tot;
            scanf("%d", &dis[tot]);
            a[tot] = i;
            b[tot] = j;
            if (dis[tot] == 0)
            {
                --tot;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        ++tot;
        scanf("%d", &dis[tot]);
        a[tot] = i;
        b[tot] = 0;
    }
    Qsort(1, tot);
    int ans = 0;
    for (int j = 1; j <= tot; ++j)
    {
        if (gf(a[j]) != gf(b[j]))
        {
            fa[gf(a[j])] = fa[gf(b[j])];
            ans += dis[j];
        }
    }
    printf("%d", ans);
}
int gf(int x)
{
    if (x == fa[x]) return x;
    return fa[x] = gf(fa[x]);
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
    return;
}
void Qsort(int l, int r)
{
    int i = l, j = r, mid = dis[(l + r) >> 1];
    while (i <= j)
    {
        while (dis[i] < mid)
            ++i;
        while (dis[j] > mid)
            --j;
        if (i <= j)
        {
            swap(dis[i], dis[j]);
            swap(a[i], a[j]);
            swap(b[i], b[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
}
