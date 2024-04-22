#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define trav(a, x) for(auto& a : x)
#define f first
#define s second
#define pb push_back
const char nl = '\n';

#ifdef DBG
void dbg_out() { cerr << nl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        vi a(n), b(m);
        rep(i, 0, n)
            cin >> a[i];
        rep(i,0, m)
            cin >> b[i];
        int j = 0;
        rep(i,0, n)
            if(a[i] == b[j]) {
                j++;
                if(j == m)
                    break;
            }
        if(j == m)
            cout << "Yes\n";
        else 
            cout << "No\n"; 
    }

}