#include <iostream>
#include <cassert>
using namespace std;

bool somePredicate(double x) {
    return x > 0;
}
// Return true if the somePredicate function returns true for at
// least one of the array elements, false otherwise.
bool anyTrue(const double a[], int n)
{
    if (n <= 0) return false;
    if (n == 1) return somePredicate(a[0]);
    return (somePredicate(a[n - 1]) || anyTrue(a, n - 1));  // This is always correct.
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n <= 0) return 0;
    return somePredicate(a[n - 1]) + countTrue(a, n - 1);  // This is correct.
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (n <= 0) return -1;
    int ans = firstTrue(a, n - 1);
    if (somePredicate(a[n - 1])) {
        if (ans != -1) return ans;
        else return n - 1;
    }
    return ans;   // This is correct.
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfMin(const double a[], int n)
{
    if (n <= 0) return -1;
    int ans = positionOfMin(a, n - 1);
    if (ans == -1) return n - 1;
    if (ans != -1 && a[n - 1] < a[ans]) return n - 1;
    return ans;   // This is correct.
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0) return true;
    if (n1 <= 0 && n2 > 0) return false;
    if (a1[0] == a2[0]) return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    return includes(a1 + 1, n1 - 1, a2, n2);  // This is always correct.
}

int main() {
    const double a[6] = {1, -2, 3, -4, 5, -8};
    const double b[3] = {1, 3, 3};
    const double b1[3] = {1, -2, 5};
    const double c[7] = {0, 0, 0, 0, 0, 0, 3};
    assert(firstTrue(a, 0) == -1);
    assert(firstTrue(a, -2) == -1);
    assert(positionOfMin(a, 0) == -1);
    assert(positionOfMin(a, -1) == -1);
    assert(includes(a, 6, b, 3) == 0);
    assert(includes(a, 6, b1, 3) == 1);
    assert(positionOfMin(c, 7) == 0);
    assert(includes(c, 6, b, 3) == 0);
    assert(includes(c, 6, b1, 3) == 0);
    assert(includes(a, 6, a, 3) == 1);
    assert(includes(c, 7, c, 6) == 1);
    assert(includes(c, 3, c, 7) == 0);
    assert(includes(c + 3, 3, c, 3) == 1);
    cout << "All test cases passed!" << endl;
    return 0;
}
