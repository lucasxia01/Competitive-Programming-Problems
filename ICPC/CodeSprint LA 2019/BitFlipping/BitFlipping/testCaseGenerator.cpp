#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>
using namespace std;

ofstream fout;

int main() {
    time_t srand(105909109);
    fout.open("bitFlipping.out");
    int T, n, k, ans = 0, a, b;
    cin >> T;
    fout << T << endl;
    cout << T << endl;
    for (int i = 0; i < T; i++) {
        n = rand() % 100000;
        k = rand() % 10000;
        ans = 0;
        cout << n << " " << k << endl;
        for (int j = 0; j < k; j++) {
            a = rand() % 100000;
            b = a + (rand() % (100000 - a));
            cout << a << " " << b << endl;
        }
    }
    fout.close();
    return 0;
}
