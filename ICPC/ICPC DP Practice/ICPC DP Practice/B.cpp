#include <iostream>
#include <string>
//#include <cmath>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    cout << n << endl;
    // n - number of columns in grid
    // k - number of componenets required
    //    const int size = 500;
    //    int bicolorings[1000]={0};
    //    int bb[size][2*size]={0}, bw[size][2*size]={0}, wb[size][2*size]={0}, ww[size][2*size]={0};
    
//    int bb[1000][1000]={0}, bw[1000][1000]={0}, wb[1000][1000]={0}, ww[1000][1000]={0};
//
//    bb[0][0] = 1;
//    bw[0][0] = 0;
//    wb[0][0] = 0;
//    ww[0][0] = 1;
//
//    bb[0][1] = 0;
//    bw[0][1] = 1;
//    wb[0][1] = 1;
//    ww[0][1] = 0;
//
//    for (int i = 1; i < n; i++) { // cols
//        bb[i][0] = bb[i-1][0] + bw[i-1][0] + wb[i-1][0];
//        bw[i][0] = bw[i-1][0];
//        wb[i][0] = wb[i-1][0];
//        ww[i][0] = bw[i-1][0] + wb[i-1][0] + ww[i-1][0];
//
//        bb[i][1] = bb[i-1][1] + bw[i-1][1] + wb[i-1][1] + ww[i-1][0];
//        bw[i][1] = bb[i-1][0] + bw[i-1][1] + ww[i-1][0];
//        wb[i][1] = bb[i-1][0] + wb[i-1][1] + ww[i-1][0];
//        ww[i][1] = bb[i-1][0] + bw[i-1][1] + wb[i-1][1] + ww[i-1][1];
//
//        for (int j = 2; j < 2*i+2; j++) {
//            bb[i][j] = bb[i-1][j] + bw[i-1][j] + wb[i-1][j] + ww[i-1][j-1];
//            bw[i][j] = bb[i-1][j-1] + bw[i-1][j] + wb[i-1][j-2] + ww[i-1][j-1];
//            wb[i][j] = bb[i-1][j-1] + bw[i-1][j-2] + wb[i-1][j] + ww[i-1][j-1];
//            ww[i][j] = bb[i-1][j-1] + bw[i-1][j] + wb[i-1][j] + ww[i-1][j];
//        }
//    }
//    cout << ((bb[n-1][k-1]%998244353 + bw[n-1][k-1]%998244353)%998244353 + (wb[n-1][k-1]%998244353 + ww[n-1][k-1]%998244353)%998244353)%998244353 << endl;
//
    
    
    //    int bicolorings[2000][4];
    //
    //    for (int i = 0; i < 2*n; i++) { // cols
    //        bb[i] = bb[1] + bw[i-1][1] + wb[i-1][1] + ww[i-1][0]+1;
    //        bw[i] = bb[0]+1 + bw[i-1][1] + ww[i-1][0]+1;
    //        wb[i] = bb[0]+1 + wb[i-1][1] + ww[i-1][0]+1;
    //        ww[i] = bb[0]+1 + bw[i-1][1] + wb[i-1][1] + ww[i-1][1];
    //
    //        bicolorings[i][0] = bb[i][0] + bw[i][1] + wb[i][2] + ww[i-1][3]+1;
    //
    //        for (int j = 0; j < 4; j++) {
    //
    //            bb[i][j] = bb[i-1][j] + bw[i-1][j] + wb[i-1][j] + ww[i-1][j-1]+1;
    //            bw[i][j] = bb[i-1][j-1]+1 + bw[i-1][j] + wb[i-1][j-2]+2 + ww[i-1][j-1]+1;
    //            wb[i][j] = bb[i-1][j-1]+1 + bw[i-1][j-2]+2 + wb[i-1][j] + ww[i-1][j-1]+1;
    //            ww[i][j] = bb[i-1][j-1]+1 + bw[i-1][j] + wb[i-1][j] + ww[i-1][j];
    //        }
    //    }
    //    cout << (bb[n-1] + bw[n-1] + wb[n-1] + ww[n-1]) << endl;
}
