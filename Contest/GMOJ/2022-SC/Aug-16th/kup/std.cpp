#include <cstdio>

/* Constant */
const int MAXN = 2e3 + 1;

/* Declaration */
int main();
long long GetSum(int x1, int y1, int x2, int y2);
void FileIO();
int Max(int, int);

/* Variable */
int a[MAXN][MAXN];
int s[MAXN][MAXN];
int d[MAXN][MAXN];
int l[MAXN], r[MAXN];
int sta[MAXN];
int sta_bh[MAXN];

/* Definition */
int main()
{
    FileIO();
    int n;
    long long k;
    scanf("%lld%d", &k, &n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%d", &a[i][j]);
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
        }
    }
    long long k2 = k * 2;
    for (int i = n; i >= 1; --i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (a[i][j] > k2)
            {
                a[i][j] = -1;
            }
            else if (a[i][j] >= k)
            {
                printf("%d %d %d %d", i, j, i, j);
                return 0;
            }
            else
            {
                d[i][j] = Max(i, d[i + 1][j]);
            }
        }
    }
    int top;
    int x1, y1, x2, y2;
    x1 = y1 = x2 = y2 = -1;
    for (int i = 1; i <= n; ++i)
    {
        if (x1 != -1)
            break;
        top = 0;
        for (int j = n; j >= 1; --j)
        {
            while (sta[top] > d[i][j])
            {
                l[sta_bh[top]] = j + 1;
                --top;
            }
            ++top;
            sta[top] = d[i][j];
            sta_bh[top] = j;
        }
        while (top)
        {
            l[sta_bh[top]] = 1;
            --top;
        }
        top = 0;
        for (int j = 1; j <= n; ++j)
        {
            while (sta[top] > d[i][j])
            {
                r[sta_bh[top]] = j - 1;
                --top;
            }
            ++top;
            sta[top] = d[i][j];
            sta_bh[top] = j;
        }
        while (top)
        {
            r[sta_bh[top]] = n;
            --top;
        }
        for (int j = 1; j <= n; ++j)
        {
            if (a[i][j] == -1)
                continue;
            if (GetSum(i, l[j], d[i][j], r[j]) >= k)
            {
                x1 = i;
                y1 = l[j];
                x2 = d[i][j];
                y2 = r[j];
                break;
            }
        }
    }
    if (x1 == -1)
    {
        printf("0 0 0 0");
        return 0;
    }
    int sum = GetSum(x1, y1, x2, y2);
    while (sum > k2)
    {
        if (y2 > y1)
        {
            if (GetSum(x1, y1, x2, y2 - 1) < k)
            {
                y1 = y2;
            }
            else
            {
                --y2;
                sum = GetSum(x1, y1, x2, y2);
            }
        }
        else if (x2 > x1)
        {
            if (GetSum(x1, y1, x2 - 1, y2) < k)
            {
                x1 = x2;
            }
            else
            {
                --x2;
                sum = GetSum(x1, y1, x2, y2);
            }
        }
        else
        {
            printf("0 0 0 0");
            return 0;
        }
    }
    printf("%d %d %d %d", x1, y1, x2, y2);
    return 0;
}
long long GetSum(int x1, int y1, int x2, int y2)
{
    return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
}
void FileIO()
{
    freopen("kup.in", "r", stdin);
    freopen("kup.out", "w", stdout);
    return;
}
int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}

