#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    int adj[m][m];
    F0R(i, m) F0R(j, m) adj[i][j] = 0;
    F0R(i, n-1) {
        adj[s[i]-'a'][s[i+1]-'a']++;
        adj[s[i+1]-'a'][s[i]-'a']++;
    }
    vector<int> keyboard;
    F0R(i, m) {
        int minIdx = -1, minAns = INF;
        F0R(j, keyboard.size()+1) {
            int count = 0;
            F0R(k, keyboard.size()) {
                FOR(l, k+1, keyboard.size()) {
                    if (k < j && l >= j) {
                        count += (l-k+1)*adj[keyboard[k]][keyboard[l]];
                    } else {
                        count += (l-k)*adj[keyboard[k]][keyboard[l]];
                    }
                }
            }
            F0R(k, keyboard.size()) {
                if (k < j) count += (j-k)*adj[keyboard[k]][i];
                else count += (k-j+1)*adj[keyboard[k]][i];
            }
            //cout << i << " " << j << " " << count << endl;
            if (count < minAns) {
                minAns = count;
                minIdx = j;
            }
        }
        int k = 0;
        for (vector<int>::iterator it = keyboard.begin(); it != keyboard.end(); it++) {
            if (minIdx == k) {
                keyboard.insert(it, i);
                break;
            }
            k++;
        }
        if (k == keyboard.size()) keyboard.pb(i);
    }
    int ans = 0;
    F0R(k, keyboard.size()) {
        //cout << (char)('a'+keyboard[k]) << endl;
        FOR(l, k+1, keyboard.size()) {
            ans += (l-k)*adj[keyboard[k]][keyboard[l]];
        }
    }
    cout << ans << endl;
    return 0;
}
