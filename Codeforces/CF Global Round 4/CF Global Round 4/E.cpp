#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <functional>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <regex>
#include <fstream>
#include <utility>

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
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

string s;

void process (int idx) {
    size_t len = s.length();
    if (len-2*idx < 2) {
        return;
    } else if (len-2*idx < 4) {
        cout << s[0];
        return;
    }
    int* freq = new int[3];
    F0R(i, 3) freq[i] = 0;
    freq[s[idx]-'a']++;
    freq[s[idx+1]-'a']++;
    freq[s[len-1-idx]-'a']++;
    freq[s[len-2-idx]-'a']++;
    F0R(i, 3) {
        if (freq[i] >= 2) {
            delete [] freq;
            cout << char('a'+i);
            process(idx+2);
            cout << char('a'+i);
            break;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> s;
    process(0);
    return 0;
}
