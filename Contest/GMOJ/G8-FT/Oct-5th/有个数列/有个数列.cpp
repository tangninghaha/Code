#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const long long INF = 1e17;

/* Declaration */
int main();

/* Variable */
long long a[MAXN * 2];
long long s[MAXN * 2];
long long q[MAXN * 2];
long long q2[MAXN * 2];

/* Definition */
int main()
{
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    bool negative = true;
    long long big_num = -INF;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        a[i + n] = a[i];
        if (a[i] > 0)
        {
            negative = false;
        }
        if (a[i] > big_num)
        {
            big_num = a[i];
        }
    }
    if (negative)
    {
        printf("%lld", big_num);
        return 0;
    }
    int n2 = 2 * n;
    for (int i = 1; i <= n2; ++i)
    {
        s[i] = s[i - 1] + a[i];
    }
    long long sum = 0;
    int sum_num = 0;
    long long ans = -INF;
    int head = 1, tail = 0;
    int st = 1;
    for (int i = 1; i <= n2; ++i)
    {
        sum += a[i];
        ++sum_num;
        if (sum <= 0)
        {
            st = i + 1;
            sum = 0;
            sum_num = 0;
        }
        if (sum_num > n)
        {
            while (q2[head] <= st && head <= tail)
            {
                ++head;
            }
            if (head > tail)
            {
                sum = 0;
                sum_num = 0;
            }
            sum_num = i - q2[head] + 1;
            sum -= q[head] - s[st - 1];
            st = q2[head] + 1;
            if (sum <= 0)
            {
                st = i + 1;
                sum = 0;
                sum_num = 0;
            }
        }
        if (sum > ans && sum_num)
        {
            ans = sum;
        }
        while (q[tail] >= s[i] && head <= tail)
        {
            --tail;
        }
        ++tail;
        q[tail] = s[i];
        q2[tail] = i;
    }

    printf("%lld", ans);
    return 0;
}
