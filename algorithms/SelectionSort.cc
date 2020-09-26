/*交换排序*/

#include <iostream>
using std::begin;
using std::cout;
using std::end;
using std::swap;
int main()
{
    int a[] = {9, 1, 4, 2, 5, 3, 7};
    auto length = end(a) - begin(a);
    for (decltype(length) i = 0; i < length; ++i)
    {
        decltype(length) min = i;
        //剩余元素中找最小
        for (decltype(length) j = i + 1; j < length; ++j)
            if (a[j] < a[min])
                min = j;
        swap(a[i], a[min]);
    }
    for (auto i : a)
        cout << i << " ";
    return 0;
}