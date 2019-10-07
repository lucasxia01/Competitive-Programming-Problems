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
    F0R(i, n) {
        cin >> p[i][0] >> p[i][1];
    }
    int ST[2][2][7][2*n];
    int shift[7] = {0, 1, 2, 3, 2, 1, 0};
    F0R(i, 7) {
        F0R(dir, 2) {
            F0R(k, 2)
                F0R(j, n) {
                    ST[dir][k][i][j+n] = p[j][0] + shift[((i+(2*dir-1)*j)%7+7)%7]*p[j][1];
                }
            F0Rd(j, n) {
                ST[dir][0][i][j] = max(ST[dir][0][i][2*j], ST[dir][0][i][2*j+1]);
                    ST[dir][1][i][j] = min(ST[dir][1][i][2*j], ST[dir][1][i][2*j+1]);
            }
        }
    }
    int q, s, t;
    cin >> q;
    F0R(i, q) {
        cin >> s >> t;
        s--; t--;
        int best = 0, worst = 1<<30;
        int day;
        if (s < t) {
            day = ((-s)%7+7)%7;
            cout << day << endl;
            int l = s, r = t+1;
            for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
                if (l&1) best = max(best, ST[1][0][day][l--]);
                if (r&1) best = max(best, ST[1][0][day][--r]);
            }
            l = s; r = t+1;
            for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
                if (l&1) worst = min(worst, ST[1][1][day][l--]);
                if (r&1) worst = min(worst, ST[1][1][day][--r]);
            }
        } else {
            day = s%7;
            cout << day << endl;
            int l = t, r = s+1;
            for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
                if (l&1) best = max(best, ST[0][0][day][l--]);
                if (r&1) best = max(best, ST[0][0][day][--r]);
            }
            l = t; r = s+1;
            for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
                if (l&1) worst = min(worst, ST[0][1][day][l--]);
                if (r&1) worst = min(worst, ST[0][1][day][--r]);
            }
        }
        cout << best << " " << worst << endl;
    }
    return 0;
}
