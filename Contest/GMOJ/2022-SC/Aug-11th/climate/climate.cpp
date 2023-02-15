#include <cstdio>

/* Constant */
const int MAXN = 105;
const long long INF = 1e13;

/* Declaration */
long long Dfs(int i, int x, int ed);
int main();
void FileIO();
long long Min(long long a, long long b);
long long Abs(long long x);

/* Variable */
long long m[MAXN];
int n;
int e;
bool chs[MAXN];
int chs_num[MAXN];

/* Definition */
long long Dfs(int ii, int x, int ed)
{
    if (x > ed)
    {
        long long num = 0;
        int last_chs = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (!chs[i])
            {
                if (!last_chs)
                {
                    num += 2 * Abs(m[i] - m[chs_num[1]]);
                }
                else if(last_chs == ed)
                {
                    num += 2 * Abs(m[i] - m[ed]);
                }
                else
                {
                    num += Abs(2 * m[i] - (m[chs_num[last_chs]] + m[chs_num[last_chs + 1]]));
                }
            }
            else
            {
                ++last_chs;
            }
        }
        return num;
    }
    if (x + n - ii + 1 < ed)
    {
        return INF;
    }
    long long ret = INF;
    chs[ii] = true;
    chs_num[x] = ii;
    ret = Min(ret, Dfs(ii + 1, x + 1, ed));
    if (ret <= e)
    {
        return ret;
    }
    chs[ii] = false;
    chs_num[x] = 0;
    ret = Min(ret, Dfs(ii + 1, x, ed));
    return ret;
}
int main()
{
    FileIO();
    scanf("%d%d", &n, &e);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &m[i]);
    }
    int lbound = 0, rbound = n;
    long long ret;
    int mid;
    int ans1 = 0;
    long long ans2 = 0;
    while (lbound < rbound)
    {
        mid = (lbound + rbound) >> 1;
        printf("true");
        ret = Dfs(1, 1, mid);
        if (ret <= e)
        {
            ans1 = mid;
            ans2 = ret;
            rbound = mid;
        }
        else
        {
            lbound = mid + 1;
        }
    }
    printf("%d %lld", ans1, ans2);
    return 0;
}
void FileIO()
{
    freopen("climate.in", "r", stdin);
    freopen("climate.out", "w", stdout);
    return;
}
long long Min(long long a, long long b)
{
    return a < b ? a : b;
}
long long Abs(long long x)
{
    return x > 0 ? x : -x;
}
