#include <cstdio>
#include <algorithm>

/* Constant */
const int N = 1e5;

/* Class */
class Point
{
  public:
    int x;
    int y;
    int t;
};
bool operator<(Point _x, Point _y)
{
  if (_x.x == _y.x)
    return _x.y < _y.y;
  return _x.x < _y.x;
}

/* Declaration */
int main();

/* Variable */
Point c[N + 1];
Point ali[N + 1];

/* Definition */
int main()
{
  int g, n;
  scanf("%d", &g, &n);
  for (int i = 1; i <= g; ++i)
  {
    scanf("%d%d", &
  }
}
