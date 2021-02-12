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

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    FOR(tt, 1, t) {
        ll n, w, k; cin >> n >> k >> w;
        ll l[n], h[n];
        F0R(i, k) cin >> l[i];
        ll al, bl, cl, dl; cin >> al >> bl >> cl >> dl;
        F0R(i, k) cin >> h[i];
        ll ah, bh, ch, dh; cin >> ah >> bh >> ch >> dh;
        ll pL=-INF, pH = 0;
        ll curP = 0;
        ll curAns = 1;
        F0R(i, n) {
            ll L, H;
            if (i < k) L=l[i], H=h[i];
            else {
                L=(al*l[i-2]+bl*l[i-1]+cl)%dl;
                H=(ah*h[i-2]+bh*h[i-1]+ch)%dh;
            }
            l[i]=L, h[i]=H;
            curP = (curP+2*min(L-pL, w))%MOD;
            if (pL+w >= L) curP = (curP+2*max(0LL, H-pH))%MOD;
            else curP += 2*H;
            pL=L,pH=H;
            curAns = (curAns*curP)%MOD;
        }
        cout << "Case #" << tt << ": " << curAns << nl;
    }
    return 0;
}
