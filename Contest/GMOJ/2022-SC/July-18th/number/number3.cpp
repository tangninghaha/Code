#include <stdio.h>
#include <string.h>
typedef long long int64;
int64 f[19][163][163][2];
int N[19], len;
int64 max(int64 a, int64 b);
void Split(int64 x);
int main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    int64 n;
    scanf("%lld", &n);
    ++n;
    Split(n);
    int64 ans = 0;
    for (int sum = 1; sum <= 162; ++sum)
    {
        memset(f, 0, sizeof(f));
        f[0][0][0][0] = 1;
        for (int i = 0; i < len; ++i)
        {
            for (int s = 0; s <= sum; ++s)
            {
                for (int m = 0; m < sum; ++m)
                {
                    for (int x = 0; x <= 9; ++x)
                    {
                        if (s + x > sum)
                            break;
                        f[i + 1][s + x][(m * 10 + x) % sum][1] += f[i][s][m][1];
                        if (x == N[i + 1])
                        {
                            f[i + 1][s + x][(m * 10 + x) % sum][0]
                            += f[i][s][m][0];
                        }
                        if (x < N[i + 1])
                        {
                            f[i + 1][s + x][(m * 10 + x) % sum][1] 
                            += f[i][s][m][0]; 
                        }
                    }
                }
            }
        }
        ans += f[len][sum][0][1];
    }
    printf("%lld", ans);
    return 0;
}



int64 max(int64 a, int64 b)
{
   return a > b ? a : b;
} 
void Split(int64 x)
{
    len = 0;
    while(x) 
    {
        ++len;
        N[len] = x % 10;
        x /= 10;
    }
	int tmp;
	for (int i = 1; i <= len / 2; ++i)
	{
		tmp = N[i];
		N[i] = N[len - i + 1];
		N[len - i + 1] = tmp;
	}
    return;
}
