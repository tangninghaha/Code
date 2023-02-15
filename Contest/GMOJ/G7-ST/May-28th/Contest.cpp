#include <stdio.h>

const int MAXN = 5e4 + 10;
int a[MAXN], b[MAXN];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
	}
	
	double ans = 0, k = 1.0 / n;
	int point;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			point = (a[i] - b[j]) * (a[i] - b[j]);
			if (a[i] < b[j])
				point *= -1;
			ans += k * point;
		}
	}
	printf("%.1lf", ans);
	return 0;
}
