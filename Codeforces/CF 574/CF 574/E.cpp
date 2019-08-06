#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, m, a, b;
    cin >> n >> m >> a >> b;
    long long g, x, y, z;
    cin >> g >> x >> y >> z;
    long long mat[n][m], mat1[n][m - b + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat[i][j] = g;
            g = ((g*x) % z + y) % z;
            //cout << mat[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;
    deque<long long> dq;
    for (int i = 0; i < n; i++) {
        dq.clear();
        for (int j = 0; j < m; j++) {
            while (dq.size() != 0 && mat[i][dq.back()] >= mat[i][j]) {
                dq.pop_back();
            }
            dq.push_back(j);
            if (j >= b-1) {
                while (dq.size() != 0 && dq.front() <= j - b) {
                    dq.pop_front();
                }
                mat1[i][j-b+1] = mat[i][dq.front()];
            }
//            for (int k = 0; k < dq.size(); k++) {
//                cout << dq[k] << " ";
//            }
//            cout << endl;
        }
    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m - b + 1; j++) {
//            cout << mat1[i][j] << " ";
//        }
//        cout << endl;
//    }
    long long ans = 0;
    for (int j = 0; j <= m - b; j++) {
        dq.clear();
        for (int i = 0; i < n; i++) {
            while (dq.size() != 0 && mat1[dq.back()][j] >= mat1[i][j]) {
                dq.pop_back();
            }
            dq.push_back(i);
            if (i >= a-1) {
                while (dq.size() != 0 && dq.front() <= i - a) {
                    dq.pop_front();
                }
                ans += mat1[dq.front()][j];
            }
//            for (int k = 0; k < dq.size(); k++) {
//                cout << dq[k] << " ";
//            }
//            cout << endl;
        }
    }
    cout << ans << endl;
    return 0;
}
