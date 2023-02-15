#include <bits/stdc++.h>

/* Constant */
const int MAXN = 5005;

/* Declaration & Definition */
std::string a[MAXN], b[MAXN];
int main()
{
    freopen("test.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        std::cin >> b[i];
    }
    std::sort(a + 1, a + n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] != a[i - 1])
        {
            ++cnt;
        }
        printf("%d ", cnt);
    }
    return 0;
}
