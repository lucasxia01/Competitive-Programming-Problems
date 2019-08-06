#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value) {
    if (n < 0) return -1;
    for (int i = 0; i < n; i++) a[i] += value; // adds to everything
    return n;
}
int lookup(const string a[], int n, string target) {
    for (int i = 0; i < n; i++) if (a[i] == target) return i; // finds target and returns position
    return -1;
}
int positionOfMax(const string a[], int n) {
    if (n <= 0) return -1;
    string best = a[0]; // set best to first thing
    int bestPos = 0;
    for (int i = 0; i < n; i++) if (a[i] > best) { // if higher value
        best = a[i];
        bestPos = i; // update position
    }
    return bestPos;
}
int rotateLeft(string a[], int n, int pos) {
    if (n < 0) return -1;
    if (pos < 0 || pos >= n) return -1;
    string temp = a[pos]; // store temporarily
    for (int i = pos; i < n - 1; i++) a[i] = a[i + 1]; // move them
    a[n - 1] = temp; // change last value
    return pos;
}
int countRuns(const string a[], int n) {
    if (n < 0) return -1;
    int count = 0;
    string prev = "";
    for (int i = 0; i < n; i++) {
        if (prev != a[i]) { // check if not same run
            count++; // add to count
            prev = a[i]; // change the new current value
        }
    }
    return count;
}
int flip(string a[], int n) {
    if (n < 0) return -1;
    string temp = "";
    for (int i = 0; i < n/2; i++) { // only go halfway
        temp = a[i]; // temp variable to swap
        a[i] = a[n - 1 - i]; // swap them
        a[n - 1 - i] = temp; // swap them
    }
    return n;
}
int differ(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) return -1;
    for (int i = 0; i < min(n1, n2); i++) if (a1[i] != a2[i]) return i; // check if they differ and return first position
    return min(n1, n2);
}
int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) return -1;
    for (int i = 0; i <= n1 - n2; i++) { // condition is to not go out of bounds
        int j;
        for (j = 0; j < n2; j++) if (a1[i + j] != a2[j]) break; // if not same, it is not subsequence
        if (j == n2) return i; // if it went through whole a2 array, it is subsequence
    }
    return -1;
}
int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) return -1;
    for (int i = 0; i < n1; i++) for (int j = 0; j < n2; j++) if (a1[i] == a2[j]) return i; // check if same and return
    return -1; // if none found
}
int divide(string a[], int n, string divider) {
    if (n < 0) return -1;
    int id = 0; // index of first unused position
    string temp;
    for (int i = 0; i < n; i++) {
        if (a[i] < divider) { // send anything less than divider to front
            temp = a[i];
            a[i] = a[id];
            a[id] = temp;
            id++;
        }
    }
    int id2 = n - 1; // last index of unused position
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] > divider) { // send anything more than divider to back
            temp = a[i];
            a[i] = a[id2];
            a[id2] = temp;
            id2--;
        }
    }
    return id; // this is where the divider is
}

void print(string a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}
int main() {
    //test cases given by smallberg
    {
        string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
        assert(lookup(h, 7, "eleni") == 5);
        assert(lookup(h, 7, "ed") == 2);
        assert(lookup(h, 2, "ed") == -1);
        assert(positionOfMax(h, 7) == 3);
        string g[4] = { "greg", "gavin", "fiona", "kevin" };
        assert(differ(h, 4, g, 4) == 2);
        assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
        assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");
        string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
        assert(countRuns(d, 5) == 2);
        string e[4] = { "ed", "xavier", "", "eleni" };
        assert(subsequence(h, 7, e, 4) == 2);
        string f[3] = { "fiona", "ed", "john" };
        assert(lookupAny(h, 7, f, 3) == 2);
        assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");
        string names[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
        string names1[10] = { "gavin", "kevin", "greg" };
        assert(subsequence(names, 6, names1, 3)==1);  // returns 1
        string names2[10] = { "eleni", "greg" };
        assert(subsequence(names, 5, names2, 2)==-1);
        string names3[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
        string set1[10] = { "dianne", "betty", "greg", "gavin" };
        assert(lookupAny(names, 6, set1, 4)==1);  // returns 1 (a1 has "gavin" there)
        string set2[10] = { "xavier", "ed" };
        assert(lookupAny(names, 6, set2, 2)==-1);  // returns -1 (a1 has none)
        string candidate[6] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty" };
        assert(divide(candidate, 6, "eleni") == 3) ;  //  returns 3
        assert(divide(h, 7, "fiona") ==3);
        
        string candidate1[6] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty" };
        assert(positionOfMax(candidate1, 6)==3);   // returns 3, since  xavier  is latest
        // in alphabetic order
        string politician[5] = { "eleni", "dianne", "fiona", "kevin", "gavin" };
        assert(rotateLeft(politician, 5, 1)==1);  // returns 1
        string d1[9] = {
            "xavier", "betty", "john", "john", "ed", "ed", "ed", "john", "john"
        };
        assert(countRuns(d1, 9)==5);  //  returns 5
        string folks[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
        assert(flip(folks, 4)==4&& folks[0]=="xavier"  && folks[1]==""  && folks[2]=="john"  && folks[3]=="betty"  && folks[4]=="kevin" && folks[5]== "dianne");  // returns 4
        string candidate100[6] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty" };
        assert(divide(candidate100, 6, "eleni")==3);
        string candidate101[4] = { "gavin", "kevin", "fiona", "john" };
        assert(divide(candidate101, 4, "john")==2);
    }
    
    //own test cases
    //appendToAll test cases
    {
        string append1[2] = {"", "abc"} ;
        assert(appendToAll(append1, -1, "123")==-1) ; //returns -1 for negative nubmers
        string append2[2] = {"", "abc"} ;
        assert(appendToAll(append2, 0, "123") == 0 && append2[0] == "") ; //returns 0 and nothing changes for 0
        string append3[2] = {"", "abc"} ;
        assert(appendToAll(append3, 2, "123") == 2 && append3[0] == "123" && append3[1] == "abc123") ; //works correctly for natural numbers
        string append4[0] = {} ;
        assert(appendToAll(append4, 0, "123")== 0) ; //retunrs 0 for empty set
    }
    
    //lookup test cases
    {
        string look1[3] = {"abc", "Abc", "abc"} ;
        assert(lookup(look1, -1, "abc") == -1) ; //returns -1 for negative numbers
        string look2[3] = {"abc", "Abc", "abc"} ;
        assert(lookup(look2, 0, "abc") == -1) ; //returns -1 for 0 bc doesn't check anything
        string look3[4] = {"abc", "Abc", "abc"} ;
        assert(lookup(look3, 3, "abc") == 0) ; //returns 0, lowest position first for multiple correct
        string look4[3] = {"Abc", "abc", "abc"} ;
        assert(lookup(look4, 3, "abc") == 1) ; //returns 1 and checks Abc != abc
        string look5[0] = {} ;
        assert(lookup(look5, 0, "abc") == -1) ; //returns 1 and checks Abc != abc
    }
    
    //positionofmax test cases
    {
        string max1[5] = {"abc", "abc", "bac", "Bac", "bac"} ;
        assert(positionOfMax(max1, -1) == -1) ;//returns -1 for negative numbers
        string max2[5] = {"abc", "abc", "bac", "Bac", "bac"} ;
        assert(positionOfMax(max2, 0) == -1) ;//returns -1 bc doesn't check anything
        string max3[5] = {"abc", "abc", "bac", "Bac", "bac"} ;
        assert(positionOfMax(max3, 5) == 2) ;//returns 2 bc bac > bac and returns lowest pos first
        string max4[0] = {};
        assert(positionOfMax(max4, 0) == -1) ;//returns -1 for empty set
    }
    
    //rotateleft test cases
    {
        string left1[4] = {"abc", "bca", "cba", "def"} ;
        assert(rotateLeft(left1, -1, 4) == -1) ; //returns -1 for negative n
        string left2[4] = {"abc", "bca", "cba", "def"} ;
        assert(rotateLeft(left2, 4, 5) == -1) ; //returns -1 for pos > n
        string left3[4] = {"abc", "bca", "cba", "def"} ;
        assert(rotateLeft(left3, 4, -1) == -1) ; //returns -1 for pos < 0
        string left4[4] = {"abc", "bca", "cba", "def"} ;
        assert(rotateLeft(left4, 4, 1) == 1 && left4[0] == "abc" && left4[1] == "cba" && left4[2] == "def" && left4[3]=="bca") ; //function works for normal cases
        string left5[0] = {} ;
        assert(rotateLeft(left5, 0, 0) == -1) ; //returns -1 for empty set
    }
    
    //countruns test cases
    {
        string count1[9] = {"a", "b", "c", "c", "d", "d", "d", "e", "e"} ;
        assert(countRuns(count1, -1) == -1); //returns -1 for negative numbers
        string count2[9] = {"a", "b", "c", "c", "d", "d", "d", "e", "e"} ;
        assert(countRuns(count2, 0) == 0); //returns 0 for 0
        string count3[9] = {"a", "b", "c", "c", "d", "d", "d", "e", "e"} ;
        assert(countRuns(count3, 9) == 5); //function works normally
        string count4[0] = {};
        assert(countRuns(count4, 0) == 0) ; //returns 0 for empty set
    }
    
    //flip test cases
    {
        string flip1[3] = {"abc", "def", "xyz"} ;
        assert(flip(flip1, -1) == -1 ); //returns -1 for negative n
        string flip2[3] = {"abc", "def", "xyz"} ;
        assert(flip(flip2, 0) == 0 && flip2[0] == "abc"); //returns 0 for 0 and nothing changes
        string flip3[3] = {"abc", "def", "xyz"} ;
        assert(flip(flip3, 3) == 3 && flip3[0] == "xyz" && flip3[1] == "def" && flip3[2] == "abc"); //works normally for odd arrays
        string flip4[4] = {"abc", "def", "xyz", "hic"} ;
        assert(flip(flip4, 4) == 4 && flip4[0] == "hic" && flip4[1] == "xyz" && flip4[2] == "def" && flip4[3] == "abc"); //works normally for even arrays
        string flip5[0] = {} ;
        assert(flip(flip5, 0) == 0) ;//works for empty set
    }
    
    //differ test cases
    {
        string folks1[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
        string group1[5] = { "betty", "john", "dianne", "", "xavier" };
        assert(differ(folks1, 6, group1, 5)==2);  // works normally
        string folks2[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
        string group2[5] = { "betty", "john", "dianne", "", "xavier" };
        assert(differ(folks2, 2, group2, 1) ==1);  // works if one runs out n2 < n1
        string folks3[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
        string group3[5] = { "betty", "john", "dianne", "", "xavier" };
        assert(differ(folks3, 1, group3, 2) ==1);  // works if one runs out n1 < n2
        string folks4[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
        string group4[5] = { "betty", "john", "dianne", "", "xavier" };
        assert(differ(folks4, 2, group4, 2) ==2);  // works if one runs out n2 == n1
        string folks5[0] = {};
        string group5[5] = { "betty", "john", "dianne", "", "xavier" };
        assert(differ(folks5, 0, group5, 2) ==0);  //returns 0 for empty set
        string folks6[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
        string group6[5] = { "betty", "john", "dianne", "", "xavier" };
        assert(differ(folks6, -5, group6, 2) ==-1);  // returns -1 for n1 < 0
        string folks7[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
        string group7[5] = { "betty", "john", "dianne", "", "xavier" };
        assert(differ(folks7, 2, group7, -1) ==-1);  // returns -1 for n2 <0
    }
    
    //subsequence test cases
    {
        string sub11[3] = {"abc", "def", "xyz"} ;
        string sub12[3] = {"def", "xyz"} ;
        assert(subsequence(sub11, 3, sub12, 2) == 1) ; //works normally
        string sub21[3] = {"abc", "def", "xyz"} ;
        string sub22[3] = {"def", "xyz"} ;
        assert(subsequence(sub21, -1, sub22, 2) == -1) ; //returns -1 for n1 < 0
        string sub31[3] = {"abc", "def", "xyz"} ;
        string sub32[3] = {"def", "xyz"} ;
        assert(subsequence(sub31, 3, sub32, -2) == -1) ; //returns -1 for n2 < 0
        string sub41[6] = {"abc", "def", "xyz", "abc", "def", "xyz"} ;
        string sub42[3] = {"def", "xyz"} ;
        assert(subsequence(sub41, 6, sub42, 2) == 1) ; //returns lowest pos for multiple
        string sub51[3] = {"abc", "def", "xyz"} ;
        string sub52[3] = {"ab", "de"} ;
        assert(subsequence(sub51, 3, sub52, 2) == -1) ; //returns -1 if can't find
        string sub61[3] = {"abc", "def", "xyz"} ;
        string sub62[0] = {} ;
        assert(subsequence(sub61, 3, sub62, 0) == 0) ; //works for empty set
        string sub71[0] = {} ;
        string sub72[0] = {} ;
        assert(subsequence(sub71, 0, sub72, 0) == 0) ; //works for empty set of empty set
        string sub81[3] = {"abc", "def", "xyz"} ;
        string sub82[4] = {"abc", "def", "xyz", "adf"} ;
        assert(subsequence(sub81, 3, sub82, 4) == -1) ; //returns -1 for n2 > n1
    }
    
    //lookupany test cases
    {
        string any11[3] = {"Abc", "abc", "abc"} ;
        string any12[3] = {"bed", "abc"} ;
        assert(lookupAny(any11, 3, any12, 2)==1) ; //returns lowest pos
        string any21[3] = {"Abc", "abc", "abc"} ;
        string any22[3] = {"bed", "abc"} ;
        assert(lookupAny(any21, -3, any22, 2)==-1) ; //returns -1 n1 < 0
        string any31[3] = {"Abc", "abc", "abc"} ;
        string any32[3] = {"bed", "abc"} ;
        assert(lookupAny(any31, 3, any32, -2)==-1) ; //returns -1 n2 < 0
        string any41[0] = {} ;
        string any42[3] = {"bed", "abc"} ;
        assert(lookupAny(any41, 0, any42, 2)==-1) ; //returns -1 for empty set
        string any51[1] = {"abc"} ;
        string any52[0] = {} ;
        assert(lookupAny(any51, 1, any52, 0)==-1) ; //returns -1 for empty set
        string any61[0] = {} ;
        string any62[0] = {} ;
        assert(lookupAny(any61, 0, any62, 0)==-1) ; //returns -1 for empty set
        string names[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
        string set1[10] = { "dianne", "betty", "greg", "gavin" };
        assert(lookupAny(names, 6, set1, 4)==1);  // returns 1 (a1 has "gavin" there)
        string set2[10] = { "xavier", "ed" };
        assert(lookupAny(names, 6, set2, 2)==-1);  // returns -1 (a1 has none)
    }
    
    //divide
    {
        string divide1[4] = {"bac", "cda", "def", "efg"} ;
        assert(divide(divide1, 4, "a") == 0) ; //returns n if none less
        string divide2[4] = {"bac", "cda", "def", "efg"} ;
        assert(divide(divide2, -4, "a") == -1) ; //returns -1 if negative n
        string divide3[4] = {"bac", "cda", "def", "efg"} ;
        assert(divide(divide3, 4, "dee") == 2) ; //works normally
        string divide4[0] = {} ;
        assert(divide(divide4, 0, "abc") == 0) ;//returns 0 for empty set
    }
    cout << "All test cases succeeded!" << endl ;
    return 0;
}
