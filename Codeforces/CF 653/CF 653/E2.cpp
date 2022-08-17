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
    #include <random>
    #include <chrono>
    #include <cassert>

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
    #define FOR(i,a,b) for (int i = a; i <= b; i++)
    #define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
    #define FORd(i,a,b) for (int i = (b); i >= (a); i--)
    #define trav(a, x) for (auto& a : x)

    #define f first
    #define s second
    #define mp make_pair
    #define pb push_back
    #define lb lower_bound
    #define ub upper_bound
    #define sz(x) (int)x.size()

    const char nl = '\n';
    const int MAX_N = 100011;
    const ll INF = (1LL<<50) + 123;
    const ll MOD = 1000000007; // 998244353
    const ld PI = 4*atan((ld)1);

    template <typename T> bool ckmin(T& a, const T& b) {
        return a > b ? a=b, 1 : 0;
    }
    template <typename T> bool ckmax(T& a, const T& b) {
        return b > a ? a=b, 1 : 0;
    }

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    const int MX = 1<<20;

    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(0); cout.tie(0);
        int n, m, k; cin >> n >> m >> k;
        vpi both, left, right;
        int t, a, b;
        set<pi> rest;
        F0R(i, n) {
            cin >> t >> a >> b;
            if (a&&b) both.pb({t, i});
            else if (a) left.pb({t, i});
            else if (b) right.pb({t, i});
            rest.insert({t, i});
        }
        set<pi> rCopy = rest;
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());
        sort(both.begin(), both.end());
        int sm = min(sz(left), sz(right));
        if (sz(both)+sm < k) {
            cout << -1 << nl;
            return 0;
        }
        ll bothSum = 0;
        int bothCount = 0;
        F0R(i, min(k, sz(both))) {
            bothSum += both[i].f;
            bothCount++;
            rest.erase(rest.find(both[i]));
        }
        ll ans = INF;
        ll curAns = 0;
        ll rSum = 0;
        set<pi> r;
        while (sz(r) < m-k) {
            if (sz(rest)==0) break;
            r.insert(*rest.begin());
            rSum += rest.begin()->f;
            rest.erase(rest.begin());
        }
        int bestIdx = -1;
        if (bothCount == k && sz(r) == m-k) if (ckmin(ans, bothSum+rSum)) bestIdx = k;
        F0Rd(i, k) {
            if (k-i-1 >= sm || 2*(k-i)+i > m) break;
            if (i < sz(both)) { // taking out the ith both and adding to rest
                bothSum -= both[i].f;
                rest.insert(both[i]);
                bothCount--;
            }
            curAns += left[k-i-1].f+right[k-i-1].f;
            if (rest.find(left[k-i-1]) != rest.end()) rest.erase(rest.find(left[k-i-1]));
            if (rest.find(right[k-i-1]) != rest.end()) rest.erase(rest.find(right[k-i-1]));
            if (r.find(left[k-i-1]) != r.end()) r.erase(r.find(left[k-i-1])), rSum -= left[k-i-1].f;
            if (r.find(right[k-i-1]) != r.end()) r.erase(r.find(right[k-i-1])), rSum -= right[k-i-1].f;
            while (sz(r) < m-2*(k-i)-i) {
                if (sz(rest)==0) break;
                r.insert(*rest.begin());
                rSum += rest.begin()->f;
                rest.erase(rest.begin());
            }
            while (sz(r) > m-2*(k-i)-i) {
                rest.insert(*r.rbegin());
                rSum -= r.rbegin()->f;
                r.erase(--r.end());
            }
            if (bothCount == i && bothCount+2*(k-i)+sz(r) == m)
                if (ckmin(ans, bothSum+curAns+rSum)) bestIdx = i;
        }
        if (bestIdx == -1) cout << -1 << nl;
        else {
            cout << ans << nl;
            F0R(i, bestIdx) {
                cout << both[i].s+1 << " ";
                rCopy.erase(rCopy.find(both[i]));
            }
            F0R(i, k-bestIdx) {
                cout << left[i].s+1 << " " << right[i].s+1 << " ";
                rCopy.erase(rCopy.find(left[i]));
                rCopy.erase(rCopy.find(right[i]));
            }
            int count = 0;
            trav(a, rCopy) {
                if (count+bestIdx+2*(k-bestIdx) == m) break;
                count++;
                cout << a.s+1 << " ";
            }
            cout << nl;
            assert(count+bestIdx+2*(k-bestIdx) == m);
            
        }
        return 0;
    }
