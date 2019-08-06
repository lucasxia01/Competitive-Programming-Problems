#include <iostream>
#include <stdio.h>
#include <utility>
#include <algorithm>

using namespace std;
// Prints a maximum set of activities that can be done by a single
// person, one at a time.
//  n   -->  Total number of activities
//  s[] -->  An array that contains start time of all activities
//  f[] -->  An array that contains finish time of all activities
void printMaxActivities(pair<int, int> s[], int n)
{
    int i, j;
    
    //printf ("Following activities are selected n");
    
    // The first activity always gets selected
    i = 0;
    //printf("%d ", i);
    int ans = 1;
    // Consider rest of the activities
    for (j = 1; j < n; j++)
    {
        // If this activity has start time greater than or
        // equal to the finish time of previously selected
        // activity, then select it
        if (s[j].second >= s[i].first)
        {
            ans++;
            i = j;
        }
    }
    cout << ans << endl;
}

// driver program to test above function
int main()
{
    int T, n;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> n;
        pair<int, int>* s = new pair<int, int>[n];
        for (int j = 0; j < n; j++) {
            cin >> s[j].second >> s[j].first;
            s[j].first += s[j].second;
        }
        sort(s, s+n);
        printMaxActivities(s, n);
        delete [] s;
    }
    return 0;
}
