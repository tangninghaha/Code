#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 3e4 + 5;
const char pat[11] = "!agnus";

/* Declaration */
int main();
void FileIO();
bool Check(int, int);

/* Variable */
char cha[MAXN];

/* Definition */
int main()
{
    // FileIO();
    scanf("%s", cha + 1);
    cha[0] = '!';
    int len = strlen(cha) - 1;
    long long ans = 0;
    for (int i = 1; i <= len; ++i)
    {
        for (int j = i; j <= len; ++j)
        {
            if (Check(i, j))
            {
                // printf("%d %d\n", i, j);
                ++ans;
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
void FileIO()
{
    freopen("agnus.in", "r", stdin);
    freopen("agnus.out", "w", stdout);
    return;
}
bool Check(int l, int r)
{
    for (int i = l; i <= r; ++i)
    {
        for (int j = 1; j <= 5; ++j)
        {
            if (cha[i + j - 1] != pat[j])
            {
                break;
            }
            if (i + j - 1 > r)
                break;
            if (j == 5)
                return true;
        }
    }
    return false;
}
