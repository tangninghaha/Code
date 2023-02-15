#include <cstdio>

/* Constant */
const int MAXN = 302;
const int mod = 1e9 + 7;

/* Declaration */
int main();

/* Variable */
int f[MAXN][MAXN][MAXN];

/* Definition */
int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    int _, __, ___;
    for (int i = 1; i <= m ; ++i)
    {
        scanf("%d%d%d", &_, &__, &___);
        f[_ + 1][__ + 1][___ + 1] = -1;
    }
    f[1][1][1] = 1;
    for (int x = 1; x <= n + 1; ++x)
    {
        for (int y = 1; y <= n + 1; ++y)
        {
            for (int z = 1; z <= n + 1; ++z)
            {
                if (f[x][y][z] == -1)
                {
                    f[x][y][z] = 0;
                    continue;
                }
                f[x][y][z] += f[x - 1][y][z];
                f[x][y][z] %= mod;
                f[x][y][z] += f[x][y - 1][z];
                f[x][y][z] %= mod;
                f[x][y][z] += f[x][y][z - 1];
                f[x][y][z] %= mod;
            }
        }
    }
    printf("%d", f[n + 1][n + 1][n + 1]);
    return 0;
}
