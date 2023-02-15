#include <stdio.h>
#include <cmath>

int main()
{
	int n = 1e9 + 7;
	for (int i = 2; i <= sqrt(n) + 1; i++)
	{
		if(n % i == 0)
		{
			printf("No: %d\n", i);
		}
	}
	printf("Yes:%d\n", 31623*31623);
	return 0;
}
