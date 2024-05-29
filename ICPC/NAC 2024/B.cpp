#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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

__int128_t stoint128_t(string s)
{
    string p = s;
    __int128_t val = 0;
    int idx = 0;
    while (p[idx] >= '0' && p[idx] <= '9') {
        val = (10 * val) + (p[idx] - '0');
        idx++;
    }
    return val;
}

string int128_to_string(__int128_t x) {
    string ret = "";
    while (x) {
        ret += (char)((x % 10) + '0');
        x /= 10;
    }
    reverse(all(ret));
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // generate the champernowne string up to like 150
    string small = ""; // this is used to take care of small numbers
    vpi v;
    FOR(i, 1, 125) {
        string x = to_string(i);
        F0R(j, sz(x)) {
            v.pb({i, j});
            small += x[j];
        }
    }
    // string brute = "";
    // vpi v_brute;
    // FOR(i, 1, 15000) {
    //     string x = to_string(i);
    //     F0R(j, sz(x)) {
    //         v_brute.pb({i, j});
    //         brute += x[j];
    //     }
    // }
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = sz(s);
        tuple<int, string, int> ans = {27, "", 0}; // stores the length of first number as string, the first number as a string, and the offset into this string
        F0R(i, sz(small)-n+1) {
            bool match = 1;
            F0R(j, n) {
                // check if it matches
                if (s[j]=='?' || s[j]==small[i+j]) continue;
                else {
                    match = 0;
                    break;
                }
            }
            if (match) {
                string x = to_string(v[i].f);
                ans = {sz(x), x, v[i].s};
                break;
            }
        }


        // tuple<int, string, int> brute_ans = {27, "", 0}; // stores the length of first number as string, the first number as a string, and the offset into this string
        // F0R(i, sz(brute)-n+1) {
        //     bool match = 1;
        //     F0R(j, n) {
        //         // check if it matches
        //         if (s[j]=='?' || s[j]==brute[i+j]) continue;
        //         else {
        //             match = 0;
        //             break;
        //         }
        //     }
        //     if (match) {
        //         string x = to_string(v_brute[i].f);
        //         brute_ans = {sz(x), x, v_brute[i].s};
        //         break;
        //     }
        // }
        // assert(get<0>(brute_ans) != 27);

        // dbg(get<0>(ans), get<1>(ans), get<2>(ans));
        // now just pad the string with many ?
        int pad = 26;
        string st = ""; F0R(i, pad) st += '?';
        st += s;
        n = sz(st);
        F0R(i, pad+1) { // first start of a number, up
            FOR(len, 3, 26) { // length of this number
                if (i+len <= pad) continue; // first number should use at least one non padded digit
                
                F0R(carries, len+1) { // number of digits that get carried over
                    // special case if carries = 0
                    // special case if carries = len
                    F0R(j, 10) { // we carry after the jth number
                        // now process the string in the chunks
                        int idx = i;
                        vector<string> strs;
                        int str_idx = 0;
                        while (idx < n) {
                            // go from idx to idx+len
                            string cur = "";
                            int curLen = len;
                            if (str_idx > j && carries==len) curLen++; // we get an extra digit
                            F0R(k, curLen) {
                                if (idx+k >= n) cur += '?';
                                else cur += st[idx+k];
                            }
                            strs.pb(cur);
                            idx+=curLen;
                            str_idx++;
                        }
                        int num_strs = str_idx;
                        if (num_strs <= j) break; // we don't have to look at higher js
                        // now we have strs, check the validity and find the min
                        // the first len-carries-1 digits are fixed
                        // the next 1 digit increases by 1 once after carrying
                        // the last carries digits are 99..9x then 99..99, 00..00, 00..01, ..., 00..0y
                        bool ok = 1;
                        vector<string> digits(num_strs, "");
                        F0R(jj, len-carries-1) { // this is for the fixed digits
                            // check that they're all ? or same digit
                            char digit = '?';
                            F0R(k, num_strs) { 
                                if (strs[k][jj] != '?') {
                                    if (digit != '?' && digit != strs[k][jj]) {
                                        ok = 0;
                                        break;
                                    } else if (digit == '?')  digit = strs[k][jj];
                                }
                            }
                            if (!ok) break;
                            F0R(k, num_strs) digits[k] += digit;
                        }
                        if (!ok) continue;
                        if (carries == len) {
                            F0R(k, num_strs) { // for the 1 digit that increases by 1 from the carry
                                if (k <= j) digits[k]; // do nothing
                                else {
                                    digits[k] = '1'; // add 1
                                    if (strs[k][0] != '?' && strs[k][0] != '1') {
                                        ok = 0;
                                        break;
                                    }
                                }
                            }
                        } else if (carries != 0) {
                            char curDigit = '?';
                            F0R(k, num_strs) { // for the 1 digit that increases by 1 from the carry
                                // we don't overflow to a new digit
                                // we should find what this digit is
                                char d = strs[k][len-carries-1];
                                if (d != '?') {
                                    if (k <= j) {
                                        if (curDigit == '?') curDigit = d;
                                        else if (curDigit != d) {
                                            ok = 0;
                                            break;
                                        }
                                    } else {
                                        if (d == '0') {
                                            ok = 0;
                                            break;
                                        }
                                        d--;
                                        if (curDigit == '?') curDigit = d;
                                        else if (curDigit != d) {
                                            ok = 0;
                                            break;
                                        }
                                    }
                                }
                            }
                            if (curDigit == '?') {
                                if (sz(digits[0]) == 0)curDigit = '1';
                                else curDigit = '0';
                            }
                            F0R(k, num_strs) 
                                if (k <= j) digits[k] += curDigit; // still a case to handle if its ?, maybe not actually, we just set it to 0
                                else {
                                    if (curDigit+1 > '9') ok = 0;
                                    digits[k] += (char)(curDigit+1);
                                }
                        } else {
                            // carries is 0
                            char curDigit = '?';
                            F0R(k, num_strs) { // for the 1 digit that increases by 1 from the carry
                                // we don't overflow to a new digit
                                // we should find what this digit is
                                char d = strs[k][len-carries-1];
                                if (d != '?') {
                                    if (d-'0' < k) {
                                        ok = 0;
                                        break;
                                    }
                                    d-=k;
                                    if (curDigit == '?') curDigit = d;
                                    else if (curDigit != d) {
                                        ok = 0;
                                        break;
                                    }
                                }
                            }
                            if (curDigit == '?') {
                                if (sz(digits[0]) == 0)curDigit = '1';
                                else curDigit = '0';
                            }
                            F0R(k, num_strs) {
                                if (curDigit+k > '9') ok = 0;
                                digits[k] += (char)(curDigit+k);
                            }
                        }
                        if (carries > 0) {
                            F0R(k, num_strs) { // the last digits that are fixed
                                string cur = "";
                                F0R(jj, carries-1) {
                                    if (k <= j) cur += '9';
                                    else cur += '0';
                                }
                                char lastDigit = (k-j+9)%10 + '0';
                                cur += lastDigit;
                                // check that it compares to strs
                                trav(c, cur) {
                                    char d = strs[k][sz(digits[k])];
                                    if (d != '?' && d != c) {
                                        ok = 0;
                                        break;
                                    }
                                    digits[k] += c;
                                }
                                if (!ok) break;
                            }
                            if (!ok) continue;
                        }
                        if (!ok) continue;
                        if (len == 3) {
                            dbg(i, len, carries, j, num_strs);
                            F0R(k, num_strs) {
                                dbg(k, strs[k], digits[k]);
                                assert(sz(strs[k]) == sz(digits[k]));
                            }
                        }
                        // check the digits
                        // NO LEADING ZEROS
                        F0R(jj, len) {
                            if (jj == 0 && digits[0][jj] == '?') digits[0][jj] = '1';
                            else if (digits[0][jj] == '?') digits[0][jj] = '0';
                        }
                        if (digits[0][0] == '0') continue;
                        // we're ok now?
                        // offset is i
                        ckmin(ans, {sz(digits[0]), digits[0], pad-i});

                    }
                }
            }
        }
        dbg(get<0>(ans), get<1>(ans), get<2>(ans));
        // check that it actually matches the given string...
        assert(get<0>(ans) != 27);
        string check = "";
        __int128_t cur = stoint128_t(get<1>(ans));
        while (sz(check)-get<2>(ans) < sz(s)) {
            check += int128_to_string(cur);
            cur++;
        }
        // cut off offset from start
        check = check.substr(get<2>(ans));
        // now compare it to s
        assert(sz(check) >= sz(s));
        F0R(i, sz(s)) {
            if (s[i] != '?' && s[i] != check[i]) {
                assert(0);
            }
        }
        // if (ans != brute_ans) {
        //     dbg(s);
        //     assert(0);
        // }
        // calculate the answer
        // find sum of strings up to 10^n-1
        int len = get<0>(ans);
        ll cnt = 9;
        ll total = 0;
        FOR(i, 1, len-1) {
            total += (1LL*cnt * i);
            total %= MOD;
            cnt *= 10;
            cnt %= MOD;
        }
        // now process the string
        ll c = 0;
        ll pow = 1;
        F0Rd(i, len) {
            int d = (get<1>(ans)[i] - '0');
            if (i == 0) d--;
            c += (d * pow)%MOD;
            c %= MOD;
            pow *= 10;
            pow %= MOD;
        }
        c = (c*len)%MOD;
        cout << (total+c+get<2>(ans)+1)%MOD << nl;
    }
    return 0;
}
