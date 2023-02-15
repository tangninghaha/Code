#include <stdio.h>
#include <stdlib.h>
#include <ctime>

const int c = 50000;

int main()
{
	srand(time(0));
	freopen("in.txt", "w", stdout);
	int n = 50000;
	printf("%d\n", n);
	for (int i = 1; i <= n; i++)
	{
		int t = rand() % c + 1;
		printf("%d ", c);
	}
	printf("\n");
	for (int i = 1; i <= n; i++)
	{
		int t = rand() % c + 1;
		printf("%d ", t);
	}
	printf("\n");
}
