#include <stdio.h>

const int MAXM = 1010, MAXN = 110;
int head[MAXN], nxt[MAXM], to[MAXM], dis[MAXM], tot;
bool vis[MAXN];
int recover[MAXM];
int ans;
int n, c;

void Add(int x, int y, int diss);
void Dfs(int x, int k, int sum);
void Qsort(int l, int r);
void swap(int &a, int &b);
int min(int a, int b);

int main()
{
    freopen("t0.in", "r", stdin);
    int m;
    scanf("%d%d%d", &n, &m, &c);
    int u, v, w;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        Add(u, v, w);
    }
    ans = 2147483647;
    
    Dfs(1, 0, 0);
    
    printf("%d", ans);
}

void Add(int x, int y, int diss)
{
    tot++;
    nxt[tot] = head[x];
    to[tot] = y;
    dis[tot] = diss;
    head[x] = tot;
}

void Dfs(int x, int k, int sum) //现在在x点，已经走过k条边，路上边权和为sum
{
    if (x == n)
    {
        int tmp = 0;
        int tmpc = sum - c;
        Qsort(1, k);
        for (int i = k; i >= 1; i--)
        {
            tmpc -= recover[i];
            tmp++;
            if (tmpc <= 0)
            {
                break;
            }
        }
        ans = min(ans, tmp);
        return;
    }
    for (int i = head[x]; i; i = nxt[i])
    {
        if (!vis[to[i]])
        {
            vis[to[i]] = 1;
            recover[k + 1] = dis[i];
            Dfs(to[i], k + 1, sum + dis[i]);
            vis[to[i]] = 0;
        }
    }
}

void Qsort(int l, int r) //对recover数组排序
{
    int i = l, j = r, mid = recover[(l + r) >> 1];
    while (i < j)
    {
        while (recover[i] < mid) i++;
        while (recover[j] > mid) j--;
        if (i <= j)
        {
            swap(recover[i], recover[j]);
            i++;
            j--;
        }
    }
    if (i < r) Qsort(i, r);
    if (l < j) Qsort(l ,j);
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

int min(int a, int b)
{
    return a < b ? a : b;
}
