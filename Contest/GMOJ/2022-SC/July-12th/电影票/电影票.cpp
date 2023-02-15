#include <stdio.h>
const int MAXN = 5001, MAXM = 5001, N = 5000;
unsigned long long f[MAXN][MAXM];
unsigned long long s_lie[MAXN][MAXM];
unsigned long long s_hang[MAXN][MAXM];
void Init();
int main()
{
    Init();
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%llu", f[n][m]);
}
void Init()
{
    f[1][1] = 1;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            f[i][j] += s_lie[j][i - 1] - s_lie[j][j - 1];
            f[i][j] += s_hang[i][j - 1];
            s_lie[j][i] = s_lie[j][i - 1] + f[i][j];
            s_hang[i][j] = s_hang[i][j - 1] + f[i][j];
        }
    }
    return;
}
