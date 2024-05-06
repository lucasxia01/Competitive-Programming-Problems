#include <bits/stdc++.h>

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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

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
const ll MOD = 998244353;
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

/**** Credit to chatgpt 4.0 ****/

// Stream operator for std::pair
template<typename T1, typename T2>
ostream& operator<<(ostream &out, const pair<T1, T2> &v) {
    out << "(" << v.first << ", " << v.second << ")"; 
    return out;
}

// Trait to check if a type is iterable
template<typename T, typename = void>
struct is_iterable : false_type {};

template<typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

// Stream operator for iterable types excluding std::string
template<typename TT>
typename enable_if<is_iterable<TT>::value && !is_same<TT, string>::value, ostream&>::type
operator<<(ostream& out, const TT& c) {
    out << "{ ";
    for (const auto& x : c) out << x << " ";
    out << "}"; 
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, std::stack<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.top());
        container.pop();
    }
    std::reverse(elements.begin(), elements.end()); // Reverse to maintain order
    return out << elements;
}

template<typename T>
ostream& operator<<(ostream& out, std::queue<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.front());
        container.pop();
    }
    return out << elements;
}

// Helper function to print std::priority_queue
template<typename T, typename Container, typename Compare>
ostream& operator<<(ostream& out, std::priority_queue<T, Container, Compare> pq) {
    out << "{";
    while (!pq.empty()) {
        out << " " << pq.top();
        pq.pop();
    }
    out << " }";
    return out;
}

#ifdef DBG
void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__);
#define dbg_array(a, n) cerr << #a << ": { "; for(int i = 0; i < n; i++) cerr << a[i] << " "; cerr << "}\n";
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

pair<pair<string, string>, char> p[11];
int n;

struct State {
    int gr[26][26]; // 0 is not set, 1 is equal, 2 is i > j, 3 is i < j
    int more[26];
    int less[26];
    State() {
        F0R(i, 26) F0R(j, 26) gr[i][j] = 0;
        F0R(i, 26) more[i] = -1;
        F0R(i, 26) less[i] = 10;
    }
};

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

ll ans = 0;
vi comp;
int vis[26];
void dfs(State& s, int v) {
    if (vis[v]) return;
    comp.pb(v);
    vis[v] = 1;
    F0R(i, 26) {
        if (s.gr[v][i] != 0) dfs(s, i);
    }
}
int par[26], SZ[26];
int find(int v) {
    return (v==par[v]?v:par[v] = find(par[v]));
}
void merge(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (SZ[a] < SZ[b]) swap(a, b);
    par[b] = a;
    SZ[a] += SZ[b];
}

int vis2[26];
int dfs2(vector<vi>& gr, int v, int mark) {
    if (vis2[v] == mark) return 0;
    vis2[v] = mark;
    int ret = (1<<v);
    trav(u, gr[v]) {
        ret |= dfs2(gr, u, mark);
    }
    return ret;
}

ll calc(State& s) {
    dbg("calcing ans for state");
    // F0R(i, 26) {
    //     F0R(j, 26) cerr << s.gr[i][j] << " ";
    //     cerr << nl;
    // }
    // F0R(i, 26) cerr << s.more[i] << " "; cerr << nl;
    // F0R(i, 26) cerr << s.less[i] << " "; cerr << nl;
    F0R(i, 26) vis[i] = 0;
    // now for the graph of 26
    // find each component
    ll ret = 1;
    F0R(i, 26) {
        if (vis[i] == 1) continue;
        F0R(i, 26) {
            par[i] = i;
            SZ[i] = 1;
        }
        comp.clear();
        dfs(s, i);
        // now for this component, merge things
        trav(u, comp) {
            trav(v, comp) {
                if (u == v) continue;
                if (s.gr[u][v] == 1) {
                    merge(u, v);
                }
            }
        }
        // now relabel it to be 0, 1, 2...
        vi labels(26, -1);
        int cnt = 0;
        trav(u, comp) if (find(u) == u) {
            dbg((char)(u+'A'), cnt);
            labels[u] = cnt++;
        }
        vector<vi> gr(cnt);
        trav(u, comp) {
            trav(v, comp) {
                if (find(u) == find(v) && s.gr[u][v] >= 2) return 0; 
                int a = labels[find(u)], b = labels[find(v)];
                if (s.gr[u][v] == 2) {
                    gr[a].pb(b);
                    dbg("edge", a, b);
                } else if (s.gr[u][v] == 3) {
                    gr[b].pb(a);
                    dbg("edge", b, a);
                }
            }
        }
        dbg(i, cnt);

        // find all subtree masks for each number
        int subtreeMask[cnt];
        F0R(i, 26) vis2[i] = -1;
        F0R(i, cnt) {
            subtreeMask[i] = dfs2(gr, i, i);
            dbg(i, subtreeMask[i]);
        }
        bool downwardClosed[1<<cnt]; F0R(i, (1<<cnt)) downwardClosed[i] = 0;
        F0R(i, 1<<cnt) {
            int mask = 0;
            F0R(j, cnt) if (i&(1<<j)) mask |= subtreeMask[j];
            downwardClosed[mask] = 1;
            dbg(mask);
        }

        // create validity mask for each level
        int mergedMore[cnt]; F0R(i, cnt) mergedMore[i] = -1;
        int mergedLess[cnt]; F0R(i, cnt) mergedLess[i] = 10;
        trav(v, comp) {
            ckmax(mergedMore[labels[find(v)]], s.more[v]);
            ckmin(mergedLess[labels[find(v)]], s.less[v]);
        }
        int invalidMask[10] = {};
        F0R(v, 10) {
            F0R(i, cnt) {
                if (v <= mergedMore[i] || v >= mergedLess[i]) invalidMask[v] |= (1<<i);
            }
            dbg(v, invalidMask[v]);
        }
        // find masks that don't have one be a parent of another
        int noParent[1<<cnt];
        F0R(i, 1<<cnt) {
            bool ok = 1;
            F0R(j, cnt) {
                if (i&(1<<j)) 
                    trav(k, gr[j]) if (i&(1<<k)) ok = 0;
            }
            noParent[i] = ok;
            dbg(i, noParent[i]);
        }
        int dp[10][1<<cnt]; 
        F0R(v, 10) {
            F0R(i, 1<<cnt) {
                dp[v][i] = 0;
                if (!downwardClosed[i]) continue;
                // dbg(v, i, noParent[i], (i&invalidMask[v]));
                // loop over submasks of i on previous level
                if (v > 0) {
                    for (int mask = i; mask; mask = (mask-1)&i) {
                        if (dp[v-1][mask] == 0) continue;
                        int newMask = (i^mask);
                        if (newMask&invalidMask[v]) continue;
                        if (!noParent[newMask]) continue;
                        if (!downwardClosed[mask]) continue;
                        dbg(v, i, mask, newMask, dp[v-1][mask]);
                        dp[v][i] = (dp[v][i]+dp[v-1][mask])%MOD;
                    }
                }
                // check 0 separately
                if (noParent[i] && (i&invalidMask[v]) == 0) {
                    dbg(v, i, 0, i, 1);
                    dp[v][i] = (dp[v][i]+1)%MOD;
                }
                dbg(v, i, dp[v][i]);
            }
        }
        dbg(i, dp[9][(1<<cnt)-1]);
        ret = (1LL*ret*dp[9][(1<<cnt)-1])%MOD;
    }
    dbg(ret);
    return ret;
}

void solve(int k, State s) {
    if (k == n) {
        // solve this graph
        ans = (ans+calc(s))%MOD;
        return;
    }
    string a = p[k].f.f;
    string b = p[k].f.s;
    int m = sz(a);
    dbg("solve", k, a, b);
    char op = p[k].s;
    if (op == '=') {
        State nextState = s;
        // then everything is equal
        bool ok = 1;
        F0R(i, m) {
            char x = a[i];
            char y = b[i];
            if (isDigit(x) && isDigit(y)) {
                if (x != y) {
                    ok = 0;
                    break;
                }
            } else if (isDigit(x) && !isDigit(y)) {
                // then y-'A' is equal to x
                // less than x+1, more than x-1
                ckmax(nextState.more[y-'A'], (x-'0'-1));
                ckmin(nextState.less[y-'A'], (x-'0'+1));
            } else if (!isDigit(x) && isDigit(y)) {
                // then x-'A' is equal to y
                // less than y+1, more than y-1
                ckmax(nextState.more[x-'A'], (y-'0'-1));
                ckmin(nextState.less[x-'A'], (y-'0'+1));
            } else {
                if (nextState.gr[x-'A'][y-'A'] > 1) {
                    ok = 0;
                    break;
                }
                nextState.gr[x-'A'][y-'A'] = 1;
                nextState.gr[y-'A'][x-'A'] = 1;
            }
        }
        if (!ok) return;
        solve(k+1, nextState);
        return;
    }
    if (op == '<') {
        swap(a, b);
    }
    // otherwise, we need to loop through to find the not equal stuff
    F0R(j, m) {
        // j is the one where the operator applies
        State nextState = s;
        bool ok = 1;
        F0R(i, j) {
            char x = a[i];
            char y = b[i];
            if (isDigit(x) && isDigit(y)) {
                if (x != y) {
                    ok = 0;
                    break;
                }
            } else if (isDigit(x) && !isDigit(y)) {
                // then y-'A' is equal to x
                // less than x+1, more than x-1
                ckmax(nextState.more[y-'A'], (x-'0'-1));
                ckmin(nextState.less[y-'A'], (x-'0'+1));
            } else if (!isDigit(x) && isDigit(y)) {
                // then x-'A' is equal to y
                // less than y+1, more than y-1
                ckmax(nextState.more[x-'A'], (y-'0'-1));
                ckmin(nextState.less[x-'A'], (y-'0'+1));
            } else {
                if (nextState.gr[x-'A'][y-'A'] > 1) {
                    ok = 0;
                    break;
                }
                nextState.gr[x-'A'][y-'A'] = 1;
                nextState.gr[y-'A'][x-'A'] = 1;
            }
        }
        if (!ok) continue;
        char x = a[j];
        char y = b[j];
        dbg(j, x, y);
        if (isDigit(x) && isDigit(y)) {
            if (!(x > y)) {
                ok = 0;
                continue;
            }
        } else if (isDigit(x) && !isDigit(y)) {
            ckmin(nextState.less[y-'A'], (x-'0'));
        } else if (!isDigit(x) && isDigit(y)) {
            ckmax(nextState.more[x-'A'], (y-'0'));
        } else {
            if (nextState.gr[x-'A'][y-'A'] == 1 || nextState.gr[x-'A'][y-'A'] == 3) {
                continue;
            }
            dbg("setting directed edge", x, y);
            nextState.gr[x-'A'][y-'A'] = 2; // > 
            nextState.gr[y-'A'][x-'A'] = 3; // <
        }
        solve(k+1, nextState);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    string constraints[n];
    F0R(i, n) cin >> constraints[i];
    // split by the operator
    string opset = "><=";
    F0R(i, n) {
        string left = "", right = "";
        char op;
        int j = 0;
        while (opset.find(constraints[i][j]) == -1) {
            left += constraints[i][j];
            j++;
        }
        op = constraints[i][j];
        j++;
        while (j < sz(constraints[i])) {
            right += constraints[i][j];
            j++;
        }
        // pad the smaller side with leading zeros
        if (sz(left) < sz(right)) {
            left = string(sz(right) - sz(left), '0') + left;
        } else if (sz(left) > sz(right)) {
            right = string(sz(left) - sz(right), '0') + right;
        }
        dbg(left, op, right);
        p[i] = {{left, right}, op};
    }
    // now solve all cases
    State initial;
    solve(0, initial);
    cout << ans << nl;
    return 0;
}
