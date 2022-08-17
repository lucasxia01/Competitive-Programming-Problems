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

void print(int i, ll x) {
    cout << "Case #" << i << ": " << x << "\n";
}

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

struct nbPtrs {
    int dir[4]; // 0: l, 1: u, 2: r, 3: d
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    FOR(t, 1, T) {
        int r, c;
        cin >> r >> c;
        ll s[r][c];
        ll sum = 0;
        F0R(i, r) F0R(j, c) {
            cin >> s[i][j];
            sum += s[i][j];
        }
        nbPtrs nb[r][c]; // initial neighbors for each
        F0R(i, r) {
            F0R(j, c-1) nb[i][j].dir[2] = j+1;
            nb[i][c-1].dir[2] = -1;
            FORd(j, 1, c-1) nb[i][j].dir[0] = j-1;
            nb[i][0].dir[0] = -1;
        }
        F0R(j, c) {
            F0R(i, r-1) nb[i][j].dir[3] = i+1;
            nb[r-1][j].dir[3] = -1;
            FORd(i, 1, r-1) nb[i][j].dir[1] = i-1;
            nb[0][j].dir[1] = -1;
        }
        ll ans = 0;
        set<pi> marked;
        F0R(i, r) F0R(j, c) marked.insert(mp(i, j)); // we check everything first
        do {
            set<pi> removeNbs;
            ans += sum;
            trav(a, marked) {
                if(!s[a.f][a.s]) continue;
                ll total = 0;
                int count = 0;
                F0R(d, 4) {
                    if (nb[a.f][a.s].dir[d] != -1) {
                        if (d%2==0) total += 1LL*s[a.f][nb[a.f][a.s].dir[d]];
                        else total += 1LL*s[nb[a.f][a.s].dir[d]][a.s];
                        count++;
                    }
                }
                if (!count) continue;
                if (s[a.f][a.s]*count >= total) continue; // check to see if ok
                //cout << a.f << " " << a.s << " " << total << " " << count << endl;
                
                // insert neighbors
                removeNbs.insert(a); // add to neighbors
            }
            marked.clear();
            trav(a, removeNbs) {
                sum -= s[a.f][a.s]; // remove
                s[a.f][a.s] = 0;
                F0R(d, 4) { // updating neighbors of removed guy's neighbors
                    if (nb[a.f][a.s].dir[d] != -1) {
                        if (d%2==0) { // l, r
                            marked.insert(mp(a.f, nb[a.f][a.s].dir[d]));
                            nb[a.f][nb[a.f][a.s].dir[d]].dir[(d+2)%4] = nb[a.f][a.s].dir[(d+2)%4];
                        } else { // u, d
                            marked.insert(mp(nb[a.f][a.s].dir[d], a.s));
                            nb[nb[a.f][a.s].dir[d]][a.s].dir[(d+2)%4] = nb[a.f][a.s].dir[(d+2)%4];
                        }
                    }
                }
            }
        } while (sz(marked));
        print(t, ans);
    }
    return 0;
}
