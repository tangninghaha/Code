#include <cstdio>

/* Constant */
const int MAXN = 155;
const int MAXM = 55;

/* Declaration */
int main();
void Qsort(int, int, long long*);
template<typename T> void Swap(T&, T&);
int Dfs(int, int);
void Clear();

/* Variable */
bool a[MAXN][MAXM];
bool s[MAXN][MAXM];
int anum[MAXM][2];
int snum[MAXM][2];
long long aa[MAXN];
long long ss[MAXN];

int diffline[MAXM];

long long twom[51];

int n = 0, m = 0;
bool get_ans;

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
    bool pd = false;
    for (int fot = 1; fot <= t; ++fot)
    {
        get_ans = false;
        int ans = 0;
        pd = false;
        Clear();
        scanf("%d%d", &n, &m);
        char tmp = getchar();
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                while (tmp != '0' && tmp != '1')
                {
                    tmp = getchar();
                }
                a[i][j] = tmp - '0';
                ++anum[j][a[i][j]];
                tmp = getchar();
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                while (tmp != '0' && tmp != '1')
                {
                    tmp = getchar();
                }
                s[i][j] = tmp - '0';
                ++snum[j][s[i][j]];
                tmp = getchar();
            }
        }
        for (int i = 1; i <= m; ++i)
        {
            if (anum[i][0] != snum[i][0] && anum[i][0] != snum[i][1])
            {
                pd = true;
                printf("Impossible\n");
                break;
            }
        }
        if (pd)
            continue;
        int diff_tot = 0;
        for (int i = 1; i <= m; ++i)
        {
            if (anum[i][0] != anum[i][1])
            {
                if (anum[i][0] != snum[i][0])
                {
                    if (anum[i][0] == snum[i][1])
                    {
                        ++ans;
                        for (int j = 1; j <= n; ++j)
                        {
                            a[j][i] = !a[j][i];
                        }
                    }
                    else
                    {
                        pd = true;
                        printf("Impossible\n");
                        break;
                    }
                }
            }
            else
            {
                ++diff_tot;
                diffline[diff_tot] = i;
            }
        }
        if (pd)
            continue;
        int k = 0;
        for (int i = 1; i <= diff_tot; ++i)
        {
            for (int j = m; j >= 1; --j)
            {
                if (anum[j][0] != anum[j][1])
                {
                    k = j;
                    break;
                }
            }
            if (k < diffline[i])
                break;
            for (int j = 1; j <= n; ++j)
            {
                Swap(a[j][k], a[j][diffline[i]]);
                Swap(s[j][k], s[j][diffline[i]]);
            }
            Swap(anum[diffline[i]][0], anum[k][0]);
            Swap(anum[diffline[i]][1], anum[k][1]);
            Swap(snum[diffline[i]][1], snum[k][1]);
            Swap(snum[diffline[i]][1], snum[k][1]);
            diffline[i] = k;
        }

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                aa[i] += twom[j - 1] * a[i][j];
                ss[i] += twom[j - 1] * s[i][j];
            }
        }
        int begin = m + 1;
        for (int i = 1; i <= m; ++i)
        {
            if (anum[i][0] == anum[i][1])
            {
                begin = i;
                break;
            }
        }
        Qsort(1, n, aa);
        Qsort(1, n, ss);
        int ret = Dfs(begin, 0);
        if (ret == -1)
        {
            printf("Impossible\n");
            continue;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (aa[i] != ss[i])
            {
                pd = true;
                printf("Impossible\n");
                break;
            }
        }
        if (pd)
            continue;

        ans += ret;
        printf("%d\n", ans);
    }
}
void Clear()
{
    for (int i = 1; i <= m; ++i)
    {
        anum[i][0] = 0;
        anum[i][1] = 0;
        snum[i][0] = 0;
        snum[i][1] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        ss[i] = aa[i] = 0;
    }
}
void Qsort(int l, int r, long long* _a)
{
    int i = l, j = r;
    long long mid = _a[(l + r) >> 1];
    while (i <= j)
    {
        while (_a[i] < mid)
            ++i;
        while (mid < _a[j])
            --j;
        if (i <= j)
        {
            Swap(_a[i], _a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
    {
        Qsort(i, r, _a);
    }
    if (l < j)
    {
        Qsort(l, j, _a);
    }
    return;
}
template<typename T> void Swap(T& _a, T& _b)
{
    T t = _a;
    _a = _b;
    _b = t;
    return;
}
int Dfs(int _x, int cost)
{
    if (_x > m)
    {
        get_ans = true;
        for (int i = 1; i <= n; ++i)
        {
            if (ss[i] != aa[i])
            {
                get_ans = false;
                cost = -1;
                break;
            }
        }
        return cost;
    }
    int ret = -1;
    ret = Dfs(_x + 1, cost);
    if (get_ans)
    {
        return ret;
    }
    for (int i = 1; i <= n; ++i)
    {
        aa[i] ^= twom[_x - 1];
    }
    Qsort(1, n, aa);
    ret = Dfs(_x + 1, cost + 1);
    return ret;
}
