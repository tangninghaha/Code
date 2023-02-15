#include <cstdio>

/* Constant */
const int MAXN = 155;
const int MAXM = 55;

/* Variable */
long long a[MAXN];
long long s[MAXN];
long long twom[51];

long long tmp[MAXN];
bool pds[MAXN];

/* Declaration */
int main();
void Init(int);
int Min(int, int);

/* Definition */
int main()
{
    freopen("light.in", "r", stdin);
    freopen("light.out", "w", stdout);
    twom[0] = 1;
    for (int i = 1; i <= 50; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }

    int t;
    scanf("%d", &t);
    int n = 0, m;
    char cha;
    for (int fot = 1; fot <= t; ++fot)
    {
        Init(n);
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                while (cha != '0' && cha != '1')
                    cha = getchar();
                a[i] += twom[j - 1] * (cha - 48);
                cha = getchar();
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                while (cha != '0' && cha != '1')
                    cha = getchar();
                s[i] += twom[j - 1] * (cha - 48);
                cha = getchar();
            }
        }
        long long ns;
        long long tmps;
        int ans = m + 1;
        int sum = 0;
        bool get_ans;
        bool pd;
        for (int i = 1; i <= n; ++i)
        {
            get_ans = true;
            ns = a[1] ^ s[i];
            tmps = ns;
            sum = 0;
            for (int j = 1; j <= m; ++j)
            {
                if (tmps & 1)
                {
                    ++sum;
                }
                tmps >>= 1;
            }
            if (sum > ans)
                continue;
            for (int j = 1; j <= n; ++j)
            {
                tmp[j] = a[j] ^ ns;
            }
            for (int j = 1; j <= n; ++j)
            {
                pds[j] = false;
            }
            for (int j = 2; j <= n; ++j)
            {
                pd = false;
                for (int k = 1; k <= n; ++k)
                {
                    if (k == i)
                        continue;
                    if (pds[k])
                        continue;
                    if (tmp[j] == s[k])
                    {
                        pd = pds[k] = true;
                        break;
                    }
                }
                if (!pd)
                {
                    get_ans = false;
                    break;
                }
            }
            if (!get_ans)
                continue;
            ans = Min(ans, sum);
        }
        if (ans == m + 1)
            printf("Impossible\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}
void Init(int _n)
{
    for (int i = 1; i <= _n; ++i)
    {
        a[i] = s[i] = 0;
    }
    return;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
