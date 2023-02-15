#include <stdio.h>
#include <string.h>
#define int long long
#define INF 10000000000

const int LENA = 105, LENB = 200005;

const int mod = 998244353;
const int base = 19491001;
void FileIO();
int GetHashB(int l, int r);
void InitBasePow(int n);
void InitF(int n);
void InitHashA(int len);
void InitHashB(int len);
signed main();
int Sovle(int lena, int lenb);

int base_pow[LENB];
int hash_a[51];
int hash_b[LENB];
int len_hash_a[51];
int tot_hash_a;
int f[LENB][51];
char a[LENA];
char b[LENB];

void FileIO()
{
    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);
    return;
}
int GetHashB(int l, int r)
{
    return ((hash_b[r] - (hash_b[l - 1] * base_pow[r - l + 1]) % mod)
            % mod + mod) % mod;
}
void InitBasePow(int n)
{
    base_pow[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        base_pow[i] = base_pow[i - 1] * base;
        base_pow[i] %= mod;
    }
    return;
}
void InitF(int n)
{
    for (int i = 1; i <= tot_hash_a; ++i)
    {
        f[n + 1][i] = INF;
    }
    for (int i = n; i >= 1; --i)
    {
        for (int j = 1; j <= tot_hash_a; ++j)
        {
            f[i][j] = f[i + 1][j];
            if (GetHashB(i, i + len_hash_a[j] - 1) == hash_a[j]
                && i + len_hash_a[j] - 1 <= n)
            {
                f[i][j] = i;
            }
        }
    }
    return;
}
void InitHashA(int len)
{
    int i = 1;
    while (i <= len)
    {
        while (a[i] == '*')
        {
            ++i;
        }
        if (i > len)
        {
            break;
        }
        if (i == 1 && a[i] != '*')
        {
            while (a[i] != '*' && i <= len)
            {
                ++i;
            }
            continue;
        }
        while (a[i] == '*')
        {
            ++i;
        }
        if (i > len)
        {
            break;
        }
        ++tot_hash_a;
        while (a[i] != '*' && i <= len)
        {
            ++len_hash_a[tot_hash_a];
            hash_a[tot_hash_a] = hash_a[tot_hash_a] * base + a[i];
            hash_a[tot_hash_a] %= mod;
            ++i;
        }
    }
    if (a[len] != '*')
    {
        --tot_hash_a;
    }
    return;
}
void InitHashB(int len)
{
    for (int i = 1; i <= len; ++i)
    {
        hash_b[i] = hash_b[i - 1] * base + b[i];
        hash_b[i] %= mod;
    }
    return;
}
signed main()
{
    FileIO();
    scanf("%s%s", a + 1, b + 1);
    a[0] = '.';
    b[0] = '.';
    int lena = strlen(a) - 1;
    int lenb = strlen(b) - 1;
    for (int i = 1; i <= lenb; ++i)
    {
        b[i + lenb] = b[i];
    }
    printf("%lld", Sovle(lena, lenb));
    return 0;
}
int Sovle(int lena, int lenb)
{
    InitBasePow(lenb * 2);
    InitHashA(lena);
    InitHashB(lenb * 2);
    InitF(lenb * 2);
    int ed;
    int now = 1;
    int ans = 0;
    bool pdd;
    for (int st = 1; st <= lenb; ++st)
    {
        pdd = false;
        ed = st + lenb - 1;
        now = st;
        if (a[1] != '*')
        {
            bool pd = false;
            int x = 1;
            while (now <= ed)
            {
                if (a[x] == '*')
                    break;
                if (a[x] != b[now])
                {
                    pd = true;
                    break;
                }
                ++x;
                ++now;
            }
            if (pd)
                continue;
        }
        now = st;
        for (int i = 1; i <= tot_hash_a; ++i)
        {
            if (now >= INF)
            {
                break;
            }
            now = f[now][i] + len_hash_a[i];
        }
        --now;
        if (now <= ed && now != 0)
        {
            pdd = true;
        }
        now = ed;
        if (a[lena] != '*')
        {
            bool pd = false;
            int x = lena;
            while (now >= st)
            {
                if (a[x] == '*')
                    break;
                if (a[x] != b[now])
                {
                    pd = true;
                    break;
                }
                --x;
                --now;
            }
            if (pd)
                continue;
        }
        if (pdd)
        {
            ++ans;
        }
    }
    return ans;
}
