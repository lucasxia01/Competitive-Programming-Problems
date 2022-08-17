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
#include <cassert>

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int t[n+1];
    vector<int> edgeList[n+1];
    int edgeCount[n+1];
    F0R(i, n) edgeCount[i+1] = 0;
    priority_queue<pi> zeros;
    F0R(i, n) {
        cin >> t[i+1];
        int d; cin >> d;
        
        int node;
        F0R(j, d) {
            cin >> node;
            edgeList[i+1].pb(node);
            edgeCount[node]++;
        }
    }
    F0R(i, n) {
        if (edgeCount[i+1] == 0) {
            zeros.push(mp(-t[i+1], i+1));
        }
    }
    int ans = 0;
    int done = n-1;
    pi top;
    while (!zeros.empty()) {
        top = zeros.top(); zeros.pop();
        //cout << top.s << " " << -top.f+done << endl;
        ans = max(ans, -top.f+done);
        trav(a, edgeList[top.s]) {
            edgeCount[a]--;
            assert(edgeCount[a] >= 0);
            if (edgeCount[a] == 0) {
                zeros.push(mp(-t[a], a));
            }
        }
        done--;
    }
    cout << ans << endl;
    
    return 0;
}
