//
//  main.cpp
//  ConvexHull
//
//  Created by Lucas Xia on 6/18/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#define INF 1<<30
#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;

int minX, minY;

bool comparePoint(const pii& a, const pii& b) {
    cout << &a << " " << &b << endl;
    int diffX_a = a.f;
    int diffY_a = a.s;
    int diffX_b = b.f;
    int diffY_b = b.s;
    if (diffX_a == 0 && diffY_a == 0) return true;
    if (diffX_b == 0 && diffY_b == 0) return false;
    //return a.f < b.f;
    if ((double)diffY_a/diffX_a < (double)diffY_b/diffX_b) {
        cout << minX + a.f << "," << minY + a.s << " has lesser slope than " << minX + b.f << "," << minY + b.s << endl;
        return true;
    } else if ((double)diffY_a/diffX_a > (double)diffY_b/diffX_b) {
        cout << minX + a.f << "," << minY + a.s << " has greater slope than " << minX + b.f << "," << minY + b.s << endl;
        return false;
    }
    
    if (diffY_a*diffY_a > diffY_b*diffY_b || (diffY_a*diffY_a == diffY_b*diffY_b && diffX_a*diffX_a > diffX_b*diffX_b) ) {
        cout << minX + a.f << "," << minY + a.s << " has same slope/greater mag than " << minX + b.f << "," << minX + b.s << endl;
        return false;
    }
    cout << "some addresses: " << &a << " " << &b << endl;
    cout << minX + a.f << "," << minY + a.s << " has same slope/less mag than " << minX + b.f << "," << minY + b.s << endl;
    return true;
}

int main() {
    int t, n, x, y;
    cin >> t;
    while (t) {
        cin >> n;
        pii points[n], ans[n];
        //int points1[8][2] = {{3,7},{6,8},{7,8},{11,10},{4,3},{8,5},{7,13},{4,13}};
        
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            points[i] = make_pair(x, y);
            ans[i] = make_pair(-1, -1);
        }
        minX = points[0].f;
        minY = points[0].s;
        for (int i = 0; i < n; i++) {
            if (points[i].f < minX) {
                minX = points[i].f;
                minY = points[i].s;
            }
        }
        for (int i = 0; i < n; i++) {
            cout << i << ": " << points[i].f << " " << points[i].s << " " << &points[i] << endl;
            points[i].f -= minX;
            points[i].s -= minY;
        }
        cout << sizeof(points)/sizeof(points[0]) << endl;
        sort(points, points + n, comparePoint);
        for (int i = 0; i < n; i++) {
            points[i].f += minX;
            points[i].s += minY;
            cout << i << ": " << points[i].f << " " << points[i].s << endl;
        }
        ans[0].f = points[0].f;
        ans[0].s = points[0].s;
        ans[1].f = points[1].f;
        ans[1].s = points[1].s;
        cout << ans[0].f << " " << ans[0].s << ", " << ans[1].f << " " << ans[1].s << endl;
        int count = 2;
        int diffX_a, diffY_a, diffX_b, diffY_b;
        for (int i = 2; i < n; i++) {
            
            diffX_a = points[i].f - ans[count - 1].f;
            diffY_a = points[i].s - ans[count - 1].s;
            diffX_b = ans[count - 2].f - ans[count - 1].f;
            diffY_b = ans[count - 2].s - ans[count - 1].s;
            if (diffX_a * diffY_b - diffY_a * diffX_b >= 0) {
                ans[count].f = points[i].f;
                ans[count].s = points[i].s;
                count++;
            } else {
                count--;
                i--;
                if (i < 2) cout << "SOMETHING WRONG" << endl;
            }
        }
        int i = 0;
        for (i = 0; i < n-1; i++) {
            if (ans[i+1].f > 0) cout << ans[i].f << " " << ans[i].s << ", ";
            else break;
        }
        cout << ans[i].f << " " << ans[i].s << endl;
        t--;
    }
    return 0;
}
