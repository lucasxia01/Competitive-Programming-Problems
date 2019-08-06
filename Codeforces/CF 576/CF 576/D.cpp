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
#include <utility>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define F0R(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n; cin >> n;
    ll a[n];
    F0R(i, n) cin >> a[i];
    ll q; cin >> q;
    ll op, id, bal;
    vector<ll> payouts;
    vector<pair<ll, pair<ll, ll> > > receipts;
    ll i = 0;
    while (q) {
        cin >> op;
        if (op == 1) {
            cin >> id >> bal;
            receipts.push_back(make_pair(i, make_pair(id-1, bal)));
        } else {
            cin >> bal;
            payouts.push_back(bal);
            i++;
        }
        q--;
    }
    ll maxMinAfter[payouts.size()+1];
    ll curMax = 0;
    if (payouts.size() > 0) ll curMax = payouts[payouts.size()-1];
    F0Rd(i, payouts.size()) {
        maxMinAfter[i] = max(curMax, payouts[i]);
        curMax = maxMinAfter[i];
        //cout << maxMinAfter[i] << endl;
    }
    maxMinAfter[payouts.size()] = 0;
    F0R(i, n) a[i] = max(a[i], maxMinAfter[0]);
    F0R(i, receipts.size()) {
        a[receipts[i].s.f] = max(receipts[i].s.s, maxMinAfter[receipts[i].f]);
        //cout << receipts[i].s.f << " " << receipts[i].s.s << " " << receipts[i].f << endl;
    }
    cout << a[0];
    FOR(i, 1, n)
        cout << " " << a[i];
    cout << endl;
    return 0;
}
