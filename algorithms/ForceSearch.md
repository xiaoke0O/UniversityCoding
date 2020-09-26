# 最简单的暴力法 子字符串查找

原理很简单。从文本字符串开头出发，以模式字符串的长度为周期，逐个字符匹配。
在模式字符串的全部字符循环周期内，所有字符都配上了，就返回这时模式字符串第一个元素所对应的字符在文本字符串的位置。

```cpp
#include <iostream>
#include <string>
using namespace std;

size_t ForceSearch(string pat, string txt) {
  auto M = pat.length();
  auto N = txt.length();
  for (size_t i = 0; i <= N - M; ++i) {
    size_t j;
    for (j = 0; j < M; ++j)
      if (txt[i + j] != pat[j]) break;
    if (j == M) return i;
  }
  return N;
}

int main() {
  string a("I like my cup.");
  string b("cup");
  cout << ForceSearch(b, a) << endl;
  return 0;
}
```

```cpp
第一轮：            I like my cup.
每个字符都配不上     cup
每个字符都配不上      cup
每个字符都配不上       cup

.......

直到                         cup

输出10          
---------------------
```