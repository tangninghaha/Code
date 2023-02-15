#include <stdio.h>

typedef long long int64;

const int64 mod = 1e9 + 7, MAXN = 15;
int64 mul[MAXN];

int64 c(int m, int n)
{
	return mul[n] / (mul[n - m] * mul[m]);
}

int main()
{
	mul[0] = 1;
	for (int i = 1; i <= 14; i++)
	{
		mul[i] = mul[i - 1] * i;
	}
	
	int n = 4;
	int64 ans = 0;
	
	for (int i = 0; i <= n; i++)
	{
		int64 ret = c(i, n);
		printf("C %d, %d: %lld\n", n, i, ret);
		ans += ret;
	}
	printf("%lld", ans);
}
