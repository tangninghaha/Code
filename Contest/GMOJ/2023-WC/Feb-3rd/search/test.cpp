#include <cstdio>
#include <algorithm>

int a[500];

int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &a[i]);
  }
  printf("-----");
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i)
    printf("%d\n", a[i]);
}
