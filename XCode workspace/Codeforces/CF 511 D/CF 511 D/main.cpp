#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <string>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    if (n <= 2) cout << 0 << endl;
    else if (n % 2 == 0) cout << n << endl;
    else cout << n - 1;
    return 0;
}
