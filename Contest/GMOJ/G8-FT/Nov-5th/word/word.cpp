#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 5e5 + 5;

/* Declaration */
int main();

/* Variable */
char a[15][15];
int lena[15];
char str[MAXN];

/* Definition */
int main()
{
    freopen("word.in", "r", stdin);
    freopen("word.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for (int fot = 1; fot <= t; ++fot)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%s", a[i]);
            lena[i] = strlen(a[i]);
        }
        scanf("%s", str);
        int lenstr;
        lenstr = strlen(str);
        int k;
        for (int i = 0; i < lenstr; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                k = 0;
                while (str[i - k] == a[j][lena[j] - k - 1])
                {
                    ++k;
                    if (k == lena[j])
                    {
                        str[i] = '*';
                        break;
                    }
                }
            }
        }
        printf("%s\n", str);
    }
    return 0;
}
