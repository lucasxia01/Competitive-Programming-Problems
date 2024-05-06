#include<stdio.h>
#include<algorithm>

using namespace std;

long long M = 998244353;
long long N, A[5][100000], ans = 0;

long long pairs(long long Arr[], int i, int j){
    int k = -1, l = -1;
    for(int x=0; x<4; x++){
        if(i != x && j != x){
            if(k != -1) l = x;
            else k = x;
        }
    }
    long long temp = 1;
    temp = temp * ((Arr[i] * Arr[j]) % M);
    temp %= M;
    temp = temp * (((N-Arr[k])*(N-Arr[l]))% M);
    temp %= M;
    return temp;
}

int main(){
    scanf("%lld", &N);
    for(int i=0; i<5; i++){
        for(int j=0; j<N; j++){
            scanf("%lld", &A[i][j]);
        }
    }
    for(int i=0; i<5; i++){
        sort(A[i], A[i]+N);
    }
    long long temp[4];
    for(int i=0; i<5; i++){
        for(int j=0; j<N; j++){
            long long num = A[i][j];
            int it = 0;
            for(int k=0; k<5; k++){
                if(k == i) continue;
                else if(k < i){
                    temp[it++] = lower_bound(A[k], A[k]+N, num) - A[k];
                } else {
                    temp[it++] = upper_bound(A[k], A[k]+N, num) - A[k];
                }
            }
            for(int i=0; i<4; i++){
                for(int j=i+1; j<4; j++){
                    ans += num*pairs(temp, i, j);
                    ans %= M;
                }
            }
        }
    }
    while(ans < 0) ans += M;
    printf("%lld", ans);
}
