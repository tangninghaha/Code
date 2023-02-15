#include <stdio.h>
const int MAXN = 505;
char str[MAXN];
int n, k;
void Dfs(int x, int last);
void Swap(char &a, char &b);
int ans = 0;
int main()
{
    freopen("LHX.in", "r", stdin);
    freopen("LHX.out", "w", stdout);
    scanf("%d%d", &n, &k);
    str[0] = '#';
    scanf("%s", str + 1);
    Dfs(1, 0);
    printf("%d", ans);
    return 0;
}
void Swap(char &a, char &b)
{
    char tmp = a;
    a = b;
    b = tmp;
    return;
}
void Dfs(int x, int last)
{
    int sum = 0;
    for (int i = 1; i < n; ++i)
    {
        if (str[i] == 'j' && str[i + 1] == 'z')
            ++sum;
    }
    if (sum > ans)
    {
        ans = sum;
    }
    if (x > k)
        return;
    bool pd;
    int No;
    for (int i = last + 1; i <= n; ++i)
    {
        if (str[i] == 'z')
            continue;
        pd = false;
        for (int j = 1; j < n; ++j)
        {
            if ((str[j - 1] == 'z' || j == 1) && str[j] == 'z' 
                && (str[j + 1] == 'z' || j + 1 == i))
            {
                Swap(str[j], str[i]);
                pd = true;
                No = j;
                break;
            }
        }
        if (pd)
        {
            Dfs(x + 1, i);
            Swap(str[No], str[i]);
        }
    }
    return;
}
