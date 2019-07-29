#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    string hand[3];
    // m = 0, p = 1, s = 2
    int board[3][10];
    for (int i = 0;i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j] = 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        cin >> hand[i];
        if (hand[i][1] == 'm')
            board[0][hand[i][0] - '0']++;
        if (hand[i][1] == 'p')
            board[1][hand[i][0] - '0']++;
        if (hand[i][1] == 's')
            board[2][hand[i][0] - '0']++;
    }
    int ans = 2;
    for (int i = 0;i < 3; i++) {
        for (int j = 1; j < 10; j++) {
            ans = min(ans, 3 - board[i][j]);
        }
    }
    for (int i = 0;i < 3; i++) {
        for (int j = 1; j < 8; j++) {
            int count = 0;
            for (int k = j; k < j+3; k++) {
                if (board[i][k])
                    count++;
            }
            ans = min(ans, 3 - count);
        }
    }
    cout << ans << endl;
    return 0;
}
