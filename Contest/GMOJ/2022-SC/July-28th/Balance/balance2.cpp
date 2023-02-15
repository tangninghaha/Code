#include <stdio.h>
#define INF 1000000000000005
const int MAXN = 1e5 + 5;
typedef long long int64;
int num_l[MAXN];
int num_r[MAXN];
int64 sum_l[MAXN][2];
int64 sum_r[MAXN][2];
int64 qz_l[MAXN][2];
int64 hz_r[MAXN][2];
int64 not_order_num_l;
int not_order_num_r;

int64 Sovle(int n);
int64 GetAns1(int n);
int64 GetAns2(int n);
int64 Abs(int64 x);
int64 Min(const int64 &a, const int64 &b);
void InitQzHz(int n);
void InitNotOrderNum(int n);
int main();

int main()
{
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &num_l[i]);
        sum_l[i][0] = sum_l[i - 1][0] + (num_l[i] == 0);
        sum_l[i][1] = sum_l[i - 1][1] + (num_l[i] == 1);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &num_r[i]);
        sum_r[i][0] = sum_r[i - 1][0] + (num_r[i] == 0);
        sum_r[i][1] = sum_l[i - 1][1] + (num_r[i] == 1);
    }
    InitNotOrderNum(n);
    printf("%lld", Sovle(n));
    return 0;
}
void InitQzHz(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        qz_l[i][0] = qz_l[i - 1][0] + (num_l[i] == 0);
        qz_l[i][1] = qz_l[i - 1][1] + (num_l[i] == 1);
    }
    for (int i = n; i >= 1; --i)
    {
        hz_r[i][0] = hz_r[i + 1][0] + (num_r[i] == 0);
        hz_r[i][1] = hz_r[i + 1][1] + (num_r[i] == 1);
    }
    return;
}
void InitNotOrderNum(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        if (num_l[i] == 0)
            continue;
        not_order_num_l += sum_l[n][0] - sum_l[i][0];
    }
    for (int i = 1; i <= n; ++i)
    {
        if (num_r[i] == 0)
            continue;
        not_order_num_r += sum_r[n][0] - sum_r[i][0];
    }
    return;
}
int64 Sovle(int n)
{
    int64 ret;
    ret = GetAns1(n);
    ret = Min(ret, GetAns2(n));
    return ret;
}
int64 GetAns1(int n)
{
    return Abs(not_order_num_l - not_order_num_r);
}
int64 GetAns2(int n)
{
    int64 now_not_order_num_l = not_order_num_l;
    int64 now_not_order_num_r = not_order_num_r;
    int64 ret = INF, cnt;
    int hz_l[2] = {0, 0};
    int qz_r[2] = {0, 0};
    if (now_not_order_num_l < now_not_order_num_r)
    {
        int i = n, j = 1;
        while (true)
        {
            while (num_l[i] && i >= 1)
            {
                ++hz_l[1];
                --i;
            }
            while (!num_r[j] && j <= n)
            {
                ++qz_r[0];
                ++j;
            }
            if (i < 1 || j > n)
                break;
            now_not_order_num_l -= hz_l[0];
            now_not_order_num_l += qz_l[i - 1][1];
            now_not_order_num_r -= qz_r[1];
            now_not_order_num_r += hz_r[j + 1][0];
            ++hz_l[1];
            ++qz_r[0];
            cnt = (j + n - i) * 2;
            ret = Min(ret, 
                      cnt + Abs(now_not_order_num_l - now_not_order_num_r));
        }
    }
    return ret;
}
int64 Abs(int64 x)
{
    return x > 0 ? x : -x;
}
int64 Min(const int64 &a, const int64 &b)
{
    return a < b ? a : b;
}
