#include <iostream>
using namespace std;


const int V = 6;
const int E = V * (V - 2)/2;
int mat[V][V];

int main(int argc, const char * argv[]) {
    string s = "";
    int x = 0;
    int ans = 1 << E;
    memset(mat, 0, V * V * sizeof(int));
    for (int i = 0; i < 1 << E; i++) {
        s = "";
        x = i;
        for (int j = 0; j < E; j++) {
            if (x % 2) s = "1" + s;
            else s = "0" + s;
            x /= 2;
        }
        cout << s << endl;
        int count = 0;
        for (int j = 2; j < V; j++) {
            for (int k = 2 * (j/2); k < V; k++) {
                mat[j - 2][k] = s[count] - '0';
                mat[k][j - 2] = s[count] - '0';
                count++;
            }
        }
        for (int x0 = 0; x0 < V; x0++) {
            for (int y = 0; y < V; y++) {
                cout << mat[x0][y];
            }
            cout << endl;
        }
        cout << endl;
        
        for (int a = 0; a < V * V; a++) {
            if (a/V == a % V) continue;
            for (int b = a + 1; b < V * V; b++) {
                if (b/V == b % V || b/V != a%V) continue;
                if (mat[a/V][a%V] && mat[b/V][b%V] && mat[a/V][b%V]) {
                    ans--;
                    b = V * V;
                    a = V * V;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
