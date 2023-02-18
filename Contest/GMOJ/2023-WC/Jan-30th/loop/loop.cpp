#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 5e6 + 1;

/* Declaration */
int main();
int Max(int, int);
int Min(int, int);
bool Check(int, int, int);

/* Variable */
char cha[MAXN * 2];

/* Definition */
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
int main()
{
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    int len;
    while (scanf("%s", cha) != EOF)
    {
        len = strlen(cha);
        for (int i = 0; i < len; ++i)
            cha[i + len] = cha[i];
        bool ans;
        for (int i = 0; i < len - 1; ++i)
        {
            ans = false;
            for (int k = 0; k < len; ++k)
            {
                if (Check(len, k, i))
                {
                    ans = true;
                    break;
                }
            }
            printf("%d", ans);
        }
        printf("0\n");
    }
    return 0;
}
bool Check(int len, int cut_st, int cut_len)
{
    int cut_ed = cut_st + cut_len - 1;
    int lst = -1;
    int first = -1;
    for (int i = 0; i < len; ++i)
    {
        if (i >= cut_st && i <= cut_ed)
            continue;
        if (i + len >= cut_st && i + len <= cut_ed)
            continue;
        if (lst == -1)
        {
            lst = i;
            first = i;
            continue;
        }
        if (cha[lst] == cha[i])
            return false;
        lst = i;
    }
    if (cha[first] == cha[lst])
        return false;
    return true;
}
