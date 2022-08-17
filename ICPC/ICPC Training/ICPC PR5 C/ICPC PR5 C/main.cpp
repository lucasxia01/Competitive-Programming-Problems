#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

ll ans = 0;
vector<ll> p;
ll geoSum(ll r, ll n) {
    if (r == 1) return n;
    ll p = 1;
    ll sum = 0;
    rep(i, n + 1) {
        sum += p;
        p *= r;
    }
    //cout << r << " " << n << " " << p << " HIHIHIHI" << endl;
    return sum;
}

ll sumF(ll x) {
    map<ll, ll> m;
    for (ll i = 0; i < p.size() && p.at(i) <= x; i++) {
        //cout << p.at(i) << " HIHSO" << endl;
        if (x % p.at(i) == 0) {
            if (m.find(p.at(i)) == m.end()) m.insert(mp(p.at(i), 1));
            else m.at(p.at(i))++;
            x /= p.at(i);
            i--;
        }
    }
    ll prod = 1;
    if (x != 1) m.insert(mp(x, 1));
    for (map<ll, ll>::iterator it = m.begin(); it != m.end(); it++) {
        prod *= geoSum(it->f, it->s);
    }
    //cout << prod << endl;
    return prod;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    
    ll a, b;
    cin >> a >> b;
    //sieve
    int ar[MAX_N] = {};
    for (ll i = 2; i <= sqrt(b); i++) {
        if (!ar[i]) {
            p.pb(i);
            for (ll j = 2; i * j <= sqrt(b); j++) ar[i * j] = 1;
        }
    }
    //rep (i, p.size()) cout << p.at(i) << " ";
    
    for (ll i = a; i <= b; i++) ans += sumF(i);
    cout << ans << endl;
    return 0;
}
