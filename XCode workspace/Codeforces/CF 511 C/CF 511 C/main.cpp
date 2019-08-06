#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MAX 15000011
using namespace std;

int f[MAX];
bool p[MAX];

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    ll x;
    memset(p, true, sizeof(p));
    for (int i = 2; i * i <= MAX; i++) {
        if (p[i]) {
            for (int j = 2 * i; j <= MAX; j+=i) {
                p[j] = false;
            }
        }
    }
    vector<int> prime;
    prime.push_back(1);
    for (int i = 2; i < MAX; i++) if (p[i]) {prime.push_back(i);}
    rep(i, n) {
        cin >> x;
        for (int j = 0; j < prime.size() && prime[j] * prime[j] <= x; j++) {
            if (x % prime[j] == 0) {
                f[prime[j]]++;
                if (prime[j] * prime[j] != x) f[x/prime[j]]++;
            }
        }
    }
    //rep (i, 40) cout << f[i] << " ";
    int m = 0;
    for (int i = MAX - 1; i >= 0; i--) {
        if (f[i] >= n) continue;
        m = max(f[i], m);
    }
    if (m) cout << n - m << endl;
    else cout << -1 << endl;
    return 0;
}
