#include <cstdio>

int a[5];
bool vis[10005];

int main()
{
    int n;
    int k;
    scanf("%d%d", &n, &k);
    int ans = k;
    for (int i = k; i >= 1; --i)
    {
        int tmp = i;
        for (int j = 1; j <= 4; ++j)
        {
            a[j] = tmp % 10;
            tmp /= 10;
        }
        int temp = 0;
        for (int j = 1; j <= 4; ++j)
        {
            temp = a[j] + temp * 10;
        }
        if (temp <= k && temp < i)
        {
            --ans;
        }
    }
    printf("%d", ans);
}
