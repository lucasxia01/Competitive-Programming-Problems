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

const int MX = 1e5+5;
map<int, set<int> > C[3]; // maps from rgb value to set of ids
map<int, int> score; // maps from id to score
set<pi> pq; // pair of score with id

struct State {
    int c[3], id;
};
map<int, State> ids; // maps from ids to angles

int nxt(int j, int v) {
    auto it = C[j].find(v);
    assert(it != C[j].end());
    it++;
    if (it == C[j].end()) {
        it = C[j].begin();
    }
    return it->f;
}

int prv(int j, int v) {
    auto it = C[j].find(v);
    assert(it != C[j].end());
    if (it == C[j].begin()) {
        it = C[j].end();
    }
    it--;
    return it->f;
}

int calc(int id) {
    int ans = 0;
    F0R(j, 3) {
        int a = ids[id].c[j];
        if (sz(C[j][a]) > 1) continue;
        int na = nxt(j, a);
        int pa = prv(j, a);
        if (na == pa) ans += 360;
        else ans += (na - pa + 360) % 360;
    }
    return ans;
}

void resolve(int id) {
    F0R(j, 3) {
//        dbg("Removing", id, j);
        // remove
        int a = ids[id].c[j]; // angle
        if (sz(C[j][a]) > 2) {
            C[j][a].erase(C[j][a].find(id));
            continue;
        }
        int na = nxt(j, a);
        int pa = prv(j, a);
        if (sz(C[j][a]) == 2) {
            C[j][a].erase(C[j][a].find(id));
            int neighborID = *C[j][a].begin();
            int oldScore = score[neighborID];
            pq.erase(pq.find({oldScore, -neighborID}));
            int newScore = calc(neighborID);
            pq.insert({newScore, -neighborID});
//            dbg("Updating", neighborID,"to", newScore);
            score[neighborID] = newScore;
        } else {
            C[j].erase(C[j].find(a));
            if (sz(C[j][na]) == 1) {
                int neighborID = *C[j][na].begin();
                int oldScore = score[neighborID];
                pq.erase(pq.find({oldScore, -neighborID}));
                
                int newScore = calc(neighborID);
                pq.insert({newScore, -neighborID});
//                dbg("Updating", neighborID,"to", newScore);
                score[neighborID] = newScore;
            }
            if (sz(C[j][pa]) == 1) {
                int neighborID = *C[j][pa].begin();
                int oldScore = score[neighborID];
                pq.erase(pq.find({oldScore, -neighborID}));
                
                int newScore = calc(neighborID);
                pq.insert({newScore, -neighborID});
//                dbg("Updating", neighborID,"to", newScore);
                score[neighborID] = newScore;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int c[3], id;
    F0R(i, n) {
        cin >> c[0] >> c[1] >> c[2] >> id;
        State s; F0R(j, 3) s.c[j] = c[j]; s.id = id;
        ids[id] = s;
        F0R(j, 3) {
            if (C[j].find(c[j]) == C[j].end()) {
                set<int> temp = {id};
                C[j][c[j]] = temp;
            } else C[j][c[j]].insert(id);
        }
    }
    
    // precalculate uniqueness
    trav(card, ids) {
        int id = card.f;
        score[id] = calc(id);
//        dbg(id, score[id]);
        pq.insert({score[id], -id});
    }
    F0R(i, n) {
        auto it = pq.begin();
        cout << -it->s << nl;
        resolve(-it->s);
        pq.erase(pq.begin());
    }
    return 0;
}
