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

const int MX = 2e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("ranking.in", "r", stdin);
//    freopen("ranking.out", "w", stdout);
    int n; cin >> n;
    pair<ld, string> score[n];
    string str;
    getline(cin, str);
    int maxLen = 0;
    F0R(i, n) {
        getline(cin, str);
        score[i] = {0, str};
        ckmax(maxLen, (int)str.length());
    }
    int m; cin >> m;
    int count[n]; F0R(i, n) count[i] = 0;
    while (m--) {
        int k; cin >> k;
        int partic[n]; F0R(i, n) partic[i] = 0;
        int x;
        F0R(i, k) {
            cin >> x; x--;
            partic[x] = 1;
            count[x]++;
        }
        int pn; cin >> pn;
        int rn; cin >> rn;
        int solved[n][pn], pen[n][pn];
        F0R(i, n) F0R(j, pn) solved[i][j] = pen[i][j] = 0;
        while (rn--) {
            int t; char p; int time; char ac;
            cin >> t >> p >> time >> ac;
            t--;
            int pr = p-'A';
            if (solved[t][pr]) continue;
            if (ac == '+') {
                solved[t][pr] = 1;
                pen[t][pr] += time;
            } else pen[t][pr] += 20;
        }
        vector<pair<pi, int> > sc;
        int pm = 0;
        F0R(i, n) {
            if (!partic[i]) continue;
            int solveCount = 0, penTotal = 0;
            F0R(j, pn) {
                if (!solved[i][j]) continue;
                solveCount += solved[i][j];
                penTotal += pen[i][j];
            }
            ckmax(pm, solveCount);
            sc.pb({{-solveCount, penTotal}, i});
        }
        if (pm == 0) continue;
        sort(sc.begin(), sc.end());
        int rank = 0;
        F0R(i, k) {
            if (!i || sc[i-1].f != sc[i].f) rank = i+1;
//            cout << sc[i].s+1 << " " << rank << " " << (ld) -sc[i].f.f/pm*(2*k-2)/(k-2+rank) << nl;
            score[sc[i].s].f += (ld) -sc[i].f.f/pm*(2*k-2)/(k-2+rank);
        }
    }
    F0R(i, n) if (count[i]) score[i].f /= count[i]; else score[i].f = 0;
    sort(score, score+n, greater<pair<ld, string> >());
    cout.precision(4);
    F0R(i, n) {
        cout << score[i].s;
        F0R(j, maxLen+1-score[i].s.length()) cout << " ";
        cout << fixed << score[i].f << nl;
    }
    return 0;
}
