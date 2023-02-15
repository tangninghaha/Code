#include <stdio.h>
#include <cmath>

const int MAXN = 1010;
const int mod = 999983;
long long f[MAXN][9 * MAXN];
int s[11], slen;

int main()
{
	int n;
	scanf("%d", &n);
	char cha = getchar();
	while (cha < '0' || cha > '9')
	{
		cha = getchar();
	}
	while (cha >= '0' && cha <= '9')
	{
		slen++;
		s[slen] = cha - '0';
		cha = getchar();
	}
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= 9 * n; j++)
		{
			for (int k = 1; k <= slen; k++)
			{
				if (j >= s[k])
				{
					f[i][j] += f[i - 1][j - s[k]];
					f[i][j] %= mod;
				}
			}
		}
	}
	
	long long ans = 0;
	for (int i = 0; i <= 9 * n; i++)
	{
		ans += f[n][i] * f[n][i];
		ans %= mod;
	}
	ans *= 2;
	ans %= mod;
	int up = ceil(n / 2), down = n / 2;
	for (int i = 0; i <= 9 * n; i++)
	{
		for (int j = 0; j <= 9 * n; j++)
		{
			ans -= f[up][i] * f[up][i] * f[down][j] * f[down][j];
			ans = ((ans % mod) + mod) % mod;
		}	
	}
	printf("%lld", ans % mod);
	return 0;
}
