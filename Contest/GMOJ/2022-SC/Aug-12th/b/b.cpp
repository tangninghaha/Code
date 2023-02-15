#include <cstdio>

/* Constant */
const int MAXN = 2005;

/* Declaration */
int main();
void FileIO();

/* Variable */
int fa[MAXN];

/* Definition */

int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d", &fa[i + 1]);
    }
    if (n == 1)
        printf("%d", 0);
    if (n == 2)
    {
        printf("0\n1");
    }
    if (n == 3)
    {
        if (fa[2] == 1 && fa[3] == 1)
        {
            printf("%d\n%d\n%d", 0, 1, 1);
        }
        else if (fa[2] == 3)
        {
            printf("%d\n%d\n%d", 0, 2, 2);
        }
        else if (fa[3] == 2)
        {
            printf("%d\n%d\n%d", 0, 2, 2);
        }
    }
}
void FileIO()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    return;
}
