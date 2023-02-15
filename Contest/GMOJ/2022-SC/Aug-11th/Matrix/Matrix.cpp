#include <cstdio>

/* Constant */
const int MAXN = 505;

/* Declaration */
int main();
void Qsort(int l, int r);
void Swap(int& a, int &b);
void FileIO();

/* Variable */
int T[MAXN][MAXN];
int tmp[MAXN * MAXN];

/* Definition */
int main()
{
    FileIO();
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &T[i][j]);
        }
    }
    int x1, x2, y1, y2, k;
    int tot;
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
        tot = 0;
        for (int j = x1; j <= x2; ++j)
        {
            for (int l = y1; l <= y2; ++l)
            {
                tmp[++tot] = T[j][l];
            }
        }
        Qsort(1, tot);
        printf("%d\n", tmp[k]);
    }
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int mid = tmp[(l + r) >> 1];
    while (i <= j)
    {
        while (tmp[i] < mid)
            ++i;
        while (tmp[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(tmp[i], tmp[j]);
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
void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
    return;
}
void FileIO()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    return;
}
