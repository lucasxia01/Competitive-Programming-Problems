#include <bits/stdc++.h>
using namespace std;

const int MX = 1e7+5;
bool noprime[MX];
int last[MX];
int main() {
    int n; cin >> n;
    // factor every number
    vector<int> primes;
    for (int i = 2; i < MX; i++) {
        if (noprime[i]) continue;
        for (int j = i+i; j < MX; j+=i) {
            noprime[j] = true;
        }
        primes.push_back(i);
    }
    // factorize each number
    vector<int> facs[n];
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        // cerr << a[i] << endl;
        for (int p : primes) {
            if (p*p > a[i]) break;
            if (a[i]%p == 0) facs[i].push_back(p);
            while (a[i]%p == 0) a[i]/=p;
        }
        if (a[i] > 1) facs[i].push_back(a[i]);
        // for (int f : facs[i]) {
        //     cerr << f << " ";
        // } cerr << endl;
    }
    // left and right ptrs
    for (int p : primes)
        last[p] = -1;
    int l[n], r[n];
    for (int i = 0; i < n; i++) {
        int cur = -1;
        for (int f : facs[i]) {
            cur = max(cur, last[f]);
            last[f] = i;
        }
        l[i] = cur;
    }
    for (int p : primes)
        last[p] = n;

    for (int i = n-1; i >= 0; i--) {
        int cur = n;
        for (int f : facs[i]) {
            cur = min(cur, last[f]);
            last[f] = i;
        }
        r[i] = cur;
    }
    
    function<bool(int, int, int)> split;

    int ans[n];
    split = [&] (int root, int L, int R) {
        if (L > R) return true;
        // now split action
        for (int i = L, j = R; i <= j; i++, j--) {
            // try out i then j
            if (l[i] < L && r[i] > R) {
                ans[i] = root+1;
                return (split(i, L, i-1) && split(i, i+1, R));
            }

            if (l[j] < L && r[j] > R) {
                ans[j] = root+1;
                return (split(j, L, j-1) && split(j, j+1, R));
            }
        }
        return false;
    };
    if (split(-1, 0, n-1)) {
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    } else cout << "impossible" << endl;

}