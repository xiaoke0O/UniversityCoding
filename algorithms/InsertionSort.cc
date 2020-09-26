/*插入排序*/
#include <iostream>
using std::begin;
using std::cout;
using std::end;
using std::swap;
int main()
{
    int a[] = {9, 1, 4, 2, 5, 3, 7};
    auto length = end(a) - begin(a);
    for (decltype(length) i = 1; i < length; ++i)
    {
        for (decltype(length) j = i; j > 0 && (a[j] < a[j - 1]); --j)
            swap(a[j], a[j - 1]);
    }
    for (auto i : a)
        cout << i << " ";
    return 0;
}
