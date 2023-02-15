#include <cstdio>
const int MAXN = 100 + 1;
int main();
int pri[MAXN];
bool vis[MAXN];
void init()
{
    int cnt = 0;
    for (int i = 2; i < MAXN; ++i)
    {
        if (!vis[i])
        {
            pri[cnt++] = i;
            printf("%d, ", i);
        }
        for (int j = 0; j < cnt; ++j)
        {
            if (1ll * i * pri[j] >= MAXN)
                break;
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0)
            {
                break;
            }
        }
    }
}
int main()
{
    // freopen("prime.txt", "w", stdout);
    init();
}
