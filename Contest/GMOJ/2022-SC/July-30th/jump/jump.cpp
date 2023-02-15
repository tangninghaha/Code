#include <stdio.h>

const int MAXN = 2e6 + 5;

void FileIO();
int main();
int Sovle(int n, int m);

int num[MAXN];
int queue[MAXN];
int f[MAXN];
int sum[MAXN];

void FileIO()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &num[i]);
        sum[i] = sum[i - 1] + num[i];
    }
    printf("%d", Sovle(n, m));
    return 0;
}
int Sovle(int n, int m)
{
    f[0] = m;
    int head = 1, tail = 1;
    queue[1] = 0;
    for (int i = 1; i <= n; ++i)
    {
        while(f[queue[head]] < i * 100 && head <= tail)
        {
            ++head;
        }
        if (head == tail + 1)
        {
            return -1;
        }
        f[i] = f[queue[head]] + sum[i] - sum[queue[head]] - i * 100;
        while (f[i] - f[queue[tail]] > sum[i] - sum[queue[tail]] && head <= tail)
        {
            --tail;
        }
        ++tail;
        queue[tail] = i;
    }
    return f[n];
}
