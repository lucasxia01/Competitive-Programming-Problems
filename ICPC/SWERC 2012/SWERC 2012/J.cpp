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
struct oper{
    int a, b, v;
    char op;
};

struct State {
    vi cur;
    int a, b; char op;
    vector<oper> hist;
};

char ops[4] = {'+', '-', '*', '/'};
int a[6], t;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        F0R(i, 6) cin >> a[i];
        cin >> t;
        cout << "Target: " << t << nl;
        queue<State> q;
        int best = INF;
        State bestState;
        State temp;
        F0R(i, 6) {
            temp.cur.pb(a[i]);
            if (abs(a[i]-t) < abs(best-t)) best = a[i];
        }
        q.push(temp);
        while (!q.empty()) {
            State s = q.front(); q.pop();
//            trav(u, s.cur) cout << u << ' '; cout << nl;
            F0R(o, 4) {
                F0R(i, sz(s.cur)) {
                    bool ok = 1;
                    F0R(j, sz(s.cur)) {
                        if (i == j) continue;
                        if ((o == 0 || o == 2) && j >= i) continue;
                        State st;
                        st.a = s.cur[i]; st.b = s.cur[j];
                        st.op = ops[o];
                        oper move; move.a = st.a; move.b = st.b; move.op = ops[o];
                        if (o == 0) {
                            move.v = st.a+st.b;
                        } else if (o == 1) {
                            if (st.a <= st.b) continue;
                            move.v = st.a-st.b;
                        } else if (o == 2) {
                            if (1LL*st.a*st.b >= MX) continue;
                            move.v = st.a*st.b;
                        } else {
                            if (st.a%st.b) continue;
                            move.v = st.a/st.b;
                        }
                        if (move.v >= MX) continue;
                        F0R(k, sz(s.cur)) if (k != i && k != j) st.cur.pb(s.cur[k]);
                        st.cur.pb(move.v);
                        st.hist.pb(move);
                        trav(m, s.hist) st.hist.pb(m);
                        if (abs(move.v-t) < abs(best-t)) {
                            best = move.v;
                            bestState = st;
                        }
                        if (sz(st.cur) == 1) continue;
                        q.push(st);
                    }
                    if (!ok) break;
                }
            }
        }
        reverse(bestState.hist.begin(), bestState.hist.end());
        trav(m, bestState.hist) {
            cout << m.a << " " << m.op << " " << m.b << " = " << m.v << nl;
        }
        cout << "Best approx: " << best << nl;
        cout << nl;
    }
    return 0;
}
