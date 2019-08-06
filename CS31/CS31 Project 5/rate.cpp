#include <iostream>
#include <cstring>
#include <cmath>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 250;

char toLower(char c) { return c + 'a' - 'A';} // char to lower
char isL(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');} // checks if letter
char isU(char c) { return (c >= 'A' && c <= 'Z');} // checks if upper

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns) {
    int nGood = 0; // counts number of correct patterns
    char temp[MAX_WORD_LENGTH + 1];
    for (int i = 0; i < nPatterns; i++) {
        if (separation[i] < 0 || strlen(word1[i]) == 0 || strlen(word2[i]) == 0) separation[i] = -1; // make it invalid for edge cases
        for (int j = 0; j < strlen(word1[i]); j++) {
            if (!isL(word1[i][j])) { // if word contains non letter
                separation[i] = -1; // make it invalid
                break;
            } else if (isU(word1[i][j])) word1[i][j] = toLower(word1[i][j]); // convert everything to lowercase
        }
        for (int j = 0; j < strlen(word2[i]); j++) { // does same thing as above loop but to word2
            if (!isL(word2[i][j])) {
                separation[i] = -1;
                break;
            } else if (isU(word2[i][j])) word2[i][j] = toLower(word2[i][j]);
        }
    }
    for (int i = 0; i < nPatterns; i++) {
        int maxSep = separation[i]; // keep track of maximum separation
        for (int k = i + 1; k < nPatterns; k++) { // looks for repeat patterns
            if ((strcmp(word1[i], word1[k]) == 0 && strcmp(word2[i], word2[k]) == 0) || (strcmp(word1[i], word2[k]) == 0 && strcmp(word2[i], word1[k]) == 0)) {
                if (maxSep < separation[k]) {
                    maxSep = separation[k]; // update max separation
                }
                separation[k] = -1; // set them temporarily to invalid
            }
        }
        separation[i] = maxSep; // set current one to all the best values
        strcpy(temp, word1[i]);
        strcpy(word1[nGood], temp);
        strcpy(temp, word2[i]);
        strcpy(word2[nGood], temp);
        separation[nGood] = separation[i];
        if (separation[i] >= 0) nGood++; // update number of good
    }
    return nGood;
}

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns) {
    int ans = 0;
    bool good = false;
    char document1[MAX_DOC_LENGTH + 1]; // stores all the good words
    int id = 0;
    for (int i = 0; i < strlen(document); i++) {
        if (isU(document[i])) document1[id] = toLower(document[i]); // change to lower
        else if (isL(document[i]) || document[i] == ' ') document1[id] = document[i]; // copy if fine
        else id--; // if not good, don't update index of pointer
        id++;
    }
    document1[id] = '\0'; // change last value to null terminator
    char doc[MAX_DOC_LENGTH + 1][MAX_DOC_LENGTH + 1]; // stores word by word
    char temp[MAX_DOC_LENGTH + 1] = {}; // temp word
    int wordCount = 0;
    int position = 0;
    for (int i = 0; i <= strlen(document1); i++) {
        if (i == strlen(document1) || (document1[i] == ' ')) { // if space
            if (i > 0 && document1[i - 1] == ' ') continue; // if not repeat space
            temp[position] = '\0'; // end the temp word
            strcpy(doc[wordCount], temp); // copy to doc
            wordCount++; // update word count
            memset(temp, 0, MAX_DOC_LENGTH * sizeof(char)); // reset temp
            position = 0; //reset position
        } else {
            temp[position] = document1[i]; // update temp for good letter
            position++;
        }
    }
    for (int i = 0; i < nPatterns; i++) { // for each patter
        good = false;
        for (int f = 0; f < wordCount; f++) { // check first word
            for (int e = 0; e < wordCount; e++) { // check second word
                if (e == f) continue;
                if (strcmp(word1[i], doc[f]) == 0 && strcmp(word2[i], doc[e]) == 0 && separation[i] + 1 >= abs(e - f)) good = true; // check if valid patterm
            }
        }
        if (good) ans++; // update answer
    }
    return ans;
}

int main() { // testing
    /*Test 1 is the very basics to ensure that the program can correctly count basic patterns and that
     
     it can remove basic incorrect patterns. It also ensures that the program can ignore unnecessary characters
     
     and unnecessary capitalizations*/
    const int TEST14 = 8;
    char t1[TEST14][MAX_WORD_LENGTH+1] = {"hi", "hi", "hi", "bye", "bye", "hi", "hi", "bye"};
    char t2[TEST14][MAX_WORD_LENGTH+1] = {"hi", "hi", "hi", "bye", "bye", "hi", "hi", "bye"};
    int t3[TEST14] = {14, -1, -1, 14, 2, -1, -1, 14};
    int x = makeProper(t1, t2, t3, TEST14);
    
    for (int i = 0; i < x; i++) {
        cout << t1[i] << " " << t2[i] << " " << t3[i] << endl;
    }
    const int TEST1_NRULES = 5;
    
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"mAd","deraNged","half-witted","nefarious","have"};
    
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"scientist","robot","SCIENTIST","Plot","mad"};
    
    int test1dist[TEST1_NRULES] = {1,3,9,0,12};
    
    assert(makeProper(test1w1,test1w2,test1dist,TEST1_NRULES)==4);
    
    assert(rate("The mad UCLA scientist***%^&*( unleashed a deranged evil giant robot.",
                
                test1w1, test1w2, test1dist, 4)==2);
    
    assert(rate("The mad UCLA scientist unleashed  [][]  a deranged robot.",
                
                test1w1, test1w2, test1dist, 4) == 2);
    
    assert(rate("** 2018 **",
                
                test1w1, test1w2, test1dist, 4) == 0);
    
    assert(rate("  That plot: NEF%^&*ARIO^&*(US!",
                
                test1w1, test1w2, test1dist, 4) == 1);
    
    assert(rate("deran!@#$%^ged deranged    robo#$%^&*t deranged robot robot",
                
                test1w1, test1w2, test1dist, 4) == 1);
    
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                
                test1w1, test1w2, test1dist, 4) == 0);
    
    assert(rate("mad", test1w1, test1w2, test1dist, 4) == 0);
    
    
    
    /*Test 2 tests what test1 does, but it also tests to ensure that negative separations are removed.
     
     It ensures that empty c-strings are removed from the patterns.
     
     It checks to make sure strings like "urer" and "ation" aren't counted when the words "surer" and "foundation"
     
     are in the document.
     
     It ensures that if the two words are the same in the pattern that it's not counted when only one of the words
     
     is present. (w1: there, w2: there, and there's only one "there" in the document.)*/
    
    const int TEST2=9;
    
    char test2w1[TEST2][MAX_WORD_LENGTH+1]={"fOr","TASTE","uRer","MuTual","is","THERE","There","","THAN"};
    
    char test2w2[TEST2][MAX_WORD_LENGTH+1]={"is","in","ation","literature","for","There","is","beautiful","LITERATURE"};
    
    int test2sep[TEST2]={20,-3,2,5,2,0,0,1,4};
    
    int test2count=makeProper(test2w1,test2w2,test2sep,TEST2);
    
    assert(test2count==6);
    
    assert(rate("    There is no surer foundation for a**** beautifu&**())l    friendship than a    mutual 374250942 taste i48294n literature.  ",
                
                test2w1,test2w2,test2sep,test2count)==4);
    
    
    
    /*This one makes sure that when word1 and word2 are the same, that it can still properly count the pattern when appropriate.
     
     It also makes sure that there's no errors when word2 is found in the document before word1. It also makes sure that makeProper can remove patterns on the edges of the arrays without errors.*/
    
    const int TEST3=10;
    
    char test3w1[TEST3][MAX_WORD_LENGTH+1]={"it's","BOOKS","world","that","the","SHAME","are","BOOKS","shame","books"};
    
    char test3w2[TEST3][MAX_WORD_LENGTH+1]={"own","books","world","that","the","world","callS","the","own","books"};
    
    int test3sep[TEST3]={2,6,6,6,100,3,0,0,0,5};
    
    int test3count=makeProper(test3w1,test3w2,test3sep,TEST3);
    
    assert(test3count==8);
    
    assert(rate("     The books t__hat the world calls i9mmoral are boo00ks that sho*w the world its own shame !!!!!! x",
                
                test3w1,test3w2,test3sep,test3count));
    
    
    
    /*this is to make sure that when there are repeat patterns, the right ones are removed and removed correctly.*/
    
    const int TEST4=5;
    
    char test4w1[TEST4][MAX_WORD_LENGTH+1]={"nope","nope","nope","nope","nope"};
    
    char test4w2[TEST4][MAX_WORD_LENGTH+1]={"nope","nope","nope","nope","nope"};
    
    int test4sep[TEST4]={5,4,3,2,1};
    
    int test4count=makeProper(test4w1,test4w2,test4sep, TEST4);
    
    assert(test4count==1);
    
    assert(test4sep[0]==5);
    {
        const int OWN_TEST_CASES = 7;
        char word5[OWN_TEST_CASES][MAX_WORD_LENGTH + 1] = {
            "cat", "polar", "i", "coding", "same", "twentyletterslongabc", "useless"
        };
        char word6[OWN_TEST_CASES][MAX_WORD_LENGTH + 1] = {
            "dog", "bear", "love", "fun", "same", "jeez", "testcase"
        };
        int separation3[OWN_TEST_CASES] = {
            0, 500, 1, 3, 5, 10, 10
        };
        assert(rate("same", word5, word6, separation3, OWN_TEST_CASES) == 0) ;
        assert(rate("same same ", word5, word6, separation3, OWN_TEST_CASES) == 1) ;
        assert(rate("dog cat ", word5, word6, separation3, OWN_TEST_CASES) == 1) ;
        assert(rate("twentyletterslongabc why twenty though jeez", word5, word6, separation3, OWN_TEST_CASES) == 1) ;
        assert(rate("i really love ", word5, word6, separation3, OWN_TEST_CASES) == 1) ;
        assert(rate("i really dont love ", word5, word6, separation3, OWN_TEST_CASES) == 0) ;
        assert(rate("polar dog cat same i hate love same useless coding is fun bear twentyletterslongabc why twenty though jeez", word5, word6, separation3, OWN_TEST_CASES) == 6) ;
    }
    cout << "All tests succeeded" << endl;
    return 0;
}
