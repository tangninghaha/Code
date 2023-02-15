#include <stdio.h>
const int MAXN = 1e4 + 1;
int f[MAXN];
int a[MAXN];
int max(int a, int b);
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    int k;
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        f[i] = 1;
        k = 0;
        for (int j = 1; j < i; ++j)
        {
            if (a[j] >= a[i] && f[j] + 1 >= f[i])
            {
                k = j;
                f[i] = max(f[i], f[j] + 1);
            }
        }
        ans = max(f[i], ans);
//        printf("%d(%d): F:%d\n  ", i, a[i], f[i]);
//        for (int j = 1; j < i; ++j)
//        {
//            if (f[j] + 1 == f[i])
//            {
////                printf("%d ", j);
//            }
//        }
//        printf("\n");
    }
    printf("%d", ans);
    return 0;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
