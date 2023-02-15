#include <cstdio>

/* Constant */
const int MAXANS = 1e8 + 5;

/* Declaration */
int main();
void Dfs(long long, long long, int);

/* Variable */
bool pd[MAXANS];
int ans;
int l, r, p;

/* Definition */
int main()
{
    scanf("%d%d%d", &l, &r, &p);
    Dfs(1, 0, 0);
    printf("%d", ans);
    return 0;
}

void Dfs(long long _a, long long _b, int dep)
{
    if (dep <= p)
    {
        if (!pd[_a] && _a >= l && _a <= r)
            ++ans;
        pd[_a] = true;
    }
    else
        return;
    Dfs(_a * _b, _b, dep + 1);
    Dfs(_a, _b + 1, dep + 1);
    return;
}
