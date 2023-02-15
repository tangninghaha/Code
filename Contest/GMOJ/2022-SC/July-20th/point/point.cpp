#include <stdio.h>
const int MAXN = 5e5 + 5;
int pre[MAXN], nxt[MAXN];
long long num[MAXN];
int len[MAXN], No[MAXN];
bool pd[MAXN];
void Qsort(int l, int r);
void Swap(int &a, int &b);
int Cmp(int i, int j);
int main()
{
    freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &num[i]);
    }
    pre[1] = 1;
    nxt[n] = n;
    for (int i = n - 1; i >= 1; --i)
    {
        nxt[i] = i;
        if (num[i + 1] % num[i])
            continue;
        nxt[i] = nxt[i + 1];
        while (nxt[i] < n)
        {
            if (num[nxt[i] + 1] % num[i])
                break;
            nxt[i] = nxt[nxt[i] + 1];
        }
    }
    for (int i = 2; i <= n; ++i)
    {
        pre[i] = i;
        if (num[i - 1] % num[i])
            continue;
        pre[i] = pre[i - 1];
        while (pre[i] > 1)
        {
            if (num[pre[i] - 1] % num[i])
                break;
            pre[i] = pre[pre[i] - 1];
        }
    }
    int ans_num = 0, ans_val = 0;
    for (int i = 1; i <= n; ++i)
    {
        len[i] = nxt[i] - pre[i];
        No[i] = i;
        if (len[i] > ans_val)
        {
            ans_val = len[i];
        }
    }
    Qsort(1, n);
    for (int i = 1; i <= n; ++i)
    {
        if (pre[No[i]] == pre[No[i - 1]])
            continue;
        if (len[i] != len[i - 1] && i != 1)
            break;
        ++ans_num;
    }
    printf("%d %d\n", ans_num, ans_val);
    for (int i = 1; i <= n; ++i)
    {
        if (pre[No[i]] == pre[No[i - 1]])
            continue;
        if (len[i] != len[i - 1] && i != 1)
            break;
        printf("%d ", pre[No[i]]);
    }
    return 0;
}
int Cmp(int i, int j)
{
    if (len[i] == len[j])
    {
        if (pre[No[i]] == pre[No[j]])
            return 0;
        if (pre[No[i]] > pre[No[j]])
            return -1;
        return 1;
    }
    if (len[i] < len[j])
        return -1;
    return 1;
}
void Swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
    return;
}
void Qsort(int l, int r)
{
    int i = l, j = r, mid = (l + r) >> 1;
    while (i <= j)
    {
        while (Cmp(i, mid) > 0)
            ++i;
        while (Cmp(j, mid) < 0)
            --j;
        if (i <= j)
        {
            Swap(No[i], No[j]);
            Swap(len[i], len[j]);
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
