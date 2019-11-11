#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)

using namespace std;

int main() {
    int P, D;
    cin >> P >> D;
    int d[D+1][2];
    F0R(i, D+1) {
        F0R(j, 2) d[i][j] = 0;
    }
    int dis, a, b;
    F0R(i, P) {
        cin >> dis >> a >> b;
        d[dis][0] += a;
        d[dis][1] += b;
    }
    int wA = 0, wB = 0, v = 0, temp;
    FOR(i, 1, D) {
        temp = d[i][0] + d[i][1];
        v += temp;
        if (d[i][0] > d[i][1]) {
            wB += d[i][1];
            wA += d[i][0]-(temp/2+1);
            cout << 'A' << " " << d[i][0]-temp/2-1 << " " << d[i][1] << endl;
        } else {
            wA += d[i][0];
            wB += d[i][1]-temp/2-1;
            cout << 'B' << " " <<  d[i][0]<< " " << d[i][1]-temp/2-1 << endl;;
        }
    }
    cout.precision(10);
    cout << (double)abs(wA-wB)/v << endl;
    
    return 0;
}
