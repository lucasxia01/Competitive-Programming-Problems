#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#define ll long long

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define F0Rd(i, n) for (int i = n-1; i >= 0; i--)

using namespace std;

int main() {
    int n;
    cin >> n;
    int p[n][2];
    F0R(i, n) cin >> p[i][0] >> p[i][1];
    int shift[7] = {0, 1, 2, 3, 2, 1, 0};
    int SQRTN = sqrt(n);
    int blocks = (n-SQRTN+1)/SQRTN;
    
    int q, s, t;
    cin >> q;
    F0R(i, q) {
        cin >> s >> t;
        s--; t--;
        int best = 0, worst = 1<<30;
        int day;
        if (s < t) {
            day = ((-s)%7+7)%7;
            
        } else {
            day = s%7;
        }
        cout << best << " " << worst << endl;
    }
    return 0;
}
