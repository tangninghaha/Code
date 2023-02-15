#include <cstdio>

/* Constant */
const int MAXN = 1e6 + 5;
const int MAXM = 5e5 + 5;
const int MAXQ = 2e5 + 5;

/* Declaration */
int main();

/* Variable */
char a[MAXN];
int col[MAXM], row[MAXM];
int aa, bb;
int rk[2][MAXM];

/* Definition */
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    char tmp;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            while (tmp < 'a' || tmp > 'z')
                tmp = getchar();
            a[(i - 1) * m + j] = tmp;
            tmp = getchar();
        }
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= n; ++i)
        row[i] = i;
    for (int i = 1; i <= m; ++i)
        col[i] = i;
    for (int t = 1; t <= q; ++t)
    {
        scanf("%d%d", &aa, &bb);
        for (int i = 1; i <= n; ++i)
            if (row[i] <= aa)
                row[i] = aa + 1 - row[i];
            else
            row[i] = aa + 1 + n - row[i];
        for (int i = 1; i <= m; ++i)
            if (col[i] <= bb)
                col[i] = bb + 1 - col[i];
            else
                col[i] = m + bb + 1 - col[i];
    }
    for (int i = 1; i <= n; ++i)
        rk[0][row[i]] = i;
    for (int i = 1; i <= m; ++i)
        rk[1][col[i]] = i;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            printf("%c", a[(rk[0][i] - 1) * m + rk[1][j]]);
        }
        printf("\n");
    }

}
