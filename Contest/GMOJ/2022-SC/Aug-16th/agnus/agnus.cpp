#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 3e4;
const char pat[11] = "1agnus";

/* Declaration */
void Find(char*, int);
int main();
void FileIO();

/* Variable */
char cha[MAXN];
int tot = 0;
int agns_st[MAXN];
int agns_ed[MAXN];

/* Definition */
int main()
{
    FileIO();
    scanf("%s", cha + 1);
    cha[0] = '!';
    int len = strlen(cha) - 1;
    Find(cha, len);
    agns_st[tot + 1] = len + 1;
    agns_ed[tot + 1] = len + 1;
    long long ans = 0;
    for (int i = 1; i <= tot; ++i)
    {
        ans += agns_st[i] * (agns_ed[i + 1] - agns_ed[i]);
    }
    printf("%lld", ans);
    return 0;
}
void Find(char* a_, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= 5; ++j)
        {
            if (a_[i + j - 1] != pat[j])
            {
                break;
            }
            if (i + j - 1 > n)
                break;
            if (j == 5)
            {
                ++tot;
                agns_st[tot] = i;
                agns_ed[tot] = i + 4;
            }
        }
    }
    return;
}
void FileIO()
{
    freopen("agnus.in", "r", stdin);
    freopen("agnus.out", "w", stdout);
    return;
}
