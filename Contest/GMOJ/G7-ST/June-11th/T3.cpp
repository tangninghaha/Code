#include <stdio.h>
#include <cstring>

int a[17];
int ch[17];
bool vis_2[17];

void Dfs(int deep, int x, int sum, int last);
bool dfs_2(int num, int x, int flag);
int n;
int tot, tonum, allnum;
int ans;

int main()
{
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    if (n < 4)
    {
        printf("No Solution");
        return 0;
    }
    for (int i = n; i >= 4; i--)
    {
        Dfs(i, 1, 0, 0);
    }
    if (ans == 0)
        printf ("No Solution");
    else
        printf("%d", ans);
}

void Dfs(int deep, int x, int sum, int last)
{
    if (x > deep)
    {
        if (sum % 2)
            return;
        sum /= 2;
        allnum = sum;
        tot = deep;
        for (int i = sum / 2; i >= 1; i--)
        {
            if (i * (sum - i) <= ans) continue;
            tonum = i;
            memset(vis_2, 0, sizeof(vis_2));
            if (dfs_2(i, 1, 1))
            {
                ans = i * (sum - i);
            }
        }
        return;
    }
    for (int i = last + 1; i <= n; i++)
    {
        ch[x] = a[i];
        Dfs(deep, x + 1, sum + a[i], i);
    }
}

bool dfs_2(int num, int x, int flag)
{
    if (num == 0)
    {
        if (flag == 4)
            return 1;
        if (flag == 3) 
        {
            if (dfs_2(allnum - tonum, 1, 4))
                return 1;
            return 0;
        }
        else if (flag == 2)
        {
            if (dfs_2(allnum - tonum, 1, 3))
                return 1;
            return 0;
        }
        else if (flag == 1)
        {
            if (dfs_2(tonum, 1, 2))
                return 1;
            return 0;
        }
        return 0;
    }
    if (x > tot)
    {
        return 0;
    }
    for (int i = 1; i <= tot; i++)
    {
        if (!vis_2[i] && num >= ch[i])
        {
            vis_2[i] = 1;
            if(dfs_2(num - ch[i], x + 1, flag))
                return 1;
            vis_2[i] = 0;
        }
    }
    return 0;
}

