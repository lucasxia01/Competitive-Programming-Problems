#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <string>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MOD 998244353
using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string a, l, r;
    cin >> a >> l >> r;
    ll n = a.length();
    int dp[n + 1];
    dp[0] = 1;
    rep(i, n) {
        
    }
    
    cout << dp[n] << endl;
    return 0;
}
