#include <stdio.h>

const int MAXN = 1048576;
int two_pow[21];
int a[21][21];
int friends_num[21];
int f[MAXN];
int w[MAXN];
int vis[MAXN];
int num[MAXN];
int nxt[MAXN];

int main()
{
    two_pow[0] = 1;
    for (int i = 1; i <= 20; ++i)
    {
        two_pow[i] = two_pow[i - 1] << 1;
    }
    int n, h;
    scanf("%d%d", &n, &h);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%1d", &a[i][j]);
            if (a[i][j])
                ++friends_num[i];
        }
    }
    for (int i = 0; i < two_pow[n]; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if ((i >> (j - 1)) & 1)
            {
                f[i] += friends_num[i] * 2;
            }
            else
            {
                f[i] += friends_num[i];
            }
        }
    }
    long long ans = friends_num[1];
    int t, s, len, st, ed;
    for (int i = 2; i <= h; ++i)
    {
        s = 0;
        for (int j = 1; j <= n; ++j)
        {
            s += (w[j] % 2) * two_pow[j - 1];
            st = vis[i];
            ed = i - 1;
        }
        ans += f[s];
        num[i] += f[s];
        if (vis[s])
        {
            t = num[i] - num[vis[i]];
            len = i - vis[i];
            ans += ((h - i) / len) * t + num[(h - i) % st] - num[st];
            break;
        }
        vis[s] = i;
    }
    printf("%lld", ans);
    return 0;
}
