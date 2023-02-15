#include <cstdio>

/* Constant */
const int n = 1e3 + 5;
const long long mod = 1e9 + 7;

/* Declaration */
int DP1(int w, int i, int j);
int main();
void FileIO();
int Max(int a_, int b_);

/* Variable */
int num[MAXN * MAXN];
int f[MAXN * MAXN][2][3];
bool vis[MAXN * MAXN][2][3];
int n;
int len;

/* Definition */
int DP1(int w, int i, int j)
{
    if (w > n)
    {
        return 0;
    }
    if (vis[w][i][j])
    {
        return f[w][i][j] % mod;
    }
    long long tmp = 0;
    if (i == 0)
    {
        if (j == 0)
        {
            tmp += ((DP1(w - 1, 0, 0) * 9) % mod) * Max(num[len - w + 1] - 1, 0);
            tmp %= mod;
            tmp += ((DP1(w - 1, 0, 1) * 9) % mod) * Max(num[len - w + 1] - 1, 0);
            tmp %= mod;
            tmp += ((DP1(w - 1, 1, 0) * Max(num[w] - 1, 0)) % mod) * Max(num[len - w + 1] - 1, 0);
        }
        tmp += DP1(w - 1, 0, 1);
        tmp %= mod;
        tmp += DP1(w - 1, 0, 2);
        tmp %= mod;
        f[w][i][j] = tmp;
    }
}
