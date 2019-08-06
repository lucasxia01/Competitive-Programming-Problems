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
    int n;
    cin >> n;
    if (n % 3 == 0) {
        cout << 1 << " " << 1 << " " << n - 2 << endl;
    } else {
        cout << 1 << " " << 2 << " "<< n - 3 << endl;
    }
    return 0;
}
