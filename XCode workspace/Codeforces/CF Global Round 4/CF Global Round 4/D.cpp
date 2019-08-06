#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#define MOD 998244353

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int nextPrime = n;
    while (true) {
        int i;
        for (i = 2; i*i <= nextPrime; i++) {
            if (nextPrime % i == 0) {
                break;
            }
        }
        if (i*i > nextPrime) break;
        else nextPrime++;
    }
    cout << nextPrime << endl;
    int diff = nextPrime - n;
    for (int i = 0; i < n; i++) {
        cout << i+1 << " " << (i+1)%n + 1 << endl;
    }
    for (int i = 0; i < diff; i++) {
        cout << i+1 << " " << n/2 + (i+1) << endl;
    }
    
    
    return 0;
}
