#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#define ll long long
#define INF 10000000
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)

using namespace std;

int main() {
    string s;
    cin >> s;
    int next[26][s.length()+1];
    F0R(i, 26) next[i][s.length()-1] = INF;
    for (int i = (int)s.length()-2; i >= 0; i--) {
        F0R(j, 26) {
            if (j == s[i+1]-'a') next[j][i] = i+1;
            else next[j][i] = next[j][i+1];
        }
    }
    ll ans = 0;
    F0R(i, s.length()) {
        F0R(j, 26) {
            if (next[j][i] < next[s[i]-'a'][i]) {
                ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
