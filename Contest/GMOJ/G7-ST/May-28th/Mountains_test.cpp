#include <stdio.h>

const int MAXN = 12;
bool vis[MAXN];
int a[MAXN];
int n = 10, ans;
void Check()
{
	int i;
	for (i = 1; i <= n; i++)
	{
		if(a[i] > a[i + 1])
		{
			break;
		}
	}
	for (i; i < n; i++)
	{
		if(a[i] < a[i + 1])
		{
			break;
		}
	}
	if(i == n) ans++;
}
void Dfs(int x)
{
	if (x > n)
	{
		Check();
	}
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
		{
			vis[i] = 1;
			a[x] = i;
			Dfs(x + 1);
			a[x] = 0;
			vis[i] = 0;
		}
	}
}

int main()
{
	Dfs(1);
	printf("%d", ans);
}
