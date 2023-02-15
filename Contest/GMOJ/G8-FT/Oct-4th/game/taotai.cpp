#include <cstdio>
#include <cmath>
#define FILEIO 

/* Constant */
const int MAXN = 11;
const int MAXNN = 1037;
const double xxx = 1e-10;

/* Declaration */
int main();

/* Variable */
double f[MAXN][MAXNN];
int twom[11];
double gailv[MAXNN][MAXNN];
bool vis[MAXNN];
int log_2[MAXNN];

/* Definition */

int main()
{
#ifdef FILEIO
    freopen("in.txt", "r", stdin);
#endif
    twom[0] = 1;
    for (int i = 1; i <= 10; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }
    for (int i = 1; i < MAXNN; ++i)
    {
        log_2[i] = log_2[i / 2] + 1;
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= twom[n]; ++i)
    {
        for (int j = 1; j <= twom[n]; ++j)
        {
            scanf("%lf", &gailv[i][j]);
            gailv[i][j] /= 100.0;
        }
    }
    for (int i = 1; i <= twom[n]; ++i)
    {
        f[0][i] = 1;
        f[1][i] = gailv[i][i & 1 ? i + 1 : i - 1]; 
    }
    int now_block;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j <= twom[n]; ++j)
        {
            now_block = ceil(1.0 * j / twom[i - 1]);
            if (!(now_block & 1))
                for (int k = (now_block - 2) * twom[i - 1] + 1; k <= (now_block - 1) * twom[i - 1]; ++k)
                {
                    if (k < 1)
                        continue;
                    // if (log_2[abs((k + 1) / 2 - (j + 1) / 2)] + 1 == i)
                    f[i][j] += f[i - 1][j] * gailv[j][k] * f[i - 1][k];
                }
            else
                for (int k = now_block * twom[i - 1] + 1; k <= (now_block + 1) * twom[i - 1]; ++k)
                {
                    if (k > twom[n])
                        break;
                    // if (log_2[abs((k + 1) / 2 - (j + 1) / 2)] + 1 == i)
                    f[i][j] += f[i - 1][j] * gailv[j][k] * f[i - 1][k];
                }
        }
    }
    double ans = 0;
    int ans_bh = -1;
    double sum = 0;
    for (int i = 1; i <= twom[n]; ++i)
    {
        if (f[n][i] > ans && (f[n][i] - ans > xxx))
        {
            ans = f[n][i];
            ans_bh = i;
        }
        sum += f[n][i];
    }
    printf("%d", ans_bh);
    // printf("\n%lf", sum);
    return 0;
}
