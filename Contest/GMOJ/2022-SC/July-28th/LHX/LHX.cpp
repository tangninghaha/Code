#include <stdio.h>
#define INF 1000000005
const int MAXN = 505, MAXK = 105;
int f[MAXN][MAXK][MAXK];
char str[MAXN];

void Sovle(int n, int k);
int GetAns(int n, int k);
void InitF(int n, int k);
int Max(int a, int b);
int Min(int a, int b);
int main();

int main()
{
    freopen("LHX.in", "r", stdin);
    freopen("LHX.out", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    scanf("%s", str + 1);
    int num_j = 0, num_z = 0;
    for (int i = 1; i <= n; ++i)
    {
        num_j += (str[i] == 'j');
        num_z += (str[i] == 'z');
    }
    InitF(n, k);
    Sovle(n, k);
    int ans = GetAns(n, Min(num_j, num_z));
    printf("%d", ans);
    return 0;
}
void InitF(int n, int k)
{
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            for (int l = 0; l <= k; ++l)
            {
                f[i][j][l] = -INF;
            }
        }
    }
    f[0][0][0] = 0;
    return;
}
int GetAns(int n, int k)
{
    int ret = 0;
    for (int i = 0; i <= k; ++i)
    {
        ret = Max(ret, f[n][i][i]);
    }
    return ret;
}
void Sovle(int n, int k)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            for (int l = 0; l <= k; ++l)
            {
                f[i][j][l] = f[i - 1][j][l];
                if (i < 2 || j - (str[i - 1] != 'j') < 0 || l - (str[i] != 'z') < 0)
                    continue;
                f[i][j][l] = Max(f[i - 2][j - (str[i - 1] != 'j')][l - (str[i] != 'z')]
                                 + 1,
                                 f[i][j][l]);
            }
        }
    }
    return;
}
int Max(int a, int b)
{
    return a > b ? a : b;
}
int Min(int a, int b)
{
    return a < b ? a : b;
}
