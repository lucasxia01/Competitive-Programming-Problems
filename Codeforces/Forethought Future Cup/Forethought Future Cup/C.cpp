#include <iostream>
using namespace std;

void assign(int * a, int size, int depth) {
    for (int i = 0; i < size/2; i++) {
        a[i] = 1;
    }
    for (int i = size/2; i < size; i++) {
        a[i] = 0;
    }
    if (depth == 0) return;
    assign(a, size/2, depth - 1);
    assign(a + size/2, size - size/2, depth - 1);
}
int main() {
    int t, n, best, x;
    cin >> t;
    int a[103] = {};
    for (int T = 0; T < t; T++) {
        cin >> n;
        best = 0;
        for (int guess = 0; guess < 9; guess++) {
            for (int j = 0; j < 103; j++) a[j] = 0;
            assign(a, n, guess);
            int count1 = 0;
            for (int i = 0; i < n; i++) {
                if (a[i] == 1) count1++;
            }
            if (count1 == 0) break;
            cout << count1 << " " << n - count1;
            for (int i = 0; i < n; i++) {
                if (a[i] == 1) cout <<  " " << i + 1;
            }
            for (int i = 0; i < n; i++) {
                if (a[i] == 0) cout <<  " " << i + 1;
            }
            cout << endl; cout.flush();
//            for (int i = 0; i < n; i++) {
//                cout << a[i] << " ";
//            }
            cin >> x;
            if (x > best) best = x;
        }
        cout << -1 << " " << best << endl;
        cout.flush();
    }
}
