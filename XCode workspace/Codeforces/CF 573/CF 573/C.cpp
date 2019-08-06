#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, const char * argv[]) {
    long long n, m, k;
    cin >> n >> m >> k;
    long long p[m];
    for (int i = 0; i < m; i++) {
        cin >> p[i];
    }
    long long id = 0;
    long long count = 0;
    long long next;
    while (id < m) {
        next = (((p[id] - id - 1)/k) + 1) * k + id;
        //cout << p[id] << " " << next << endl;
        while (id < m && p[id] <= next) id++;
        count++;
    }
    cout << count << endl;
    return 0;
}
