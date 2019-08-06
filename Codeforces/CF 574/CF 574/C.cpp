#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    long long row1[n];
    long long row2[n];
    for (int i = 0; i < n; i++) {
        cin >> row1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> row2[i];
    }
    for (int i = 1; i < n; i++) {
        row1[i] = max(row1[i - 1], row2[i - 1] + row1[i]);
        row2[i] = max(row2[i - 1], row1[i - 1] + row2[i]);
    }
    cout << max(row1[n - 1], row2[n - 1]) << endl;
    return 0;
}
