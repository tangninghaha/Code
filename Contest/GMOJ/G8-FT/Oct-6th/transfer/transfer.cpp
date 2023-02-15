#include <cstdio>


/* Constant */
const int MAXN = 1005;
const int INF = 1e8 + 5;

/* Declaration */
int main();
int Min(int, int);
int Abs(int);

/* Variable */
int f[MAXN][MAXN][2];
int lastk[MAXN][3];
int lastq[MAXN][3];
int rlastq[MAXN][3];
int lastm[MAXN][3];
int a[MAXN];
int b[MAXN];

/* Definition */
int main()
{
    freopen("transfer.in", "r", stdin);
    freopen("transfer.out", "w", stdout);
    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &b[i]);
    }
    int last = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (a[i] - a[last] > k)
            ++last;
        lastk[i][1] = last;
    }
    last = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (a[i] - a[last] > q)
            ++last;
        lastq[i][1] = last;
    }
    last = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (a[i] - a[last] > m)
            ++last;
        lastm[i][1] = last;
    }

    last = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (b[i] - b[last] > k)
            ++last;
        lastk[i][2] = last;
    }
    last = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (b[i] - b[last] > q)
            ++last;
        lastq[i][2] = last;
    }
    last = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (b[i] - b[last] > m)
            ++last;
        lastm[i][2] = last;
    }


    last = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (a[i] - b[last] > q)
            ++last;
        rlastq[i][1] = last;
    }
    last = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (b[i] - a[last] > q)
            ++last;
        rlastq[i][2] = last;
    }
    
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            f[i][j][0] = f[i][j][1] = INF;
        }
    }
    f[1][1][0] = 0;
    f[1][1][1] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == 1 && j == 1)
                continue;
            f[i][j][0] = Min(Min(f[lastm[i][1]][j][0], f[lastm[i][1]][j][1]), f[lastk[i][1]][j][0]);
            f[i][j][0] = Min(Min(f[i][lastm[j][2]][0], f[i][lastm[j][2]][1]), f[i][j][0]);
            f[i][j][0] = Min(f[i][j][0], f[lastq[i][1]][j][0]);

            f[i][j][1] = Min(Min(f[lastm[i][1]][j][0], f[lastm[i][1]][j][1]), f[i][lastk[j][2]][1]);
            f[i][j][1] = Min(Min(f[i][lastm[j][2]][0], f[i][lastm[j][2]][1]), f[i][j][0]);
            f[i][j][1] = Min(f[i][j][1], f[i][lastq[j][2]][1]);
            f[i][j][1] = Min(f[i][j][1], f[rlastq[j][2]][j][0] + 1);

            if (Abs(a[i] - b[j]) <= q) f[i][j][0] = Min(f[i][j][0], f[i][j][1] + 1);
            if (Abs(a[i] - b[j]) <= q) f[i][j][1] = Min(f[i][j][0], f[i][j][0] + 1);
        }
    }
    printf("%d", Min(f[n][n][0], f[n][n][1]));
    return 0;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
int Abs(int x)
{
    return x < 0 ? -x : x;
}
