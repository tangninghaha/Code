#include <cstdio>
#include <cstdlib>

/* Decalration */
int main();

/* Definition */
int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    printf("%d/%d\n", i, n);
    system("gen.exe > in.txt");
    system("bf.exe < in.txt > out1.txt");
    system("sort.exe < in.txt > out2.txt");
    if (system("fc out1.txt out2.txt"))
    {
      printf("Wrong Answer!\n");
      system("pause");
      system("pause");
      return 0;
    }
  }
  printf("Happy New Year\n");
  system("pause");
  system("pause");
  return 0;
}
