#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    int count[n];
    cin >> count[0];
    int sum = count[0], sum1 = count[0], count1 = 1;
    for (int i = 1; i < n; i++) {
        cin >> count[i];
        sum += count[i];
        if (2*count[i] <= count[0]) {
            sum1 += count[i];
            count[i] = -1;
            count1++;
        }
        
    }
    //cout << sum << " " << sum1 << " " << count1 << endl;
    if (2*sum1 > sum) {
        cout << count1 << endl;
        cout << 1;
        for (int i = 1; i < n; i++) {
            if (count[i] == -1) {
                cout << " " << i+1;
            }
        }
        cout << endl;
    } else {
        cout << 0 << endl;
    }
    
    return 0;
}
