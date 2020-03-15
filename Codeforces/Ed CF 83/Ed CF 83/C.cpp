#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;
 
int main() {
    int t, n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        long long a[n];
        bool good = true;
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int e = 0; e < 60; e++) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += a[i]%k;
                a[i] /= k;
            }
            if (sum > 1) {
                good = false;
                break;
            }
        }
        if (good) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
