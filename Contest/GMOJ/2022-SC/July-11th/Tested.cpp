#include <bits/stdc++.h>
template <typename T>
T read() {  // 声明 template 类,要求提供输入的类型T,并以此类型定义内联函数 read()
  T sum = 0, fl = 1;  // 将 sum,fl 和 ch 以输入的类型定义
  int ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') fl = -1;
  for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
  return sum * fl;
}
int main()
{
    int a;
    a = read<int>();
}
