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

#define nl endl
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
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
int dp[100][100]; // 

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    // precalc the answers before
    dp[0][1] = dp[1][0] = 0;
    F0R(i, 100) {
        F0R(j, 100) {
            if (i+j <= 1) {
                continue;
            }
            dp[i][j] = 100; // set to infty
            F0R(ii, i+1) {
                F0R(jj, j+1) {
                    if (ii == 0 && jj == 0) continue;
                    if (i-ii == 0 && j-jj == 0) continue;
                    ckmin(dp[i][j], max(dp[ii][jj], dp[i-ii][j-jj]) + 2);
                }
            }
        }
    }

    int n, m, t; cin >> n >> m >> t;
    // just try placing your start anywhere
    bool START = 0;
    int x, y;
    F0R(i, n) F0R(j, m) {
        bool win = 1;
        F0R(ii, n) F0R(jj, m) {
            if (ii == i && jj == j) continue;
            if (dp[abs(ii-i)][abs(jj-j)] > 14) win = 0;
        }
        if (win) {
            START = 1;
            x = i+1, y = j+1;
            break;
        }
    }
    // solve d
    while (t--) {

        // TODO some things seem winnable but they aren't actually because of the border...
        // not a problem if its 3x3 or bigger
        if ((n == 1 && m == 2) || n == 2) {
            START = 1; // we want to go second
            // our standard strategy won't work for just this case...
            if (m == 2) {
                // do whatever lol
                cout << 2 << nl; cout.flush();
                while (1) {
                    int r, c; cin >> r >> c;
                    char res; cin >> res;
                    if (res == 'L') assert(0);
                    else if (res == 'W') break;

                    // look for something that's not r, c
                    FOR(i, 1, n) FOR(j, 1, m) {
                        if (i == r && j == c) continue;
                        x = i, y = j;
                        break;
                    }
                    cout << x << " " << y << nl; cout.flush();
                    cin >> res;
                    if (res == 'I') assert(0);
                    else if (res == 'L') assert(0);
                    else if (res == 'W') break;
                }
            } else { // 2, 3+ case is just make sure the two things are in separate rows
                cout << 2 << nl; cout.flush();
                array<pi, 2> v;
                bool first = 1;
                while (1) {
                    int r, c; cin >> r >> c;
                    char res; cin >> res;
                    if (res == 'L') assert(0);
                    else if (res == 'W') break;
                    x = -1, y = -1;
                    if (first) {
                        // look for something that's not in same row r, c
                        FOR(i, 1, n) FOR(j, 1, m) {
                            if (i == r) continue;
                            x = i, y = j;
                            break;
                        }
                        first = 0;
                        v[0] = {r, c};
                        v[1] = {x, y};
                    } else {
                        // delete the thing in the same row as r, c
                        F0R(i, 2) {
                            if (r == v[i].f) {
                                x = v[i].f; y = v[i].s;
                                v[i] = {x, y};
                                break;
                            }
                        }
                    }
                    cout << x << " " << y << nl; cout.flush();
                    cin >> res;
                    if (res == 'I') assert(0);
                    else if (res == 'L') assert(0);
                    else if (res == 'W') break;
                }
            }

            continue;
        }
        bool on[n+1][m+1]; F0R(i, n+1) F0R(j, m+1) on[i][j] = 0;
        if (START) {
            cout << 1 << nl; cout.flush();
            int left = 14;
            array<pi, 2> v; v[0] = v[1] = {-12451, -12451};
            while (1) {
                // first check if its already on lol
                if (on[x][y]) {
                    // then pick either one of v to replace
                    v[0] = {x, y};
                } else {
                    cout << x << " " << y << nl; cout.flush();
                    on[x][y] = !on[x][y];
                    char res; cin >> res;
                    if (res == 'I') assert(0);
                    else if (res == 'L') assert(0);
                    else if (res == 'W') break;
                    int r, c; cin >> r >> c;
                    on[r][c] = !on[r][c];
                    // this might've turned off one the v
                    if (v[1].f == -12451) {
                        v[0] = {x, y};
                        v[1] = {r, c};
                    } else {
                        bool replaced = 0;
                        F0R(i, 2) {
                            if ((r == v[i].f && c == v[i].s)) {
                                v[i] = {x, y}; // replace it with x, y :)
                                replaced = 1;
                                break;
                            }
                        }
                        if (!replaced) v[0] = {x, y}; // just replace either one with x, y
                    }
                    
                    cin >> res;
                    if (res == 'L') assert(0);
                    else if (res == 'W') break;
                    left -= 2;
                }
                dbg(v[0], v[1]);
                // find what to toggle now which should be at most left
                int X = abs(v[0].f-v[1].f);
                int Y = abs(v[0].s-v[1].s);
                dbg(X, Y);
                if (X+Y <= 1) {
                    assert(X+Y != 0);
                    // find the place to put the shitter
                    if (X == 0) {
                        int lowy = min(v[0].s, v[1].s);
                        if (lowy-1 > 0) {
                            x = v[0].f;
                            y = lowy-1;
                        } else if (lowy+2 <= m) {
                            x = v[0].f;
                            y = lowy+2;
                        } else {
                            // wtf we failed when its under 3x3
                            assert(0);
                        }
                    } else {
                        int lowx = min(v[0].f, v[1].f);
                        if (lowx-1 > 0) {
                            x = lowx-1;
                            y = v[0].s;
                        } else if (lowx+2 <= n) {
                            x = lowx+2;
                            y = v[0].s;
                        } else {
                            // wtf we failed when its under 3x3
                            assert(0);
                        }
                    }
                } else {
                    // search for our next move
                    bool found = 0;
                    F0R(i, X+1) F0R(j, Y+1) {
                        if (i == 0 && j == 0) continue;
                        if (i == X && j == Y) continue;
                        if (dp[i][j] <= left && dp[X-i][Y-j] <= left) {
                            found = 1;
                            x = min(v[0].f, v[1].f)+i;
                            y = min(v[0].s, v[1].s)+j;
                            dbg("found", x, y, left, dp[i][j], dp[X-i][Y-j]);
                            break;
                        }
                    }
                    if (!found) assert(0);
                }
            }
        } else {
            cout << 2 << nl; cout.flush();
            int left = 14;
            array<pi, 2> v; v[0] = v[1] = {-12451, -12451};
            while (1) {
                int r, c; cin >> r >> c;
                char res; cin >> res;
                if (res == 'L') assert(0);
                else if (res == 'W') break;

                // look for something that takes at least left
                if (left == 14) {
                    // we need to find something to pick
                    x = -1; y = -1;
                    FOR(i, 1, n) FOR(j, 1, m) {
                        if (i == r && j == c) continue;
                        if (dp[abs(i-r)][abs(j-c)] > 14) {
                            x = i, y = j;
                            break;
                        }
                    }
                    v[0] = {r, c};
                    v[1] = {x, y};
                } else {
                    // remove something that already existed and replace with r, c
                    if ((r == v[1].f && c == v[1].s) || (dp[abs(r-v[0].f)][abs(c-v[0].s)] > left)) {
                        v[1] = {r, c};
                    } else {
                        v[0] = {r, c};
                    }
                }
                left -= 2;
                cout << x << " " << y << nl; cout.flush();
                cin >> res;
                if (res == 'I') assert(0);
                else if (res == 'L') assert(0);
                else if (res == 'W') break;
            }

        }
    }
    return 0;
}
