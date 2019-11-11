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
#define FORd(i, a, b) for (int i = b; i >= a; i--)

using namespace std;

int main() {
    int n;
    cin >> n;
    int p[n][2];
    F0R(i, n) cin >> p[i][0] >> p[i][1];
    int shift[7] = {0, 1, 2, 3, 2, 1, 0};
    int SZ = sqrt(n);
    int c[7][2][n];
    F0R(day, 7) {
        int d = day;
        //cout << "start day " << day << endl;
        F0R(i, n) {
            c[day][0][i] = p[i][0] + shift[d]*p[i][1];
            
            d = (d+1)%7;
        }
        d = day;
        F0R(i, n) {
            c[day][1][i] = p[i][0] + shift[d]*p[i][1];
            //cout << c[day][1][i] << " ";
            d = (d+6)%7;
        }
        //cout << endl;

    }
    int sqrtdcmp[7][2][SZ+1][3];
    F0R(day, 7) {
        int high = 0, low = 1<<30, profit = 0;
        //cout << "start day " << day << endl;
        F0R(i, SZ) {
            high = 0; low = 1<<30; profit = 0;
            FOR(j, i*SZ, (i+1)*SZ-1) {
                high = max(high, c[day][0][j]);
                low = min(low, c[day][0][j]);
                profit = max(profit, c[day][0][j]-low);
            }
            sqrtdcmp[day][0][i][0] = high;
            sqrtdcmp[day][0][i][1] = low;
            sqrtdcmp[day][0][i][2] = profit;
            
        }
        F0R(i, SZ) {
            high = 0; low = 1<<30; profit = 0;
            FORd(j, i*SZ, (i+1)*SZ-1) {
                high = max(high, c[day][1][j]);
                low = min(low, c[day][1][j]);
                profit = max(profit, c[day][1][j]-low);
            }
            sqrtdcmp[day][1][i][0] = high;
            sqrtdcmp[day][1][i][1] = low;
            sqrtdcmp[day][1][i][2] = profit;
//            cout << "range " << (i+1)*SZ-1 << " to " << i*SZ << endl;
//            printf("hi: %d, lo: %d, prof: %d\n", high, low, profit);
        }
    }
    int q, s, t;
    cin >> q;
    F0R(i, q) {
        cin >> s >> t;
        s--; t--;
        //cout << s << " " << t << endl;
        int day;
        int ans = 0;
        if (s < t) {
            day = ((-s)%7+7)%7;
            //cout << "day of 0: " << day << endl;
            int m = s;
            int low = 1<<30;
            while (m%SZ!=0 && m <= t) {
                low = min(low, c[day][0][m]);
                ans = max(ans, c[day][0][m]-low);
                //cout << m << " " << c[day][0][m] << endl;
                m++;
            }
            //cout << "after first " << m << endl;
            while (m+SZ <= t) {
                ans = max(ans, sqrtdcmp[day][0][m/SZ][0]-low);
                low = min(low, sqrtdcmp[day][0][m/SZ][1]);
                ans = max(ans, sqrtdcmp[day][0][m/SZ][2]);
                m += SZ;
            }
            //cout << "after sqrt blocks " << m << endl;
            while (m <= t) {
                low = min(low, c[day][0][m]);
                ans = max(ans, c[day][0][m]-low);
                //cout << m << " " << c[day][0][m] << endl;
                m++;
            }
        } else {
            day = s%7;
            //cout << "day of 0: " << day << endl;
            int m = s;
            int low = 1<<30;
            while ((m+1)%SZ!=0 &&m >= t) { //
                low = min(low, c[day][1][m]);
                ans = max(ans, c[day][1][m]-low);
                //cout << m << " " << c[day][1][m] << endl;
                m--;
            }
            //cout << "after first " << m << endl;
            while (m+1-SZ >= t) {
                ans = max(ans, sqrtdcmp[day][1][m/SZ][0]-low);
                low = min(low, sqrtdcmp[day][1][m/SZ][1]);
                ans = max(ans, sqrtdcmp[day][1][m/SZ][2]);
                m -= SZ;
            }
            //cout << "after sqrt blocks " << m << endl;
            while (m >= t) {
                low = min(low, c[day][1][m]);
                ans = max(ans, c[day][1][m]-low);
                //cout << m << " " << c[day][1][m] << endl;
                m--;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
