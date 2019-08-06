//
//  main.cpp
//  rental
//
//  Created by Lucas Xia on 10/10/18.
//  Copyright © 2018 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    int start, end, days, month, miles;
    string name, lux;
    double ans = 0;
    cout << "Odometer at start: ";
    //requesting input
    cin >> start;
    //handles incorrect input
    if (start < 0) {
        cout << "---" << endl;
        cout << "The starting odometer reading must be nonnegative." << endl;
        return 0;
    }
    cout << "Odometer at end: ";
    //requesting input
    cin >> end;
    //handles incorrect input
    if (end < start) {
        cout << "---" << endl;
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
        return 0;
    }
    cout << "Rental days: ";
    //requesting input
    cin >> days;
    //handles incorrect input
    if (days <= 0) {
        cout << "---" << endl;
        cout << "The number of rental days must be positive." << endl;
        return 0;
    }
    cout << "Customer name: ";
    //removes the endl that is stored in the program because of previous use of cin>>integer
    getline(cin, name);
    //requesting input
    getline(cin, name);
    //handles incorrect input
    if (name == "") {
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 0;
    }
    cout << "Luxury car? (y/n): ";
    //requesting input
    getline(cin, lux);
    //handles incorrect input
    if (lux != "y" && lux != "n") {
        cout << "---" << endl;
        cout << "You must enter y or n." << endl;
        return 0;
    }
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    //requesting input
    cin >> month;
    //handles incorrect input
    if (month < 1 || month > 12) {
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;
        return 0;
    }
    //calculates total number of miles
    miles = end - start;
    // calculates base charge for car based on luxury or not
    if (lux == "y") ans += days * 61;
    else ans += days * 33;
    //this section calculates charge for each mile
    ans += 0.27 * min(miles, 100); // for first 100 or less miles
    miles -= 100; // these 100 miles are counted already
    if (miles > 0) { // if there are still miles left, we must add those in
        if (month == 12 || (month >= 1 && month <= 3)) ans += 0.27 * min(miles, 300); // based on starting date, the cost changes for the next 300 miles or less
        else ans += 0.21 * min(miles, 300);
    }
    miles -= 300; //the 300 of less miles are counted already
    if (miles > 0) ans += 0.19 * miles; // if there still are unaccounted miles, add the remaining number to the cost
    //sets the number of decimal places to exactly 2 for the cost
    cout.precision(2);
    cout.setf(ios::fixed);
    cout << "---" << endl;
    cout << "The rental charge for " << name << " is $" << ans << endl; //final printing
    return 0;
}
