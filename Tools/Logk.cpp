#include <stdio.h>
#include <stdlib.h>

int main()
{
	long long n, k = 0, sum = 1, x;
	printf("Number:");
	scanf("%lld", &n);
    printf("Log:");
    scanf("%d", &x);
	while (sum < n)
	{
		sum *= x;
		k++;
	}
	printf("%lld\n", k);
    system("pause");
}
