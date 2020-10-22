//三向切分的快速排序
#include <iostream>
using std::cout;
using std::swap;
void sort(int a[], int lo, int hi)
{
    if (hi <= lo)
        return;
    int lt = lo, i = lo + 1, gt = hi;
    int v = a[lo];
    while (i <= gt)
    {
        if (a[i] < v)
            swap(a[lt++], a[i++]);
        else if (a[i] > v)
            swap(a[i], a[gt--]);
        else
            i++;
    }
    sort(a, lo, lt - 1);
    sort(a, gt + 1, hi);
}
int main()
{
    int int_arr[10] = {9, 1, 8, 7, 4, 6, 2, 5, 9, 0};
    sort(int_arr, 0, 9);
    for (auto i : int_arr)
        cout << i << " ";
    return 0;
}
