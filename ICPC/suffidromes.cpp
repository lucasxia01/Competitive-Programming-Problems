#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
// added by Lucas
#define trav(a, x) for (auto& a : x)
#define f first
#define s second
#define pb push_back
const char nl = '\n';
// stretching it a little
template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }
#ifdef DBG
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

const int INF = 1005;
// seems like kactl is missing rng
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

bool check(const string& s, int L) {
    bool ok = 1;
    for (int l = L, r = sz(s)-1; l < r; l++, r--) {
        if (s[l] != s[r]) {
            ok = 0;
            break;
        }
    }
    return ok;
}
int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
	while (1) {
	    string a, b; 
	    if (!getline(cin, a)) break;
	    getline(cin, b);
	    if (a == b) {
	        cout << "No solution." << nl;
	        continue;
	    }
	    // find longest prefix match
	    int prefixMatch = 0;
	    while (prefixMatch < min(sz(a), sz(b))) {
	        if (a[prefixMatch] != b[prefixMatch]) break;
	        prefixMatch++;
	    }
	    // now try up to smaller string+1 length
	    if (sz(a) > sz(b)) swap(a, b);
	    int len = sz(a);
	    int ans = INF;
	    string out = "";
	    rep(i, 0, len+1) {
	        // check if substring from i to len is a palindrome naively
	        if (check(a, i)) {
	            if (prefixMatch >= i && check(b, i)) continue;
	            ans = i;
	            break;
	        }
	    }
	    if (sz(a) == sz(b)) assert(ans != INF);
	    if (ans == INF) { // we can pick a character then the whole a
            ans = len+1;
	       if (prefixMatch >= len) {
                out = a;
	            if (b[len] == 'a') out += 'b';
	            else out += 'a';
                reverse(all(out));
	       } else {
	           out = a + 'a';
	           reverse(all(out));
	       }
	    } else {
	        out = a.substr(0, ans);
	        reverse(all(out));
	    }
	    
	    int ans2 = INF;
	    string out2 = "";
	    // try up to len+1 on b
	    rep(i, 0, len+1) {
	        if (check(b, i)) { // b + x is a pal
	            if (prefixMatch >= i && check(a, i)) continue;
	            ans2 = i;
	            break;
	        }
	    }
	    if (sz(a) == sz(b)) assert(ans2 != INF);
	    if (ans2 == INF) {
	        if (check(b, len+1) && prefixMatch != len) {
	            ans2 = len+1;
	            out2 = b.substr(0, len+1);
	            reverse(all(out2));
	        }
	    } else {
	        out2 = b.substr(0, ans2);
	        reverse(all(out2));
	    }
	    if (ans < ans2) cout << out << nl;
	    else if (ans > ans2) {
            out = out2;
            cout << out2 << nl;
	    } else {
	        assert(ans != INF);
	        if (out > out2) swap(out, out2);
	        cout << out << nl;
	    }
        string x = a+out;
        string y = b+out;
        int cnt = 0;
        if (check(x, 0)) cnt++;
        if (check(y, 0)) cnt++;
        assert(cnt == 1);
	}
}