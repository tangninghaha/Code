#include <stdio.h>

typedef long long int64;
const int64 mod = 1e9 + 7;

int64 QuickPow(int64 a, int64 b)
{
	if (b == 1)
	{
		return a % mod;
	}
	int64 ret = QuickPow(a, b / 2) % mod;
	if (b % 2 == 1)
	{
		return (((ret * ret) % mod) * a) % mod;
	}
	else
	{
		return (ret * ret) % mod;
	}
}

int main()
{
	int64 n;
	scanf("%lld", &n);
	printf("%lld", QuickPow(2, n - 1) % mod);
}
