#include <iostream>
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

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, t, h;
    cin >> n;
    vpi g;
    F0R(i, n) {
        cin >> t >> h;
        g.pb(mp(-h, t));
    }
    sort(g.begin(), g.end());
    int ans = 0;
    priority_queue<int> jobs;
    int nextJob = 1;
    const int INF = 1<<30;
    int curJobLen = g[0].s;
    int start = -g[0].f;
    while (true) {
        //cout << curJobLen << " " << start << endl;
        if (curJobLen > start && nextJob >= n) break;
        if (curJobLen <= start+g[nextJob].f) {
            ans++;
            start -= curJobLen;
            if (!jobs.empty()) {
                curJobLen = -jobs.top();
                jobs.pop();
            } else curJobLen = INF;
        } else {
            if (curJobLen != INF) jobs.push(-curJobLen+(start+g[nextJob].f));
            jobs.push(-g[nextJob].s);
            start = -g[nextJob].f;
            curJobLen = -jobs.top();
            jobs.pop();
            nextJob++;
        }
    }
    cout << ans << endl;
    return 0;
}
