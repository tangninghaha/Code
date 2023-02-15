#include <stdio.h>

const long long INF = 1e15 + 5;
long long f[55][125][125][4];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main();
long long Min(long long a, long long b);
long long ans_map[125][125];
int n, p_tot[13];
int q[13];
int p[13][55];
int c[13][55];
int stx[13], sty[13];

void FileIO()
{
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    scanf("%d", &n);
    char cha;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d%d%d", &stx[i], &sty[i], &q[i], &p_tot[i]);
        stx[i] += 60;
        sty[i] += 60;
        q[i] /= 90;
        c[i][0] = q[i];
        for (int j = 1; j <= p_tot[i]; ++j)
        {
            cha = getchar();
            while (cha != 'T' && cha != 'S')
            {
                cha = getchar();
            }
            if (cha == 'T')
            {
                p[i][j] = 1;
                scanf("%d", &c[i][j]);
                c[i][j] /= 90;
            }
            else
            {
                p[i][j] = 2;
                c[i][j] = c[i][j - 1];
            }
        }
    }
//    for (int i = 0; i <= 121; ++i)
//    {
//        for (int j = 0; j <= 121; ++j)
//        {
//            ans_map[i][j] = INF;
//        }
//    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= p_tot[i]; ++j)
        {
            for (int x = 0; x <= 122; ++x)
            {
                for (int y = 0; y <= 122; ++y)
                {
                    for (int k = 0; k <= 3; ++k)
                    {
                        f[j][x][y][k] = INF;
                    }
                }
            }
        }
        f[0][stx[i]][sty[i]][q[i]] = 0;
        for (int j = 1; j <= p_tot[i]; ++j)
        {
            for (int x = 1; x <= 121; ++x)
            {
                for (int y = 1; y <= 121; ++y)
                {
                    for (int k = 0; k <= 3; ++k)
                    {
                        f[j][x][y][k] = Min(f[j][x][y][k],
                                            f[j - 1][x][y][k] + 1);
                        if (p[i][j] == 1)
                        {
                            f[j][x][y][k] = Min(f[j][x][y][k],
                                                f[j - 1][x][y][(k - c[i][j] + 4) % 4]);
                        }
                        if(p[i][j] == 2)
                        {
                            f[j][x][y][k] = Min(f[j][x][y][k],
                                            f[j - 1][x - dx[k]][y - dy[k]][k]);
                        }
                    }
                }
            }
        }
        for (int x = 1; x <= 121; ++x)
        {
            for (int y = 1; y <= 121; ++y)
            {
                ans_map[x][y] += Min(f[p_tot[i]][x][y][0], 
                                 Min(f[p_tot[i]][x][y][1], 
                                 Min(f[p_tot[i]][x][y][2],
                                     f[p_tot[i]][x][y][3])));
            }
        }
    }
    long long ans = -1, ans_x, ans_y;
    for (int i = 1; i <= 121; ++i)
    {
        for (int j = 1; j <= 121; ++j)
        {
            if (ans_map[i][j] < INF && (ans_map[i][j] < ans || ans == -1))
            {
                ans = ans_map[i][j];
                ans_x = i;
                ans_y = j;
            }
        }
    }
    if (ans == -1)
    {
        printf("-1");
    }
    else
    {
        printf("%lld\n%lld %lld", ans, ans_x - 60, ans_y - 60);
    }
    return 0;
}
long long Min(long long a, long long b)
{
    return a < b ? a : b;
}
