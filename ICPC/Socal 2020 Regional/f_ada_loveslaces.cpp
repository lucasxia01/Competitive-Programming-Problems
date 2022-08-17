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
#include <climits>

using namespace std;

typedef long long ll;

#define FOR(i,a,b) for(int i = a; i < b; i++)
#define ROF(i,a,b) for(int i = b-1; i >= a; i--)

// overloaded << operator for printing vectors. Idea from Neal Wu
template<typename T> ostream& operator<< (ostream& os, vector<T> v) {
    os << '['; string sep; for (const T& el : v) os << sep << el, sep = ", "; return os << ']';
}
// overloaded << operator for printing pairs
template<typename S, typename T> ostream& operator<< (ostream& os, pair<S,T> p) {
    return os << '(' << p.first << "," << p.second << ")";
} 
// cool recursive template for debug printing. also Neal Wu
void dbg_out () {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
    cerr << ' ' << H; dbg_out(T...);
}

#ifdef JACOB_DEBUG
#define dbg(desc, ...) cerr << '(' << desc << "):"; dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

// KACTL defines
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
void run () {
    int N;
    double d_vert, s_hori, t_eyelet;
    double fmin, fmax;
    cin >> N >> d_vert >> s_hori >> t_eyelet >> fmin >> fmax;
    double L;

    vector<double> dists(N);
    FOR(i,0,N+1) dists[i] = sqrt(s_hori*s_hori + i*i*d_vert*d_vert);
    double skip_val = dists[1] - d_vert;
    vector<double> lengths;
    {
        FOR(mask, 0, 1 << (N-2)) {

            vector<int> rows;
            FOR(i,0,N-2) if (mask & (1 << i)) rows.push_back(i+1);
            int m = rows.size();
            double init_len = (2*m+4)*t_eyelet + s_hori;
            // special case: no intermediate rows
            if (m == 0) {
                if (N == 2) {
                    lengths.push_back(2*d_vert + init_len);
                }
                lengths.push_back(2*dists[N-1] + init_len);
                continue;
            } 
            do {
                double base_len = init_len;
                int num_skips = 0;
                
                base_len += 2*dists[rows[0]];
                num_skips += (rows[0] == 1);
                base_len += 2*dists[(N-1)-rows[m-1]];
                num_skips += (rows[m-1] == (N-2));

                FOR(i,1,m) {
                    base_len += 2*dists[abs(rows[i]-rows[i-1])];
                    num_skips += (abs(rows[i]-rows[i-1])==1);
                }
                //
                FOR(msk2,0,1<<num_skips) {
                    int s = __builtin_popcount(msk2);
                    lengths.push_back(base_len - 2*s*skip_val);
                }
            } while (next_permutation(all(rows)));
        }
    } 
    sort(lengths.begin(), lengths.end());
    cout << "lengths.size() " << lengths.size() << endl;
    while (cin >> L) {
        dbg("L",L);
        double Lmin = L - 2*fmax;
        double Lmax = L - 2*fmin;
        dbg("Lmin,Lmax",Lmin,Lmax);
        int ans = lower_bound(all(lengths), Lmax) - lower_bound(all(lengths), Lmin);
        dbg("hello");
        cout << ans << '\n';
    }
    dbg("what");
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    run();
    dbg("hi?");
}
