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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int m = n;
    vi LOC[n+1];
    int A[n];
    F0R(i, n) {
        cin >> A[i];
        LOC[A[i]].pb(i);
    }
    int hi = 0, best = -1;
    FOR(i, 1, m) if (ckmax(hi, sz(LOC[i]))) best = i;
    bool done = 0;
    FOR(i, 1, m) if (i != best && hi == sz(LOC[i])) done = 1;
    if (done) {
        cout << n << nl;
        return 0;
    }
    n+=2;
    int a[n]; F0R(i, n-2) a[i+1] = A[i];
    a[0] = a[n-1] = best;
    vi loc[n+1];
    F0R(i, n) loc[a[i]].pb(i);
    hi = sz(loc[best]);
    int idxBest[n];
    F0R(i, n) if (i == 0) idxBest[i] = 1; else idxBest[i] = idxBest[i-1]+(a[i]==best);
    int ans = 0;
    int SQRTN = sqrt(n)-300;
    FOR(i, 1, m) {
        int SZ = sz(loc[i]);
        if (i == best || !SZ) continue;
        if (SZ > SQRTN) {
            int j = 0, k = 0;
            int sum = 0;
            int firstLoc[2*n+1]; F0R(ii, 2*n+1) firstLoc[ii] = -1;
            firstLoc[sum+n] = 0;
            while (j != hi-1 || k != SZ) {
                int curPos;
                if (k < SZ && loc[best][j] > loc[i][k]) {
                    curPos = loc[i][k]+1;
                    ckmax(ans, curPos-1-firstLoc[sum+n]);
                    sum++;
                    k++;
                } else {
                    curPos = loc[best][j]+1;
                    ckmax(ans, curPos-1-firstLoc[sum+n]);
                    sum--;
                    j++;
                }
                if (firstLoc[sum+n] == -1) firstLoc[sum+n] = curPos;
            }
            ckmax(ans, loc[best][j]-firstLoc[sum+n]);
        } else {
            int kkk = 0;
            F0R(kk, SZ) {
                int j = max(0, idxBest[loc[i][kk]]-SZ-2);
                int jEnd = min(hi, idxBest[loc[i][kk]]+SZ+2);
                while (kkk < SZ && loc[best][j] > loc[i][kkk]) kkk++;
                int k = kkk;
                int PAD = 2*SZ+5;
                int firstLoc[2*PAD+1]; F0R(ii, 2*PAD+1) firstLoc[ii] = -1;
                int sum = -1;
//                dbg_out(i, loc[i][kk], j, jEnd, loc[best][j], sum);
                if (j == 0) firstLoc[0+PAD] = 0;
                firstLoc[sum+PAD] = loc[best][j]+1;
                j++;
                while (j < jEnd) {
                    int curPos;
                    if (k < SZ && loc[i][k] < loc[best][j]) {
                        curPos = loc[i][k]+1;
                        ckmax(ans, loc[i][k]-firstLoc[sum+PAD]);
                        sum++;
                        k++;
                    } else {
                        curPos = loc[best][j]+1;
                        ckmax(ans, loc[best][j]-firstLoc[sum+PAD]);
                        sum--;
                        j++;
                    }
//                    dbg_out("sum of ", sum, " at ", curPos-1);
                    if (firstLoc[sum+PAD] == -1) firstLoc[sum+PAD] = curPos;
                }
//                dbg_out(j, sum);
                if (j != hi) ckmax(ans, loc[best][j]-firstLoc[sum+PAD]);
            }
        }
    }
    cout << ans << nl;
    return 0;
}
