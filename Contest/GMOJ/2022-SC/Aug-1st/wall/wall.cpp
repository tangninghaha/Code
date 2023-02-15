#include <stdio.h>

int main()
{
    freopen("wall.in", "r", stdin);
    freopen("wall.out", "w", stdout);
    int n;
    scanf("%d", &n);
    if (n == 1)
    {
        printf("6");
        return 0;
    }
    int s = 1;
    int l = 1;
    int ans;
    while (s < n)
    {
        ++l;
        s = 3 * (l - 1) * (l - 1) - 3 * (l - 1) + 1;
    }
    --l;
    s = 3 * (l - 1) * (l - 1) - 3 * (l - 1) + 1;
    ans = 6 * (l - 1);
    for (int i = 1; i <= 6; ++i)
    {
        if (s >= n)
        {
            break;
        }
        ++ans;
        s += l - 1;
        if (i == 1)
        {
            --s;
        }
        if (i == 6)
        {
            ++s;
        }
    }
    printf("%d", ans);
    return 0;
}
