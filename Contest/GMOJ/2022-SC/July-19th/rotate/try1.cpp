#include <stdio.h>
const int MAXN = 1e5 + 5;
int a[MAXN];
int t[MAXN];
void swap(int &a, int &b);
int main()
{
    freopen("rotate.in", "r", stdin);
    freopen("rotate.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i; j <= n; ++j)
        {
            int cnt = 0;
            for (int k = 1; k <= n; ++k)
            {
                t[k] = a[k];
            }
            for (int k = 1; k <= (j - i + 1) / 2; ++k)
            {
                swap(t[i + k - 1], t[j - k + 1]);
            }
            for (int k = 1; k <= n; ++k)
            {
                if (t[k] == k)
                {
                    ++cnt;
                }
            }
            if (cnt > ans)
                ans = cnt;
        }
    }
    printf("%d", ans);
    return 0;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
