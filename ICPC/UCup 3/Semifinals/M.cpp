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

constexpr int digits(int base) noexcept {
    return base <= 1 ? 0 : 1 + digits(base / 10);
}

constexpr int base = 1000'000'000;
constexpr int base_digits = digits(base);

struct bigint {
    // value == 0 is represented by empty z
    vector<int> z;  // digits

    // sign == 1 <==> value >= 0
    // sign == -1 <==> value < 0
    int sign;

    bigint(long long v = 0) { *this = v; }

    bigint &operator=(long long v) {
        sign = v < 0 ? -1 : 1;
        v *= sign;
        z.clear();
        for (; v > 0; v = v / base)
            z.push_back((int)(v % base));
        return *this;
    }

    bigint(const string &s) { read(s); }

    bigint &operator+=(const bigint &other) {
        if (sign == other.sign) {
            for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
                if (i == z.size())
                    z.push_back(0);
                z[i] += carry + (i < other.z.size() ? other.z[i] : 0);
                carry = z[i] >= base;
                if (carry)
                    z[i] -= base;
            }
        } else if (other != 0 /* prevent infinite loop */) {
            *this -= -other;
        }
        return *this;
    }

    friend bigint operator+(bigint a, const bigint &b) {
        a += b;
        return a;
    }

    bigint &operator-=(const bigint &other) {
        if (sign == other.sign) {
            if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
                for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
                    z[i] -= carry + (i < other.z.size() ? other.z[i] : 0);
                    carry = z[i] < 0;
                    if (carry)
                        z[i] += base;
                }
                trim();
            } else {
                *this = other - *this;
                this->sign = -this->sign;
            }
        } else {
            *this += -other;
        }
        return *this;
    }

    friend bigint operator-(bigint a, const bigint &b) {
        a -= b;
        return a;
    }

    bigint &operator*=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < z.size() || carry; ++i) {
            if (i == z.size())
                z.push_back(0);
            long long cur = (long long)z[i] * v + carry;
            carry = (int)(cur / base);
            z[i] = (int)(cur % base);
        }
        trim();
        return *this;
    }

    bigint operator*(int v) const { return bigint(*this) *= v; }

    friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
        int norm = base / (b1.z.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q, r;
        q.z.resize(a.z.size());

        for (int i = (int)a.z.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.z[i];
            int s1 = b.z.size() < r.z.size() ? r.z[b.z.size()] : 0;
            int s2 = b.z.size() - 1 < r.z.size() ? r.z[b.z.size() - 1] : 0;
            int d = (int)(((long long)s1 * base + s2) / b.z.back());
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.z[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return {q, r / norm};
    }

    friend bigint sqrt(const bigint &a1) {
        bigint a = a1;
        while (a.z.empty() || a.z.size() % 2 == 1)
            a.z.push_back(0);

        int n = a.z.size();

        int firstDigit = (int)::sqrt((double)a.z[n - 1] * base + a.z[n - 2]);
        int norm = base / (firstDigit + 1);
        a *= norm;
        a *= norm;
        while (a.z.empty() || a.z.size() % 2 == 1)
            a.z.push_back(0);

        bigint r = (long long)a.z[n - 1] * base + a.z[n - 2];
        firstDigit = (int)::sqrt((double)a.z[n - 1] * base + a.z[n - 2]);
        int q = firstDigit;
        bigint res;

        for (int j = n / 2 - 1; j >= 0; j--) {
            for (;; --q) {
                bigint r1 = (r - (res * 2 * base + q) * q) * base * base +
                            (j > 0 ? (long long)a.z[2 * j - 1] * base + a.z[2 * j - 2] : 0);
                if (r1 >= 0) {
                    r = r1;
                    break;
                }
            }
            res *= base;
            res += q;

            if (j > 0) {
                int d1 = res.z.size() + 2 < r.z.size() ? r.z[res.z.size() + 2] : 0;
                int d2 = res.z.size() + 1 < r.z.size() ? r.z[res.z.size() + 1] : 0;
                int d3 = res.z.size() < r.z.size() ? r.z[res.z.size()] : 0;
                q = (int)(((long long)d1 * base * base + (long long)d2 * base + d3) / (firstDigit * 2));
            }
        }

        res.trim();
        return res / norm;
    }

    bigint operator/(const bigint &v) const { return divmod(*this, v).first; }

    bigint operator%(const bigint &v) const { return divmod(*this, v).second; }

    bigint &operator/=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int)z.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = z[i] + rem * (long long)base;
            z[i] = (int)(cur / v);
            rem = (int)(cur % v);
        }
        trim();
        return *this;
    }

    bigint operator/(int v) const { return bigint(*this) /= v; }

    int operator%(int v) const {
        if (v < 0)
            v = -v;
        int m = 0;
        for (int i = (int)z.size() - 1; i >= 0; --i)
            m = (int)((z[i] + m * (long long)base) % v);
        return m * sign;
    }

    bigint &operator/=(const bigint &v) {
        *this = *this / v;
        return *this;
    }

    bigint &operator%=(const bigint &v) {
        *this = *this % v;
        return *this;
    }

    bool operator<(const bigint &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (z.size() != v.z.size())
            return z.size() * sign < v.z.size() * v.sign;
        for (int i = (int)z.size() - 1; i >= 0; i--)
            if (z[i] != v.z[i])
                return z[i] * sign < v.z[i] * sign;
        return false;
    }

    bool operator>(const bigint &v) const { return v < *this; }

    bool operator<=(const bigint &v) const { return !(v < *this); }

    bool operator>=(const bigint &v) const { return !(*this < v); }

    bool operator==(const bigint &v) const { return sign == v.sign && z == v.z; }

    bool operator!=(const bigint &v) const { return !(*this == v); }

    void trim() {
        while (!z.empty() && z.back() == 0)
            z.pop_back();
        if (z.empty())
            sign = 1;
    }

    bool isZero() const { return z.empty(); }

    friend bigint operator-(bigint v) {
        if (!v.z.empty())
            v.sign = -v.sign;
        return v;
    }

    bigint abs() const { return sign == 1 ? *this : -*this; }

    long long longValue() const {
        long long res = 0;
        for (int i = (int)z.size() - 1; i >= 0; i--)
            res = res * base + z[i];
        return res * sign;
    }

    friend bigint gcd(const bigint &a, const bigint &b) { return b.isZero() ? a : gcd(b, a % b); }

    void read(const string &s) {
        sign = 1;
        z.clear();
        int pos = 0;
        while (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = (int)s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            z.push_back(x);
        }
        trim();
    }

    friend istream &operator>>(istream &stream, bigint &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream &operator<<(ostream &stream, const bigint &v) {
        if (v.sign == -1)
            stream << '-';
        stream << (v.z.empty() ? 0 : v.z.back());
        for (int i = (int)v.z.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.z[i];
        return stream;
    }

    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<long long> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < p.size(); i++)
            p[i] = p[i - 1] * 10;
        vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int v : a) {
            cur += v * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back(int(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int)cur);
        while (!res.empty() && res.back() == 0)
            res.pop_back();
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        // 2n length strings
        string s[2]; F0R(i, 2) cin >> s[i];
        // find the ranges of l and r for each one
        pi range[2]; F0R(i, 2) range[i] = {0, n};
        bool ok = 1;
        F0R(i, n) {
            F0R(j, 2) {
                if (s[j][2*i] != '?') {
                    int x = s[j][2*i] - '1';
                    ckmax(range[x].f, i+1);
                }
                if (s[j][2*i+1] != '?') {
                    int x = s[j][2*i+1] - '1';
                    ckmin(range[x].s, i);
                }
            }
            // check if there's more than 1 1 or 2
            int cnt[2] = {};
            F0R(j, 2) {
                F0R(k, 2) {
                    if (s[j][2*i+k] != '?') cnt[s[j][2*i+k] - '1']++;
                }
            }
            if (cnt[0] > 1 || cnt[1] > 1) {
                ok = 0;
            }
        }
        F0R(j, 2) {
            dbg(range[j].f, range[j].s);
            if (range[j].f > range[j].s) ok = 0;
        }
        if (!ok) {
            cout << "impossible" << nl;
        } else {
            // try all 4 directions
            string t[2] = {s[0], s[1]};
            bigint ans = -1;
            string best[2];
            F0R(x, 2) F0R(y, 2) {
                F0R(i, n) {
                    int a = 0; // the column of the 1
                    if (i < range[0].f) a = 0;
                    else if (i >= range[0].s) a = 1;
                    else a = x;

                    int b = 0; // the column of the 2
                    if (i < range[1].f) b = 0;
                    else if (i >= range[1].s) b = 1;
                    else b = y;
                    
                    // now fill in the chars
                    if (a == 0 && b == 0) {
                        t[0][2*i] = '2';
                        t[1][2*i] = '1';
                        t[0][2*i+1] = '0';
                        t[1][2*i+1] = '0';
                    } else if (a == 0 && b == 1) {
                        t[0][2*i] = '1';
                        t[1][2*i] = '0';
                        t[0][2*i+1] = '2';
                        t[1][2*i+1] = '0';
                    } else if (a == 1 && b == 0) {
                        t[0][2*i] = '2';
                        t[1][2*i] = '0';
                        t[0][2*i+1] = '1';
                        t[1][2*i+1] = '0';
                    } else {
                        t[0][2*i] = '0';
                        t[1][2*i] = '0';
                        t[0][2*i+1] = '2';
                        t[1][2*i+1] = '1';
                    }
                    // double check with s
                    F0R(j, 2) if (s[j][2*i] != '?' && s[j][2*i] != t[j][2*i]) {
                        swap(t[0][2*i], t[1][2*i]);
                        break;
                    }
                    F0R(j, 2) if (s[j][2*i+1] != '?' && s[j][2*i+1] != t[j][2*i+1]) {
                        swap(t[0][2*i+1], t[1][2*i+1]);
                        break;
                    }
                    F0R(k, 2) F0R(j, 2) if (s[j][2*i+k] != '?' && s[j][2*i+k] != t[j][2*i+k]) assert(0);
                    {
                        int cnt[2] = {};
                        F0R(j, 2) {
                            F0R(k, 2) {
                                if (t[j][2*i+k] != '0') cnt[t[j][2*i+k] - '1']++;
                            }
                        }
                        if (cnt[0] != 1 || cnt[1] != 1) {
                            assert(0);
                        }
                    }
                    if (i != 0) {
                        // check with previous 2x2
                        int cnt[2] = {};
                        F0R(j, 2) {
                            F0R(k, 2) {
                                if (t[j][2*i-1+k] != '0') cnt[t[j][2*i-1+k] - '1']++;
                            }
                        }
                        if (cnt[0] > 1 || cnt[1] > 1) {
                            assert(0);
                        }
                    }
                }
                // now that everything is filled in, compute the answer from t[0]
                string cur = "";
                bigint tmp = 0;
                F0R(i, 2*n+1) {
                    if (i == 2*n || t[0][i] == '0') {
                        bigint x(cur);
                        tmp += x;
                        cur = "";
                    } else {
                        cur += t[0][i];
                    }
                }
                // dbg(tmp);
                // F0R(j, 2) dbg(t[j]);

                if (tmp > ans) {
                    ans = tmp;
                    best[0] = t[0];
                    best[1] = t[1];
                }
            }
            cout << ans << nl;
            F0R(j, 2) cout << best[j] << nl;

            // bigint ansBrute = 0;
            // string bestBrute[2];
            // // now just try all splits
            // FOR(x, range[0].f, range[0].s) {
            //     FOR(y, range[1].f, range[1].s) {
            //         F0R(i, n) {
            //             int a = 0; // the column of the 1
            //             if (i < x) a = 0;
            //             else a = 1;

            //             int b = 0; // the column of the 2
            //             if (i < y) b = 0;
            //             else b = 1;
                        
            //             // now fill in the chars
            //             if (a == 0 && b == 0) {
            //                 t[0][2*i] = '2';
            //                 t[1][2*i] = '1';
            //                 t[0][2*i+1] = '0';
            //                 t[1][2*i+1] = '0';
            //             } else if (a == 0 && b == 1) {
            //                 t[0][2*i] = '1';
            //                 t[1][2*i] = '0';
            //                 t[0][2*i+1] = '2';
            //                 t[1][2*i+1] = '0';
            //             } else if (a == 1 && b == 0) {
            //                 t[0][2*i] = '2';
            //                 t[1][2*i] = '0';
            //                 t[0][2*i+1] = '1';
            //                 t[1][2*i+1] = '0';
            //             } else {
            //                 t[0][2*i] = '0';
            //                 t[1][2*i] = '0';
            //                 t[0][2*i+1] = '2';
            //                 t[1][2*i+1] = '1';
            //             }
            //             // double check with s
            //             F0R(j, 2) if (s[j][2*i] != '?' && s[j][2*i] != t[j][2*i]) {
            //                 swap(t[0][2*i], t[1][2*i]);
            //                 break;
            //             }
            //             F0R(j, 2) if (s[j][2*i+1] != '?' && s[j][2*i+1] != t[j][2*i+1]) {
            //                 swap(t[0][2*i+1], t[1][2*i+1]);
            //                 break;
            //             }
            //         }
            //         // now that everything is filled in, compute the answer from t[0]
            //         string curBrute = "";
            //         bigint tmpBrute = 0;
            //         F0R(i, 2*n+1) {
            //             if (i == 2*n || t[0][i] == '0') {
            //                 bigint x(curBrute);
            //                 tmpBrute += x;
            //                 curBrute = "";
            //             } else {
            //                 curBrute += t[0][i];
            //             }
            //         }
            //         // dbg(tmp);
            //         // F0R(j, 2) dbg(t[j]);

            //         if (tmpBrute > ansBrute) {
            //             ansBrute = tmpBrute;
            //             bestBrute[0] = t[0];
            //             bestBrute[1] = t[1];
            //         }
            //     }
            // }
            // cerr << ansBrute << nl;
            // F0R(j, 2) cerr << bestBrute[j] << nl;

            // if (ans != ansBrute) {
            //     assert(0);
            // }
        }
    }
    return 0;
}
