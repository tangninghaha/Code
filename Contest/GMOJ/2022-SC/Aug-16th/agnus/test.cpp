#include <cstdio>
#include <algorithm>

using std::pair;

const int MAXN = 1e7 + 5;

pair<int, int> a[MAXN];

int main()
{
    freopen("out2.txt", "r", stdin);
    freopen("res2.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d %d\n", a[i].first, a[i].second);
    }
    return 0;
}
