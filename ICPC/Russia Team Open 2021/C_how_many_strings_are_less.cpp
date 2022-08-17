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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;


struct Node {
    Node* c[26];
    int cnt[26] = {};
    int lt[26] = {};
    int lt_chain[26] = {};
    Node* bottom[26];
    int total = 0;
    int depth = 0;
    Node* par[21];
    Node(Node* p) {
        par[0] = p;
        if (p == nullptr) depth = 0;
        else depth = p->depth+1;
    }

    void compute() {
        F0R(i, 26) if (c[i]) c[i]->compute();
        F0R(i, 26) {
            if (c[i]) cnt[i] = c[i]->total;
            else cnt[i] = 0;
            if (i > 0) lt[i] = lt[i-1] + cnt[i-1];
            else lt[i] = 0;
            
            if (c[i]) lt_chain[i] = c[i]->lt_chain[i] + lt[i];
            else lt_chain[i] = lt[i];

            if (c[i]) bottom[i] = c[i]->bottom[i];
            else bottom[i] = this;
        }
    }
    Node* get_parent(int x) {
        Node* cur = this;
        F0R(i, 21) {
            if (x&(1<<i)) {
                cur = cur->par[i];
                if (cur == nullptr) break;
            }
        }
        return cur;
    }
};

vector<Node*> nodes;
void make_list(Node* cur) {
    F0R(i, 26) if (cur->c[i])
        make_list(cur->c[i]);
    nodes.pb(cur);
}

void add_string(Node root, string s) {
    dbg(s);
    Node* cur = &root;
    F0R(i, sz(s)) {
        dbg(i, s[i]-'a');
        if (cur->c[s[i]-'a'] == nullptr) {
            cur->c[s[i]-'a'] = new Node(cur);
        }
        cur->total++;
        cur = cur->c[s[i]-'a'];
    }
    cur->total++;
}

void init(Node root) {
    // set all the values we want
    root.compute();
    // set the ancestry
    make_list(&root);
    FOR(i, 1, 20) {
        trav(node, nodes) {
            if (node->par[i-1] == nullptr) node->par[i] = nullptr;
            else node->par[i] = node->par[i-1]->par[i-1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    Node root(nullptr);
    string s; cin >> s;
    string t;
    F0R(i, n) {
        cin >> t;
        add_string(root, t);
    }
    // init(root);

    // Node cur = root;
    // int ans = 0;
    // F0R(i, sz(s)) {
    //     if (cur.c[s[i]-'a']) {
    //         ans += cur.lt[s[i]-'a'];
    //         cur = cur.c[s[i]-'a'];
    //     } else break;
    // }
    // cout << ans << nl;
    stack<pair<int, char>> st;
    while (q--) {
        int k; char c; cin >> k >> c; k--;
        // while (!st.empty() && st.top().f >= k) {
        //     if (cur.depth >= st.top().s) {
        //         ans += cur.lt_chain[st.top().f-'a'];
        //         cur = *cur.get_parent(cur.depth-st.top().s);
        //         ans -= cur.lt_chain[st.top().f-'a'];
        //     }
        //     st.pop();
        // }
        // if (!st.empty() && cur.depth >= k) {
        //     ans += cur.lt_chain[st.top().f-'a'];
        //     cur = *cur.get_parent(cur.depth-k);
        //     ans -= cur.lt_chain[st.top().f-'a'];
        // } else {
             
        // }
        // st.push({k, c});
        // if (cur.depth == k) {
        //     ans += cur.lt_chain[c-'a'];
        // }
    }
    return 0;
}
