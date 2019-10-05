#include <iostream>

using namespace std;


long long gcd (long long a, long long b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a % b);
}
int main() {
    long long n, k, a, b;
    cin >> n >> k >> a >> b;
    long long f[2] = {1 + a, k + 1 - a};
    long long s[2] = {1 + b, k + 1 - b};
    long long M = 0, m = 1LL << 60;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int l = 0; l < 2; l++) {
                long long dist = (s[l] - f[j] + (n + i) * k) % (n * k);
                long long stops = (n * k) / gcd(dist, n * k);
                M = max(M, stops);
                m = min(m, stops);
            }
        }
    }
    cout << m << " " << M << endl;
    return 0;
}
