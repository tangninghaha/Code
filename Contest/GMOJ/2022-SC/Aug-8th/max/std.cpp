#include <stdio.h>

typedef long long int64;
const int MAXN = 305;
int a[MAXN][MAXN];
int64 s[MAXN][MAXN];
int64 bh[MAXN];
int64 sum[MAXN];

void FileIO();
int main();
int Max(int aa, int bb);
int Min(int aa, int bb);
void Qsort(int l, int r);
void Swap(int64 &aa, int64 &bb);

void FileIO()
{
    freopen("max.in", "r", stdin);
    freopen("max.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j]);
            s[j][i] = s[j][i - 1] + a[i][j];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i; j <= n; ++j)
        {
            for (int k = 1; k <= m; ++k)
            {
                sum[k] = sum[k - 1] + s[k][j] - s[k][i - 1];
                bh[k] = k;
            }
            Qsort(1, m);
            int64 min_num = m + 1;
            int last = 1;
            for (int k = 1; k <= m; ++k)
            {
                if (sum[k] > 0)
                {
                    ans = Max(ans, (j - i + 1) * bh[k]);
                }
                if (sum[last] < sum[k])
                {
                    while (sum[last] < sum[k] && last <= m)
                    {
                        min_num = Min(bh[last], min_num);
                        ++last;
                    }
                }
                if (min_num > bh[k])
                {
                    continue;
                }
                ans = Max(ans, (j - i + 1) * (bh[k] - min_num));
            }
        }
    }
    printf("%d", ans);
    return 0;
}
int Max(int aa, int bb)
{
    return aa > bb ? aa : bb;
}
int Min(int aa, int bb)
{
    return aa < bb ? aa : bb;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int64 mid = sum[(l + r) >> 1];
    while (i <= j)
    {
        while (sum[i] < mid)
        {
            ++i;
        }
        while (sum[j] > mid)
        {
            --j;
        }
        if (i <= j)
        {
            Swap(sum[i], sum[j]);
            Swap(bh[i], bh[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
}
void Swap(int64 &aa, int64 &bb)
{
    int64 tmp = aa;
    aa = bb;
    bb = tmp;
}
