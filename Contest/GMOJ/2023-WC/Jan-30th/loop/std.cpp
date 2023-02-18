#include <cstdio>
#include <cstring>
#include <ctime>

/* Constant */
const int N = 5e6;
const int mod = 998244353;
const int BASE = 19491001;

/* Declaration */
int main();
int GetHash(int, int);

/* Variable */
long long hash[N * 2];
char cha[N * 2];

long long base_pow[N * 2];

bool ans[N * 2];

/* Declaration */
int main()
{
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    base_pow[0] = 1;
    for (int i = 1; i < N * 2; ++i)
        base_pow[i] = (base_pow[i - 1] * BASE) % mod;
//    clock_t st, ed;
    while (scanf("%s", cha) != EOF)
    {
//        st = clock();
        int n;
        n = strlen(cha);
        for (int i = 0; i < n; ++i)
            cha[i + n] = cha[i];
        hash[0] = cha[0];
        for (int i = 1; i < 2 * n; ++i)
        {
            hash[i] = (hash[i - 1] * BASE) % mod + cha[i];
            hash[i] %= mod;
        }
        
        for (int i = 0; i < n; ++i)
            ans[i] = false;
        int last = 0;
//        int num = 0;
//        int sum = 0;
        for (int i = 1; i < 2 * n; ++i)
        {
//            ++num;
            if (cha[i] == cha[i - 1])
            {
//                for (int j = last; j < i; ++j)
//                {
//                    sum += i - last;
                    for (int k = i - last; k >= 1; --k)
                    {
//                        ++num;
                        if (GetHash(last, last + k - 1) != GetHash(i - k, i - 1))
                            if (i - last - k + 1 <= n)
                                ans[n - (i - last - k + 1)] = true;
                            else
                                break;
                    }
//                        else
//                            break;
//                }
                last = i;
            }
        }
//        for (int j = last; j < 2 * n; ++j)
//        {
//            sum += 2 * n - last;
            for (int k = 2 * n - last; k >= 1; --k)
            {
//                ++num;
                if (GetHash(last, last + k - 1) != GetHash(2 * n - k, 2 * n - 1))
                    if (2 * n - last - k + 1 <= n)
                        ans[n - (2 * n - last - k + 1)] = true;
                    else
                        break;
            }
//                        else
//                            break;
//        }
//        printf("\n###  %d %d  ###\n", num, sum);
        for (int i = 0; i < n; ++i)
            printf("%d", ans[i]);
        printf("\n");
//        ed = clock();
//        printf("%.2lf\n", (double)(ed - st) / CLOCKS_PER_SEC);
    }
}
int GetHash(int l, int r)
{
    return ((hash[r] - hash[l - 1] * base_pow[r - l + 1]) % mod + mod) % mod;
}
