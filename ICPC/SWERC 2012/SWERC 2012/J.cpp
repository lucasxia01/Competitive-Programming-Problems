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
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
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

char ops[4] = {'+', '-', '*', '/'};
int a[6], t, best;
vi best_eval;

stack<int> s;
deque<int> curOps;
void evaluate(int n) {
    if (n == -1) return;
    s.push(a[6-n]);
    F0R(i, 4) {
        stack<int> s_copy = s;
        curOps.pb(i);
        evaluate(n-1);
        F0R(i, sz(curOps)) {
            int op = curOps[i];
            int v = s.top(); s.pop();
            int w = s.top(); s.pop();
            if (op==0) s.push(w+v);
            else if (op == 1) {
                if (w<=v) break;
                s.push(w-v);
            } else if (op == 2) {
                s.push(w*v);
            } else if (op == 3) {
                if (v==0 || w%v) break;
                s.push(w/v);
            }
            if (abs(s.top()-t) < abs(best-t)) {
                best = s.top();
                best_eval = 
            }
            evaluate(n-1);
        }
        s = s_copy;
    }
}
void solve() {
    sort(a, a+6);
    do {
        stack<int> s;
        s.push(a[0]);
        evaluate(5);
    } while (next_permutation(a, a+6));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        F0R(i, 6) cin >> a[i];
        cin >> t;
        cout << "Target: " << t << nl;
        best = 0;
        solve();
        stack<int> s;
        trav(u, best_eval) {
            if (u < 0) {
                int v = s.top(); s.pop();
                int w = s.top(); s.pop();
                if (u == -4) {
                    cout << w << " + " << v << " = " << w+v << nl;
                    s.push(w+v);
                } else if (u == -3) {
                    cout << w << " - " << v << " = " << w-v << nl;
                    assert(w > v);
                    s.push(w-v);
                } else if (u == -2) {
                    cout << w << " * " << v << " = " << w*v << nl;
                    s.push(w*v);
                } else if (u == -1) {
                    cout << w << " / " << v << " = " << w/v << nl;
                    assert(w%v==0);
                    s.push(w/v);
                }
            } else s.push(u);
            if (s.top() == best) break;
        }
        cout << "Best approx: " << best << nl;
        cout << nl;
    }
    return 0;
}
