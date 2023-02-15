#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 205;
const int INF = 1e5 + 5;

/* Declaration */
int main();
int Min(int, int);
int Max(int, int);

/* Variable */
char a[MAXN];
int f[MAXN][MAXN];

int l[MAXN];
int r[MAXN];

/* Definition */
int main()
{
//    freopen("string.in", "r", stdin);
//    freopen("string.out", "w", stdout);
    int n;
    scanf("%s", a + 1);
    a[0] = 1;
    n = strlen(a) - 1;
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] == a[i - 1])
        {
            l[i] = l[i - 1];
        }
        else
        {
            l[i] = i;
        }
    }
    for (int i = n; i >= 1; --i)
    {
        if (a[i + 1] == a[i])
        {
            r[i] = r[i + 1];
        }
        else
        {
            r[i] = i;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            f[i][j] = INF;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        f[i][i] = 1;
    }
    int j;
    int tmp;
    for (int len = 2; len <= n; ++len)
    {
        for (int i = 1; i <= n; ++i)
        {
            j = i + len - 1;
            if (j > n)
                break;
//            if (a[j - 1] == a[j])
//                f[i][j] = Min(f[i][j], f[i][j - 1]);
//            else
//                f[i][j] = Min(f[i][j], f[i][j - 1] + 1);
//            if (a[i] == a[i + 1])
//                f[i][j] = Min(f[i][j], f[i + 1][j]);
//            else
//                f[i][j] = Min(f[i][j], f[i + 1][j] + 1);
            if (a[i] == a[j])
            {
                f[i][j] = Min(f[i][j], f[i + 1][j]);
                f[i][j] = Min(f[i][j], f[i][j - 1]);
            }
//            for (int k = i; k <= j; ++k)
//            {
//                tmp = 0;
//                if (l[k] > i)
//                    tmp += f[i][l[k] - 1];
//                if (r[k] < j)
//                    tmp += f[r[k] + 1][j];
//                if (l[k] > i && r[k] < j && a[l[k] - 1] == a[r[k] + 1])
//                    --tmp;
//                f[i][j] = Min(f[i][j], tmp + 1);
//            }
            for (int k = i; k < j; ++k)
            {
                f[i][j] = Min(f[i][j], f[i][k] + f[k + 1][j] - (a[k + 1] == a[k]));
            }
//            printf("%d ", f[i][j]);
        }
//        printf("\n");
    }
    printf("%d", f[1][n]);
    return 0;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
