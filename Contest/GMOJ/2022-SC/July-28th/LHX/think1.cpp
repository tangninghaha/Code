#include <stdio.h>
const int MAXN = 505;
char str[MAXN];
void Swap(char &a, char &b);
int main()
{
    freopen("LHX.in", "r", stdin);
    freopen("LHX.out", "w", stdout);
    int n, k;
    int used_k = 0;
    scanf("%d%d", &n, &k);
    scanf("%s", str);
    if (str[n - 1] == 'j')
    {
        for (int i = 0; i < n - 2; ++i)
        {
            if (str[i] == 'z' && str[i + 1] == 'z' && used_k < k)
            {
                if (i != 0)
                    if (str[i - 1] == 'j')
                        continue;
                Swap(str[n - 1], str[i]);
                ++used_k;
                break;
            }
        }
    }
    for (int i = 0; i < n - 1; ++i)
    {
        if (str[i] == 'z')
            continue;
        if (i != 0)
            if (str[i - 1] == 'z')
                continue;
        if (str[i + 1] == 'z')
            continue;
        for (int j = 0; j < n - 1; ++j)
        {
            if (str[j] == 'z' && str[j + 1] == 'z' && used_k < k)
            {
                if (j != 0)
                    if (str[j - 1] == 'j')
                        continue;
                Swap(str[i], str[j]);
                ++used_k;
                break;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        if (str[i] == 'j' && str[i + 1] == 'z')
        {
            ++ans;
        }
    }
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
