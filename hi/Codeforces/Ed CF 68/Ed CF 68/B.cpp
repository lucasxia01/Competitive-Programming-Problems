#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long q, n, m;
    cin >> q;
    
    for (int i = 0; i < q; i++) {
        cin >> n >> m;
        string mat[n];
        
        for (int j = 0; j < n; j++) {
            cin >> mat[j];
        }
        int rows[n];
        int cols[m];
        for (int x = 0; x < n; x++) {
            int count = 0;
            for (int y = 0; y < m; y++) {
                if (mat[x][y] == '*') count++;
            }
            rows[x] = count;
        }
        for (int y = 0; y < m; y++) {
            int count = 0;
            for (int x = 0; x < n; x++) {
                if (mat[x][y] == '*') count++;
            }
            cols[y] = count;
        }
        long long ans = n+m-1;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                long long center = mat[x][y]=='*';
                ans = min(ans, n + m - 1 - rows[x] - cols[y] + center);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
