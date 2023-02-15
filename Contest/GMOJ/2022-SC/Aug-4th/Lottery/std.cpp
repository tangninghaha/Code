#include <stdio.h>


const int MAXN = 10005;
int a[MAXN];
int ans[MAXN];
int tans[105][MAXN];
int sum[MAXN];
int nerst[MAXN];
int pans[105][MAXN];
int x[105];
int bh[105];
int rk[105];

int Max(int aa, int bb);
void FileIO();
int main();
void Qsort(int l, int r);
void Sovle(int n, int l, int q);
void Swap(int &aa, int &bb);

int Max(int aa, int bb)
{
	return aa > bb ? aa : bb;
}
void FileIO()
{
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);
    return;
}
int main()
{
	FileIO();
    int n, l;
    scanf("%d%d", &n, &l);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d", &x[i]);
        bh[i] = i;
    }
    Qsort(1, q);
    for (int i = 1; i <= q; ++i)
    {
        rk[bh[i]] = i;
    }
    for (int i = 1; i <= q; ++i)
    {
        nerst[x[i]] = i;
    }
    int zz = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (i > x[zz] && zz <= q)
        {
            ++zz;
        }
        if (i <= x[zz])
        {
            nerst[i] = zz;
        }
        else
        {
            nerst[i] = 104;
        }
    }
    Sovle(n, l, q);
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int mid = x[(l + r) >> 1];
    while (i <= j)
    {
        while (x[i] < mid)
            ++i;
        while (x[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(x[i], x[j]);
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
void Sovle(int n, int l, int q)
{
    int ed = n - l + 1;
    for (int i = 1; i <= n - l; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            sum[j] = 0;
            ans[j] = 0;
            if (a[j] != a[j - i])
            {
                ++ans[j];
            }
            sum[j] = sum[j - 1] + ans[j];
        }
        for (int j = 1; j <= ed; ++j)
        {
            if (j - i >= 1)
            {
                ++tans[nerst[sum[j + l - 1] - sum[j - 1]]][j];
            }
            if (j + i <= ed)
            {
                ++tans[nerst[sum[j + i + l - 1] - sum[j + i - 1]]][j];
            }
        }
    }
    for (int i = 1; i <= ed; ++i)
    {
        pans[0][i] = tans[0][i];
    }
    for (int i = 1; i <= q; ++i)
    {
        for (int j = 1; j <= ed; ++j)
        {
            pans[i][j] += pans[i - 1][j] + tans[i][j];
        }
    }
    for (int i = 1; i <= q; ++i)
    {
        for (int j = 1; j <= ed; ++j)
        {
            printf("%d ", pans[rk[i]][j]);
        }
        printf("\n");
    }
    return;
}
void Swap(int &aa, int &bb)
{
    int tmp = aa;
    aa = bb;
    bb = tmp;
    return;
}
