#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    string board;
    cin >> board;
    int first_0 = -1, first_1 = -1, last_0 = -1, last_1 = -1;
    for (int i = 0; i < n; i++) {
        if (board[i] == '0' && first_0 == -1) first_0 = i;
        if (board[i] == '1' && first_1 == -1) first_1 = i;
        if (board[i] == '0') last_0 = i;
        else last_1 = i;
    }
    if (last_1 - first_1 < k || last_0 - first_0 < k) cout << "tokitsukaze" << endl;
    else if (last_1 - first_1 == k && last_0 - first_0 == k && !(last_1 < first_0 || last_0 < first_1)) {
        cout << "quailty" << endl;
    } else {
        cout << "once again" << endl;
    }
    
    return 0;
}
