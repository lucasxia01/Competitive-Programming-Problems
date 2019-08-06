#include <iostream>
using namespace std;

int solve(int a[], int size) {
    bool good = true;
    for (int i = 1; i < size; i++) {
        if (a[i] < a[i - 1]) good = false;
    }
    if (good) return size;
    return max(solve(a, size/2), solve(a + size/2, size/2));
}
int main() {
    int i = 0x11223344;
    short * c_point = (short *) &i;
    short c = *c_point;
    short j = (short) c;
    cout << j << endl;
    return 0;
}
