#include <cstdio>

/* Constant */
const int MAXN = 2e5 + 5;

/* Declaration */
int main();
void Dfs(int);

/* Variable */
int p[MAXN];
int rk[MAXN];
int ans[MAXN];
bool pd[MAXN];
bool vis[MAXN];
int s[MAXN];
int n;
int left[MAXN];
int right[MAXN];

/* Declaration */
int main()
{
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &p[i]);
        rk[p[i]] = i;
        s[i] = n + 1;
        left[i] = i - 1;
        right[i] = i + 1;
    }
    Dfs(n / 2);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", s[i]);
    }
    return 0;
}
void Dfs(int _x)
{
    if (!_x)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (ans[i] < s[i])
            {
                break;
            }
            if (ans[i] > s[i])
            {
                return;
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            s[i] = ans[i];
        }
        return;
    }
    for (int i = 1; i < n; ++i)
    {
        if (!pd[i] && !pd[right[i]] && right[i] <= n)
        {
            pd[i] = true;
            pd[right[i]] = true;
            ans[_x * 2 - 1] = p[i];
            ans[_x * 2] = p[right[i]];
            right[left[i]] = right[right[i]];
            left[right[right[i]]] = left[i];
            Dfs(_x - 1);
            right[left[i]] = i;
            left[right[right[i]]] = right[i];
            ans[_x * 2 - 1] = 0;
            ans[_x * 2] = 0;
            pd[i] = false;
            pd[right[i]] = false;
        }
    }
    return;
}
