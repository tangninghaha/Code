#include <stdio.h>
const int MAXN = 5001, MAXM = 5001, N = 1000;
long long f[MAXN][MAXM];
long long s_lie[MAXN][MAXM];
long long s_hang[MAXN][MAXM];
void Init();
int main()
{
    Init();
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%lld", f[n][m]);
}
void Init()
{
    f[1][1] = 1;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
//            for (int k = j; k < i; ++k)
//            {
                f[i][j] += f[i - 1][j];
//            }
//            f[i][j] += s_lie[j][i - 1] - s_lie[j][j - 1];
//            f[i][j] += s_hang[i][j - 1];
//            for (int k = 1; k < j; ++k)
//            {
                f[i][j] += f[i][j - 1];
//            }
//            s_lie[j][i] = s_lie[j][i - 1] + f[i][j];
//            s_hang[i][j] = s_hang[i][j - 1] + f[i][j];
            printf("%lld ", f[i][j]);
        }
        printf("\n");
    }
    return;
}
