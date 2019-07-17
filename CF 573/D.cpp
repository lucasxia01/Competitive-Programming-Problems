#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, const char * argv[]) {
    long long n;
    cin >> n;
    long long a[n], b[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = 0;
    }
    sort(a, a+n);
//    for (int i = 0; i < n; i++) {
//        cout << a[i] << endl;
//    }
    if (n > 1 && a[0] == 0 && a[1] == 0) {
        cout << "cslnb" << endl;
        return 0;
    }
    for (int i = 0; i < n-2; i++) {
        if (a[i] == a[i+2]) {
            cout << "cslnb" << endl;
            return 0;
        }
    }
    int double_count = 0;
    for (int i = 0; i < n-1; i++) {
        if (a[i] == a[i+1]) {
            if (i != 0 && a[i - 1] == a[i] - 1) double_count++;
            double_count++;
        }
    }
    if (double_count > 1) {
        cout << "cslnb" << endl;
        return 0;
    }
    long long count = 0;
    for (int i = 0; i < n; i++) {
        if (i != 0 && a[i-1] == a[i] && count > a[i]) {
            count--;
        }
        b[i] = count;
        count++;
    }
//    for (int i = 0; i < n; i++) {
//        cout << b[i] << endl;
//    }
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] - b[i];
    }
    if (sum % 2) cout << "sjfnb" << endl;
    else cout << "cslnb" << endl;
    return 0;
}
