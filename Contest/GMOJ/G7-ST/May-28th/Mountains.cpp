#include <stdio.h>

typedef long long int64;

const int64 mod = 1e9 + 7, MAXN = 1e5 + 10;
int64 mul[MAXN];

int64 QuickPow(int64 a, int64 b)
{
	if (b == 1)
		return a;
	int64 ret = QuickPow(a, b / 2) % mod;
	if (b % 2)
	{
		return (((ret * ret) % mod) * a) % mod;
	}
	else
	{
		return (ret * ret) % mod;
	}
}

int64 c(int m, int n)
{
	return (mul[n] * (QuickPow((mul[n - m] * mul[m]) % mod, mod - 2)) % mod) % mod;
}

void Init()
{
	mul[0] = 1;
	for (int i = 1; i <= 100000; i++)
	{
		mul[i] = mul[i - 1] * i;
		mul[i] %= mod;
	}
}

int main()
{
	Init();
	int n;
	scanf("%d", &n);
	int64 ans = 0;
	
	for (int i = 0; i < n; i++)
	{
		ans += c(i, n - 1);
		ans %= mod;
	}
	printf("%lld", ans % mod);
}
