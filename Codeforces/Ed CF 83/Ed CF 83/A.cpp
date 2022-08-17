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
    int t, n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        if (n % m) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}
