#include <cstdio>

const int mod = 123456788;
const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0}, dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

int main();
void Dfs(int x, int y, int k);

long long ans = 0;
bool pd[17][17];
bool chos[17][17];
int n, m;

void Dfs(int x, int y, int k)
{
    if (x == n + 1)
    {
        if (k == m)
        {
            ++ans;
//            for (int i = 1; i <= n; ++i)
//            {
//                for (int j = 1; j <= n; ++j)
//                {
//                    printf("%d ", chos[i][j]);
//                }
//                printf("\n");
//            }
//            printf("\n");
        }
        ans %= mod;
        return;
    }
    bool pdd = false;
    for (int t = 0; t < 8; ++t)
    {
        if (chos[x + dx[t]][y + dy[t]])
        {
            pdd = true;
            break;
        }
    }
    if (!pdd && !pd[x][y])
    {
        chos[x][y] = true;
        for (int t = 0; t < 8; ++t)
        {
            pd[x + dx[t]][y + dy[t]] = true;
        }
        if (y != n)
            Dfs(x, y + 1, k + 1);
        else
            Dfs(x + 1, 1, k + 1);
    }
    chos[x][y] = false;
    for (int t = 0; t < 8; ++t)
    {
        pd[x + dx[t]][y + dy[t]] = false;
    }
    if (y != n)
        Dfs(x, y + 1, k);
    else
        Dfs(x + 1, 1, k);
    return;
}

int main()
{
    scanf("%d%d", &n, &m);
    Dfs(1, 1, 0);
    printf("%lld", ans);
    return 0;
}
