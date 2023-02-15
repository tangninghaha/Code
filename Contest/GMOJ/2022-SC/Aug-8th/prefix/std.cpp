#include <stdio.h>
#include <cstring>

const int MAXN = 2005, MAXLEN = 205;
const long long mod = 1e9 + 7;
char str[MAXN][MAXLEN];
long long f[MAXN][MAXN];
int len[MAXN];
char tmp[MAXLEN];
int LCP[MAXN][MAXN];

bool Cmp(char *a, char *b, int lenn);
int Cmp_str(char *a, char *b, int len1, int len2);
void FileIO();
int main();
int Max(int a, int b);
int Min(int a, int b);
void Qsort(int l, int r);
void Swap(int &a, int &b);
void Swap_str(int a, int b);

bool Cmp(char *a, char *b, int lenn)
{
    for (int i = 0; i < lenn; ++i)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}
int Cmp_str(int a, int b)
{
    int l = Max(len[a], len[b]);
    for (int i = 0; i < l; ++i)
    {
        if (str[a][i] > str[b][i])
            return 1;
        if (str[a][i] < str[b][i])
            return -1;
    }
    return 0;
}
void FileIO()
{
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
    return;
}
void Qsort(int l, int r)
{
    int i = l, j = r, mid = (l + r) >> 1;
    while (i <= j)
    {
        while (Cmp_str(i, mid) < 0)
            ++i;
        while (Cmp_str(j, mid) > 0)
           --j;
        if (i <= j)
        {
            Swap_str(i, j);
            if (i == mid)
                mid = j;
            else if (j == mid)
                mid = i;
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
}
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str[i]);
        len[i] = strlen(str[i]);
    }
    Qsort(1, n);
    for (int i = 1; i <= n; ++i)
    {
        // printf("%s\n", str[i]);
        LCP[i][i] = len[i];
    }
    for (int i = 1; i < n; ++i)
    {
        // printf("%d\n", Cmp_str(i, i + 1)); 
    }
    bool pd;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            pd = false;
            if (!LCP[i][j - 1])
                break;
            int ed = LCP[i][j - 1];
            for (int k = 0; k < ed; ++k)
            {
                if (str[i][k] != str[j][k])
                {
                    pd = true;
                    LCP[i][j] = k;
                    break;
                }
            }
            if (!pd)
            {
                LCP[i][j] = LCP[i][j - 1];
            }
            LCP[j][i] = LCP[i][j];
//            printf("%d ", LCP[i][j]);
        }
//        printf("\n");
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        // printf("%d: ", i);
        for (int j = 1; j <= m; ++j)
        {
            int x = i;
            while (LCP[x][i])
            {
                if (LCP[x][i] <= LCP[i][i + 1])
                {
                    break;
                }
                f[i][j] += (long long)(f[x - 1][j - 1] % mod)
                           * (Min(LCP[x][i] - LCP[x - 1][i],
                                  LCP[x][i] - LCP[i][i + 1]));
                f[i][j] %= mod;
                --x;
            }
            // printf("%lld ", f[i][j]);
        }
        // printf("\n");
    }
    printf("%lld", f[n][m]);
    return 0;
}
int Max(int a, int b)
{
    return a > b ? a : b;
}
int Min(int a, int b)
{
    return a < b ? a : b;
}
void Swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
void Swap_str(int a, int b)
{
    int l1 = len[a], l2 = len[b];
    for (int i = 0; i < l1; ++i)
    {
        tmp[i] = str[a][i];
    }
    for (int i = 0; i < l2; ++i)
    {
        str[a][i] = str[b][i];
    }
    for (int i = l2; i < l1; ++i)
    {
        str[a][i] = 0;
    }
    for (int i = 0; i < l1; ++i)
    {
        str[b][i] = tmp[i];
    }
    for (int i = l1; i < l2; ++i)
    {
        str[b][i] = 0;
    }
    Swap(len[a], len[b]);
    return;
}
