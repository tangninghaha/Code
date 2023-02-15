#include <stdio.h>
#include <cstring>

const int MAXN = 50005;

struct HASH
{
    long long mod;
    long long base;
    long long hash[MAXN];
    long long base_pow[MAXN];
    HASH(int mod_num, int base_num);
    void Init(const char str[], int len);
    long long GetHash(int l, int r);
};

HASH hasha1(19491001, 520);
HASH hasha2(1000000009, 2020);
HASH hashb1(19491001, 520);
HASH hashb2(1000000009, 2020);

char a[MAXN], b[MAXN];

int max(int a, int b);
int min(int a, int b);
int GetLCP(int lena, int lenb, int sta, int stb);

int main()
{
    freopen("data4.in", "r", stdin);
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    a[0] = b[0] = '*';
    int lena = strlen(a) - 1, lenb = strlen(b) - 1;
    int lcp, ans = 0;
    hasha1.Init(a, lena);
    hasha2.Init(a, lena);
    hashb1.Init(b, lenb);
    hashb2.Init(b, lenb);
    for (int i = 1; i <= lenb; ++i)
    {
        lcp = GetLCP(lena, lenb, 1, i);
        if (lcp == lena)
        {
            printf("%d", lcp);
            return 0;
        }
        lcp = GetLCP(lena, lenb, lcp + 2, lcp + i + 1) + lcp;
        if (i + lcp - 1 != lenb) ++lcp;
        // printf("%d %d\n", i, lcp);
        ans = max(ans, lcp);
    }
    printf("%d", ans);
    return 0;
}

int GetLCP(int lena, int lenb, int sta, int stb)
{
    int lbound = 0, rbound = min(lena - sta + 1, lenb - stb + 1), ret = 0, len;
    while (lbound < rbound)
    {
        len = (lbound + rbound + 1) / 2;
        if (hasha1.GetHash(sta, len + sta - 1) == hashb1.GetHash(stb, stb + len - 1)
            && hasha2.GetHash(sta, len + sta - 1) == hashb2.GetHash(stb, stb + len - 1))
        {
            lbound = len;
            ret = len;
        }
        else
            rbound = len - 1;
    }
    return ret;
}

HASH::HASH(int mod_num, int base_num)
{
    mod = mod_num;
    base = base_num;
    base_pow[0] = 1;
    for(int i = 1; i < MAXN; ++i)
    {
        base_pow[i] = base_pow[i - 1] * base;
        base_pow[i] %= mod;
    }
    return;
}

void HASH::Init(const char str[], int len)
{
    hash[0] = 0;
    for (int i = 1; i <= len; i++)
    {
        hash[i] = hash[i - 1] * base + str[i];
        hash[i] %= mod;
    }
    return;
}

long long HASH::GetHash(int l, int r)
{
    return ((hash[r] - base_pow[r - l + 1] * hash[l - 1]) % mod + mod) % mod;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
