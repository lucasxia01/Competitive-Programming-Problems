#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define ll long long
using namespace std;

ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}
int main() {
    ll m, n;
    cin >> m >> n;
    ll g = gcd(m, n);
    ll m1 = m/g, n1 = n/g;
    if (m1 % 2 && n1 % 2) cout << g << endl;
    else cout << 0 << endl;
    return 0;
}
