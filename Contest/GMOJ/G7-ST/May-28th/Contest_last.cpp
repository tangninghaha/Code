#include <stdio.h>

typedef long long int64;
const int MAXN = 5e4 + 10;
int64 a[MAXN], b[MAXN];
int64 sum_pow[MAXN], sum[MAXN];

void swap(int64 &a, int64 &b)
{
	int64 t = a;
	a = b;
	b = t;
}
void Qsort(int l, int r, int64 *num)
{
	int i = l, j = r, mid = num[(l + r) >> 1];
	while (i < j)
	{
		while (num[i] < mid) i++;
		while (num[j] > mid) j--;
		if (i <= j)
		{
			swap(num[i], num[j]);
			i++;
			j--;
		}
	}
	if(i < r) Qsort(i, r, num);
	if(l < j) Qsort(l, j, num);
}

int main()
{
	freopen("in.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &b[i]);
	}
	Qsort(1, n, b);
	sum_pow[0] = sum[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		sum_pow[i] = sum_pow[i - 1] + b[i] * b[i];
		sum[i] = sum[i - 1] + b[i];
	}
	double ans = 0, bili = 1.0 / n;
	double point = 0;
	for (int i = 1; i <= n; i++)
	{
		point = 0;
		int lbound = 1, rbound = n, k = n + 1;
		while (lbound < rbound)
		{
			int mid = (lbound + rbound) / 2;
			if (a[i] >= b[mid])
			{
				lbound = mid + 1;
			}
			else
			{
				k = mid;
				rbound = mid;
			}
		}
		while (a[i] < b[k - 1] && k > 0)
			k--;
		point = bili * ((k - 1) * a[i] * a[i] - (n - k + 1) * a[i] * a[i]);
		point += bili * (sum_pow[k - 1] - 2 * a[i] * sum[k - 1]);
		point += bili * (-1 * (sum_pow[n] - sum_pow[k - 1]) + 2 * a[i] * (sum[n] - sum[k - 1]));
		ans += point;
	}
	printf("%.1lf", ans);
	return 0;
}
