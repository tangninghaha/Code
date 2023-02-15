#include <stdio.h>
#include <cstring>
#define INF 1000000010
#define MAXN 1000

const long long mod = 2147483647;
int a[MAXN][MAXN];
int f[MAXN], dis[MAXN];
int bh[MAXN];
bool vis[MAXN];

void Qsort(int l, int r);
void swap(int &a, int &b);
int midn(int a, int b, int c);

int main()
{
    freopen("treecount.in", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        --u;
        --v;
        a[u][v] = w;
        a[v][u] = w;
    }
    
    memset(dis, 127 / 3, sizeof(dis));
    int minn, minp;
    dis[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        minn = INF;
        for (int j = 0; j < n; ++j)
        {
            if (dis[j] < minn && !vis[j])
            {
                minn = dis[j];
                minp = j;
            }
        }
        vis[minp] = true;
        for (int j = 0; j < n; ++j)
        {
            if (a[minp][j])
            {
                if (dis[minp] + a[minp][j] < dis[j] && !vis[j])
                {
                    dis[j] = dis[minp] + a[minp][j];
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        bh[i] = i;
    }
    Qsort(0, n - 1);
    long long ans = 1;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (dis[i] == dis[j]) break;
            if (dis[j] + a[bh[j]][bh[i]] == dis[i] && a[bh[j]][bh[i]])
            {
                f[i]++;
            }
        }

        ans *= f[i];
        ans %= mod;
    }
    printf("%lld", ans);
}

void Qsort(int l, int r)
{
    int i = l, j = r, mid = dis[l + r >> 1];
    while (i < j)
    {
        while(dis[i] < mid) ++i;
        while(dis[j] > mid) --j;
        if (i <= j)
        {
            swap(dis[i], dis[j]);
            swap(bh[i], bh[j]);
            ++i;
            --j;
        }
    }
    if (i < r) Qsort(i, r);
    if (l < j) Qsort(l, j);
    return;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
    return;
}
