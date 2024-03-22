#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

int r, c;
int comb[8][8];
void comp_comb() {
    comb[0][0] = 1;
    rep(i, 0, 7) {
        rep(j, 0, i+1) {
            comb[i+1][j] += comb[i][j];
            comb[i+1][j+1] += comb[i][j];
        }
    }
}
vi ansV(7, 0);
vi ansH(8, 0);
// 6 rows
// 7 columns
const int MX = 8*8*8*8*8*8;
int dp1[8][MX];
int dp2[7][6][7][MX];
int mod = 998244353;
int to_num(array<int, 6> vals){
    int x = 0;
    for(int i = 0; i<vals.size(); i++){
        x *= 8;
        x += vals[i];
        assert(vals[i]>=0);
        assert(vals[i]<=7);
    }
    return x;
}
int go1(int col, array<int, 6> vals);
int go2(int col, int row, int rem, array<int, 6> vals){
    if(row==6 && rem==0){
        return go1(col+1,vals);
    } else if (row==6 || rem==-1) return 0;
    int val_ind = to_num(vals);
    if(dp2[col][row][rem][val_ind]>=0){
        return dp2[col][row][rem][val_ind];
    }
    
    vals[row]++;
    int ret = go2(col,row+1,rem,vals);
    vals[row]--;
    ret += go2(col,row+1,rem-1,vals);
    ret %= mod;
    dp2[col][row][rem][val_ind] = ret;
    return ret;
}
int formula1(int x){
    // there is x in my column
    return ansV[x];
}
int formula2(int x){
    // there is x in my row
    // dbg("formula2", x);
    return ansH[x];
}
int go1(int col, array<int, 6> vals){
    int val_ind = to_num(vals);
    if(dp1[col][val_ind]>=0){
        return dp1[col][val_ind];
    }
    if(col == 7){
        int ret = 1;
        for(int i = 0; i<6; i++){
            ret = (1LL*ret*formula2(vals[i])) %mod;
        }
        dp1[col][val_ind] = ret;
        return ret;
    }
    int ret = 0;
    for(int how_many = 0; how_many <= 6; how_many++){
        int tmp = (1LL*formula1(how_many)*go2(col, 0, how_many, vals))%mod;
        ret += tmp;
        ret %= mod;
    }
    dp1[col][val_ind] = ret;
    return ret;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    comp_comb();
    cin >> r >> c;
    vi ansV0(7, 0);
    int ans[7][7];
    rep(i, 0, 7) {
        rep(ii, 0, i+1) {
            // raise to c/7-1
            ans[i][ii] = 1;
            rep(j, 0, c/7) {
                ans[i][ii] = (1LL*ans[i][ii]*comb[i][ii])%mod;
            }
            ansV0[i] += ans[i][ii];
            ansV0[i] %= mod;
        }
        // cout << ansV0[i] << endl;
    }
    // for the verts, we want to do PIE
    rep(i, 0, 7) { // we have i chosen Vertically striped cells
        // now go over all 3^i cases
        ansV[i] = 0;
        int HI = (int)pow(3, i);
        rep(mask, 0, HI) {
            int cur = mask;
            int cnt1 = 0; // count of all 0s or all 1s
            int cnt2 = 0; // count of all 1s
            rep(ii, 0, i) {
                // go through the mask and see the state of each thing
                int val = cur%3;
                if (val == 0) { // all 0s
                    cnt1++;
                } else if (val == 1) {
                    cnt1++;
                    cnt2++;
                } else {
                    // this is a true vert
                }
                cur /= 3;
            }
            // we have i-cnt1 actual verts
            // and 
            int tmp = ansV0[i-cnt1];
            if (cnt1%2) {
                ansV[i] -= tmp;
                ansV[i] += mod;
            } else {
                ansV[i] += tmp;
            }
            ansV[i] %= mod;
        }
        // cout << HI << " " << i << " " << ansV[i] << endl;
    }
    rep(i, 0, 8) {
        rep(ii, 0, i+1) {
            int tmp = 1;
            rep(j, 0, r/6) {
                tmp = (1LL*tmp*comb[i][ii])%mod;
            }
            ansH[i] += tmp;
            ansH[i] %= mod;
        }
        // cout << i << " " << ansH[i] << endl;
    }
    array<int, 6> vec = {};


    for(int a = 0; a<8; a++){
        for(int b = 0; b<MX; b++){
            dp1[a][b] = -1;
        }
    }
    for(int a = 0; a<7; a++){
        for(int b = 0; b<6; b++){
            for(int c = 0; c<7; c++){
                for(int d = 0; d<MX; d++){
                    dp2[a][b][c][d] = -1;
                }
            }
        }
    }
    cout << go1(0,vec) << endl;

}
