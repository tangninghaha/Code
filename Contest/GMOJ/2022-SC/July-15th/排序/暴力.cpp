#include <stdio.h>
const int MAXN = 10001;
int a[MAXN], rk[MAXN];
void swap(int &a, int &b);
int main()
{
    int n;
    scanf("%d", &n);
    int maxn = n, minn = 1;
    int lef = 1, rgt = n;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        rk[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        int ans = 0;
        if (i % 2)
        {
            int x = rk[minn];
            for (int i = x; i > lef; --i)
            {
                rk[a[i - 1]] = i;
                swap(a[i], a[i - 1]);
                ++ans;
            }
            rk[minn] = lef;
            ++lef;
            ++minn;
        }
        else
        {
            int x = rk[maxn];
            for (int i = x; i < rgt; ++i)
            {
                rk[a[i + 1]] = i;
                swap(a[i], a[i + 1]);
                ++ans;
            }
            rk[maxn] = lef;
            --rgt;
            --maxn;
        }
        printf("%d\n", ans);
    }
    return 0;
}
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
