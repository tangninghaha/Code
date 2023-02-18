#include <cstdio>
#include <cstdlib>

int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    printf("Test: %d/%d\n", i, n);
    system("gen > in.txt");
    system("bf < in.txt > out1.txt");
    system("solution < in.txt > out2.txt");
    if (system("checker"))
    {
      system("pause");
      return 1;
    }
  }
  return 0;
}
