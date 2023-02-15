#pragma GCC optimize(2)
#include <cstdio>

/* Constant */
const int MAXN = 1e3 + 5;
const int mod = 1e9 + 7;

/* Declaration */
int main();
inline int Dfs(int, int);
int Read();

/* Variable */
int a[MAXN][MAXN];
int last_appear[MAXN][2];
bool input_appear[MAXN];
int n, m, k;

/* Definition */
int main()
{
    freopen("in.txt", "r", stdin);
//    scanf("%d%d%d", &n, &m, &k);
    n = Read();
    m = Read();
    k = Read();
    for (register int i = 1; i <= n; ++i)
    {
        for (register int j = 1; j <= m; ++j)
        {
//            scanf("%d", &a[i][j]);
            a[i][j] = Read();
            if (a[i][j])
            {
                input_appear[a[i][j]] = true;
            }
        }
    }
    if (n + m - 1 > k)
    {
        printf("0");
        return 0;
    }
    for (register int i = 1; i <= n; ++i)
    {
        for (register int j = 1; j <= m; ++j)
        {
            if (!a[i][j])
                continue;
            for (register int x = 1; x <= i; ++x)
            {
                for (register int y = 1; y <= j; ++y)
                {
                    if (x == i && y == j)
                        continue;
                    if (a[x][y] == a[i][j])
                    {
                        printf("0");
                        return 0;
                    }
                }
            }
        }
    }
    printf("%d", Dfs(1, 1));
    return 0;
}
inline int Dfs(int _x, int _y)
{
    if (_x == n + 1)
    {
        return 1;
    }
    int ret;
    if (a[_x][_y])
    {
        if (last_appear[a[_x][_y]][0] <= _x && last_appear[a[_x][_y]][1] <= _y && last_appear[a[_x][_y]][0])
            return 0;
        int tem1 = last_appear[a[_x][_y]][0];
        int tem2 = last_appear[a[_x][_y]][1];
        last_appear[a[_x][_y]][0] = _x;
        last_appear[a[_x][_y]][1] = _y;
        if (_y == m)
            ret = Dfs(_x + 1, 1);
        else
            ret = Dfs(_x, _y + 1);
        last_appear[a[_x][_y]][0] = tem1;
        last_appear[a[_x][_y]][1] = tem2;
        return ret;
    }
    int hf = 0;
    bool pd = false;
    long long sum = 0, cnt = 0;
    for (register int i = 1; i <= k; ++i)
    {
        if (last_appear[i][0] <= _x && last_appear[i][1] <= _y && last_appear[i][0])
        {
            continue;
        }
        if (pd && !last_appear[i][0] && !input_appear[i])
            ++hf;
        else if (last_appear[i][0] || input_appear[i])
        {
            int tem1 = last_appear[i][0];
            int tem2 = last_appear[i][1];
            last_appear[i][0] = _x;
            last_appear[i][1] = _y;
            a[_x][_y] = i;
            if (_y == m)
            {
                cnt += Dfs(_x + 1, 1);
                cnt %= mod;
            }
            else
            {
                cnt += Dfs(_x, _y + 1);
                cnt %= mod;
            }
            last_appear[i][0] = tem1;
            last_appear[i][1] = tem2;
            a[_x][_y] = 0;
        }
        else
        {
            hf = 1;
            int tem1 = last_appear[i][0];
            int tem2 = last_appear[i][1];
            last_appear[i][0] = _x;
            last_appear[i][1] = _y;
            a[_x][_y] = i;
            if (_y == m)
            {
                sum = Dfs(_x + 1, 1);
                sum %= mod;
            }
            else
            {
                sum = Dfs(_x, _y + 1);
                sum %= mod;
            }
            last_appear[i][0] = tem1;
            last_appear[i][1] = tem2;
            a[_x][_y] = 0;
            pd = true;
        }
    }
    return ((sum * hf) % mod + cnt) % mod;
}
int Read()
{
    int ret = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
        tmp = getchar();
    while (tmp >= '0' && tmp <= '9')
    {
        ret = (ret << 1) + (ret << 3) + tmp - 48;
        tmp = getchar();
    }
    return ret;
}
