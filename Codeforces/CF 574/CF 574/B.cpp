#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, k;
    cin >> n >> k;
    double a = 8*(n + k) + 9;
    vector<long long> squares;
    for (long long i = 0; i < 1<<20; i++) {
        squares.push_back(i*i);
    }
    int i;
    for (i = 0; i < 1<<20; i++) {
        if (squares[i] == a) break;
    }
    if (i < 1<<20) {
        cout << n + (3 - i)/2 << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}
