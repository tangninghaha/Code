#include <cstdio>

/* Declaration */
int main();
void Dfs(int, int, int, int, bool, bool);

/* Definition */
int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    Dfs(a, b, c, 0, false, 1);
}
void Dfs(int a, int b, int c, int k, bool flag, bool player)
{
    if (!a && !b && !c)
    {
        printf("winner: %s\n", player ? "First" : "Second");
        return;
    }
    if (flag && !k)
    {
        printf("winner: %s\n", player ? "First" : "Second");
        return;
    }
    if (a)
        Dfs(a - 1, b, c, k, true, !player);
    if (b)
        Dfs(a, b - 1, c, (k + 1) % 3, true, !player);
    if (c)
        Dfs(a, b, c - 1, (k + 2) % 3, true, !player);
    return;
}
