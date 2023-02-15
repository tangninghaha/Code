#include <cstdio>

int a[4005][4005];
int f[4005][4005];

int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int x, y, c;
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d%d%d", &x, &y, &c);
        a[x][y] = c;
    }
    for (int i = n; i >= 1; --i)
    {
        for (int j = m; j >= 1; -- j)
        {
            f[i][j] = Max(f[i + 1][j], f[i][j + 1]) + a[i][j];
        }
    }
//    for (int i = 1; i <= n; ++i)
//    {
//        for (int j = 1; j <= m; ++j)
//        {
//            if (a[i][j])
//                printf("%d ", f[i][j]);
//        }
//    }
    printf("%d", f[1][1]);
    return 0;
}
