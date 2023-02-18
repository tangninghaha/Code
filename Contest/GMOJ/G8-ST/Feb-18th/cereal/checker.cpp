#include <cstdio>
#include <fstream>

using std::ifstream;

/* Constant */
const int N = 1000;

/* Declaration */
int main();

/* Variable */
int a[N + 1];
int f[N + 1];
int s[N + 1];
bool vis[N + 1];

/* Definition */
int main()
{
  ifstream in;
  in.open("./in.txt");
  int n, m;
  in >> n >> m;
  for (int i = 1; i <= n; ++i)
  {
    in >> f[i] >> s[i];
  }
  ifstream out1, out2;
  out1.open("./out1.txt");
  out2.open("./out2.txt");
  int ans1;
  int ans2;
  out1 >> ans1;
  out2 >> ans2;
  if (ans1 != ans2)
  {
    printf("Wrong Anser!\n");
    return 1;
  }
  for (int i = 1; i <= n; ++i)
    out2 >> a[i];
  int num = 0;
  for (int i = 1; i <= n; ++i)
  {
    if (!vis[f[a[i]]])
      vis[f[a[i]]] = true;
    else if (!vis[s[a[i]]])
      vis[s[a[i]]] = true;
    else
      ++num;
  }
  if (num != ans2)
  {
    printf("Wrong Solution!\n");
    return 1;
  }
  printf("Checker OK!\n");
  return 0;
}
