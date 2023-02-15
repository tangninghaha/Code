#include <cstdio>
#include <cstring>

/* Declaration */
void Dfs(int, int, int, int, bool);
int main();
int Read(int*);
int Read();
void Swap(int&, int&);

/* Variable */
int ans, ans_sum;
int lenm, lenn;
int m[11];
int n[11];
int num[11];

/* Definition */
int main()
{
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    int t;
    scanf("%d", &t);
    int k;
    for (int tt = 1; tt <= t; ++tt)
    {
        memset(num, 0, sizeof(num));
        memset(m, 0, sizeof(m));
        memset(n, 0, sizeof(n));
        ans = 1e7 + 5;
        ans_sum = 0;
        lenm = Read(m);
        lenn = Read(n);
        k = Read();
        Dfs(lenn, k, 4, 1, 0);
        printf("%d %d\n", ans, ans_sum);
    }
    return 0;
}
void Dfs(int x, int k, int status, int sum, bool zero)
{
    if (!x)
    {
        if (k)
            return;
        if (sum > ans_sum)
        {
            ans_sum = sum;
            ans = 0;
            for (int i = lenn; i >= 1; --i)
            {
                ans = (ans << 1) + (ans << 3) + num[i];
            }
        }
        else if (sum == ans_sum)
        {
            int tmp_ans = 0;
            for (int i = lenn; i >= 1; --i)
            {
                tmp_ans = (tmp_ans << 1) + (tmp_ans << 3) + num[i];
            }
            if (tmp_ans < ans)
            {
                ans = tmp_ans;
            }
        }
        return;
    }
    if (status == 4)
    {
        if (n[x] == m[x])
        {
            num[x] = n[x];
            if (k < num[x])
                return;
            if (zero)
                Dfs(x - 1, k - num[x], 4, sum * num[x], zero);
            else
                Dfs(x - 1, k - num[x], 4, sum * (num[x] ? num[x] : 1), num[x]);
        }
        else
        {
            num[x] = m[x];
            if (k < num[x])
                return;
            if (zero)
                Dfs(x - 1, k - num[x], 2, sum * num[x], zero);
            else
                Dfs(x - 1, k - num[x], 2, sum * (num[x] ? num[x] : 1), num[x]);
            for (int i = m[x] + 1; i < n[x]; ++i)
            {
                num[x] = i;
                if (k < num[x])
                    return;
                if (zero)
                    Dfs(x - 1, k - num[x], 1, sum * num[x], zero);
                else
                    Dfs(x - 1, k - num[x], 1, sum * (num[x] ? num[x] : 1), num[x]);
            }
            num[x] = n[x];
            if (k < num[x])
                return;
            if (zero)
                Dfs(x - 1, k - num[x], 3, sum * num[x], zero);
            else
                Dfs(x - 1, k - num[x], 3, sum * (num[x] ? num[x] : 1), num[x]);
        }
    }
    else if (status == 3)
    {
        for (int i = 0; i < n[x]; ++i)
        {
            num[x] = i;
            if (k < num[x])
                return;
            if (zero)
                Dfs(x - 1, k - num[x], 1, sum * num[x], zero);
            else
                Dfs(x - 1, k - num[x], 1, sum * (num[x] ? num[x] : 1), num[x]);
        }
        num[x] = n[x];
        if (k < num[x])
            return;
        if (zero)
            Dfs(x - 1, k - num[x], 3, sum * num[x], zero);
        else
            Dfs(x - 1, k - num[x], 3, sum * (num[x] ? num[x] : 1), num[x]);
    }
    else if (status == 2)
    {
        num[x] = m[x];
        if (k < num[x])
            return;
        if (zero)
            Dfs(x - 1, k - num[x], 2, sum * num[x], zero);
        else
            Dfs(x - 1, k - num[x], 2, sum * (num[x] ? num[x] : 1), num[x]);
        for (int i = m[x] + 1; i <= 9; ++i)
        {
            num[x] = i;
            if (k < num[x])
                return;
            if (zero)
                Dfs(x - 1, k - num[x], 1, sum * num[x], zero);
            else
                Dfs(x - 1, k - num[x], 1, sum * (num[x] ? num[x] : 1), num[x]);
        }
    }
    else
    {
        for (int i = 0; i <= 9; ++i)
        {
            num[x] = i;
            if (k < num[x])
                return;
            if (zero)
                Dfs(x - 1, k - num[x], 1, sum * num[x], zero);
            else
                Dfs(x - 1, k - num[x], 1, sum * (num[x] ? num[x] : 1), num[x]);
        }
    }
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
int Read(int *_a)
{
    int len = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
        tmp = getchar();
    while (tmp >= '0' && tmp <= '9')
    {
        ++len;
        _a[len] = tmp - 48;
        tmp = getchar();
    }
    for (int i = 1; i <= len / 2; ++i)
    {
        Swap(_a[i], _a[len - i + 1]);
    }
    return len;
}
void Swap(int& _a, int& _b)
{
    int tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
