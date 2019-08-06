#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool isValidUppercaseStateCode(string stateCode) { // checks if string is a valid state code
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
char toU(char c) { if (c >= 'a' && c <= 'z') c += 'A' - 'a'; return c;} // changes lowercase letter to uppercase
bool isL(char c) { return (c >= 'A' && c <= 'Z');} // checks if char is letter
bool isN(char c) { return (c >= '0' && c <= '9');} // checks if char is digit
string allUpper(string s) { for (int i = 0; i < s.length(); i++) s[i] = toU(s[i]); return s;} // changes string to all uppercase

bool isPartyResult(string s) { //checks if a string is a party result
    //if (s.length() == 0) return true;
    if (s.length() < 2 || s.length() > 3) return false;
    if (s.length() == 2) return (isN(s[0]) && isL(s[1]));
    else return (isN(s[0]) && isN(s[1]) && isL(s[2]));
}
bool isStateForecast(string s) { // checks if a string is a stateforecast
    if (s.length() < 2) return false;
    if (!isValidUppercaseStateCode(s.substr(0, 2))) return false; // check first 2 characters for statecode
    for (int i = 2; i < s.length(); i++) {
        if (s.length() - i < 2) return false;
        if (isPartyResult(s.substr(i, 2))) i++; // check next two chars for party result
        else if (i <= s.length() - 3 && isPartyResult(s.substr(i, 3))) i += 2; //check next 3 chars for party result
        else return false;
    }
    return true;
}

bool hasProperSyntax(string pollData) { // checks if string is valid poll data string
    if (pollData.length() == 0) return true; // check if empty string
    pollData = allUpper(pollData); // change to all upper for consistency
    string s = "";
    for (int i = 0; i <= pollData.length(); i++) {
        if (i == pollData.length() || pollData[i] == ',') { // if end of string or comma, check
            if (!isStateForecast(s)) return false; // check if string is state forecast
            s = ""; // reset string for new state forecast
            continue; // skip the comma
        }
        s += pollData[i]; // add to string when not comma
    }
    return true; // if nothing is wrong, it is true
}

int tallySeats(string pollData, char party, int& seatTally) { // tallies seats for a party
    pollData = allUpper(pollData); // consistent uppercase
    if(!hasProperSyntax(pollData)) return 1; // return 1 if invalid string
    if (party >= 'a' && party <= 'z') party += 'A' - 'a'; //convert party to uppercase
    if (!isL(party)) return 2; // if not a letter, return 2
    seatTally = 0; // set seatTally to 0 in case it was not reset
    for (int i = 0; i < pollData.length(); i++) {
        if (pollData[i] == party && i > 0) { //find every iteration of the party letter
            if (!isN(pollData[i - 1])) continue; // if not preceded by number, don't use it
            seatTally += (pollData[i - 1] - '0'); // add the digit before it
            if (i > 1 && isN(pollData[i - 2])) seatTally += 10 * (pollData[i - 2] - '0'); // if it is 2 digits long, add 10 times the first digit
        }
    }
    return 0; // no error so return 0;
}

int main() { // this is just testing stuff :)
    assert(hasProperSyntax("MA9D,KS4R")  &&  hasProperSyntax("KS4R,MA9D"));
    assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D"));
    assert(hasProperSyntax("") && !hasProperSyntax(",") && !hasProperSyntax(",hi,") && !hasProperSyntax("hi,,ak") && hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D") && !hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"));
    string s;
    char c;
    int count = -1;
    cout << "Enter a poll data string: ";
    getline(cin, s);
    if (!hasProperSyntax(s)) {
        cout << "Bad string" << endl;
        return 0;
    }
    cout << "Good string" << endl;
    cout << "Enter a party letter: ";
    cin >> c;
    cout << tallySeats(s, c, count) << " " << count << endl;
    return 0;
}
