#include "testlib.h"
#include <iostream>

using namespace std;

const int INF = (1<<29)+123;
const int MOD = 24*60;
const int MX = MOD+5;

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    registerGen(argc, argv, 1);
    // if arg1 is 0, small random values
    // if arg1 is 1, large random values
    // if arg1 is 2, small ordered values
    // if arg1 is 3, large ordered values
    int type = atoi(argv[1]);
    int bound = MOD-1;
    int n = atoi(argv[2]);
    cout << n << '\n';
    vector<int> arr;
    if (type == 0 || type == 2) bound = 30;
    if (type < 2) {
        
        for (int i = 0; i < n; i++) {
            arr.push_back(rnd.next(0, bound));
        }
    } else if (type == 2 || type == 3) {
        int snoozePeriods[3] = {rnd.next(1, 30), rnd.next(31, MOD/10), rnd.next(MOD/10+1, MOD-1)};
        int periodType = rnd.next(0, 2);
        int count = 0;
        for (int i = 0; i < n; i++) {
            int cur = rnd.next(1, bound);
            int end = rnd.next(cur, bound);
            while (count < n && cur <= end) {
                arr.push_back(cur);
                cur += snoozePeriods[periodType];
                count++;
            }
        }
    }
    for (int i = 0; i < n-1; i++) cout << arr[i] << ' ';
    cout << arr[n-1] << '\n';
    return 0;
}
