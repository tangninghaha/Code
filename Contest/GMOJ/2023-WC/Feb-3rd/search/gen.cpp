#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

using std::string;

string a[10] = {"CCCFCSP", "NOINOIPCSP", "2023Chengdu", "WTCAKIOI", "LuoShuoBoZaiFuShui", "BuYaoZaiFubai", "FengD"};

int main()
{
  int n, m, l, len;
  for (int i = 7; i < 10; ++i)
  {
    len = rand() % 10 + 1;
    for (int j = 1; j <= len; ++j)
      a[i] += rand() % 26 + 'a';
  }
  const int LEN = 100;
  n = 100;
  m = rand() % 100 + 1;
  l = 5;
  printf("%d %d %d\n", n, m, l);
  for (int i = 1; i <= n; ++i)
  {
    len = rand() % LEN + 1;
    while (len < l)
      len = rand() % LEN + 1;
    for (int j = 1; j <= len; ++j)
    {
      if (rand() & 1)
        printf("%c", rand() % 26 + 'a');
      else
        printf("%s", a[rand() % 10].c_str());
    }
    printf("\n");
  }
  return 0;
}
