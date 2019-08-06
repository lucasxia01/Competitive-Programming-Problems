#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>

#include "Set.h"

using namespace std;

bool higher(char top, char ch) {
    if ((top == '!' && ch != '!') || (top == '&' && ch != '!') || (top == '|' && ch == '|')) return true;
    return false;
}

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
    // Evaluate a boolean expression
    //   If infix is a syntactically valid infix boolean expression whose
    //   only operands are single lower case letters (whether or not they
    //   appear in the values sets), then postfix is set to the postfix
    //   form of the expression.  If not, postfix might or might not be
    //   changed, result is unchanged, and the function returns 1.
    //
    //   If infix is a syntactically valid infix boolean expression whose
    //   only operands are single lower case letters:
    //
    //      If every operand letter in the expression appears in either
    //      trueValues or falseValues but not both, then result is set to the
    //      result of evaluating the expression (using for each letter in the
    //      expression the value true if that letter appears in trueValues or
    //      false if that letter appears in false values) and the function
    //      returns 0.
    //
    //      Otherwise, result is unchanged and the value the function returns
    //      depends on these two conditions:
    //        at least one letter in the expression is in neither the
    //            trueValues nor the falseValues sets; and
    //        at least one letter in the expression is in both the
    //            trueValues and the falseValues set.
    //      If only the first condition holds, the function returns 2; if
    //      only the second holds, the function returns 3.  If both hold
    //      the function returns either 2 or 3 (and the function is not
    //      required to return the same one if called another time with the
    //      same arguments).
    stack<char> s;
    postfix = "";
    string ok = " ()!&|";
    string op = "!&|";
    string op2 = "&|";
    string notokafternot = ")&|";
    // check if valid infix
    int ret = 0;
    for (int i = 0; i < infix.length(); i++)
        if (infix[i] == ' ') infix = infix.substr(0, i) + infix.substr(i + 1);
    
    for (int i = 0; i < infix.length(); i++) {
        if (ok.find(infix[i]) != -1) {
            if (op2.find(infix[i]) != -1 && i > 0 && infix[i - 1] == '(') return 1;
            if (op.find(infix[i]) != -1 && i < infix.length() - 1 && infix[i + 1] == ')') return 1;
            if (infix[i] == '(' && i < infix.length() - 1 && infix[i + 1] == ')') return 1;
            if (op.find(infix[i]) != -1 && i == infix.length() - 1) return 1;
            if (infix[i] == '!' && i < infix.length() - 1 && notokafternot.find(infix[i + 1]) != -1) return 1;
            continue;
        } else if (infix[i] > 'z' || infix[i] < 'a') return 1;
        int a = trueValues.contains(infix[i]);
        int b = falseValues.contains(infix[i]);
        if (a + b == 0) ret = 2;
        else if (a + b == 2) ret = 3;
    }
    for (int i = 0; i < infix.length(); i++) {
        switch(infix[i]) {
            case ' ': continue;
            case '(': s.push('('); break;
            case ')':
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                if (s.empty()) return 1;
                s.pop();
                break;
            case '!':
            case '&':
            case '|':
                if (!s.empty() && s.top() == '(') {
                    s.push(infix[i]);
                    break;
                }
                while (!s.empty() && higher(s.top(), infix[i])) {
                    postfix += s.top();
                    s.pop();
                }
                s.push(infix[i]);
                break;
            default: postfix += infix[i];
        }
    }
    while (!s.empty()) {
        if (s.top() == '(') return 1;
        postfix += s.top();
        s.pop();
    }
    cout << postfix << endl;
    // postfix evaluation
    char v1, v2;
    for (int i = 0; i < postfix.length(); i++) {
        if (postfix[i] == '!') {
            if (s.empty()) return 1;
            v1 = s.top(); s.pop();
            s.push(!v1);
        } else if (postfix[i] == '&'){
            if (s.size() < 2) return 1;
            v2 = s.top(); s.pop();
            v1 = s.top(); s.pop();
            s.push(v1&v2);
        } else if (postfix[i] == '|'){
            if (s.size() < 2) return 1;
            v2 = s.top(); s.pop();
            v1 = s.top(); s.pop();
            s.push(v1|v2);
        } else s.push(trueValues.contains(postfix[i]));
    }
    if (s.size() != 1) return 1;
    if (ret == 0) {
        result = s.top(); s.pop();
    }
    return ret;
}

int main()
{
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    
    string pf;
    bool answer;
    
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("y()", trues, falses, pf, answer) == 1);
    assert(evaluate("!()", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("( )", trues, falses, pf, answer) == 1);
    assert(evaluate("( )))))((((", trues, falses, pf, answer) == 1);
    assert(evaluate("(y &      w)!", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("n!&t", trues, falses, pf, answer) == 1);
    assert(evaluate("(f!)f", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("5", trues, falses, pf, answer) == 1);
    assert(evaluate("!!!!!!!", trues, falses, pf, answer) == 1);
    assert(evaluate(")!f(", trues, falses, pf, answer) == 1);
    assert(evaluate(")(", trues, falses, pf, answer) == 1);
    assert(evaluate("(t)!", trues, falses, pf, answer) == 1);
    assert(evaluate("(f!())", trues, falses, pf, answer) == 1);
    assert(evaluate("t!(f)&", trues, falses, pf, answer) == 1);
    assert(evaluate("t!|!f", trues, falses, pf, answer) == 1);
    assert(evaluate("wtf", trues, falses, pf, answer) == 1);
    assert(evaluate("(!!!!(!!!!f)!)", trues, falses, pf, answer) == 1);
    assert(evaluate("tf&!t", trues, falses, pf, answer) == 1);
    assert(evaluate("f(|!f)", trues, falses, pf, answer) == 1);
    assert(evaluate("(!f|)f", trues, falses, pf, answer) == 1);
    assert(evaluate("!()f", trues, falses, pf, answer) == 1);
    assert(evaluate("!)(f", trues, falses, pf, answer) == 1);
    assert(evaluate("!(!)f", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&)t", trues, falses, pf, answer) == 1);
    assert(evaluate("t(!|!)t", trues, falses, pf, answer) == 1);
    assert(evaluate("(f) !& t", trues, falses, pf, answer) == 1);
    assert(evaluate("(t", trues, falses, pf, answer) == 1);
    assert(evaluate("y!&!!t", trues, falses, pf, answer) == 1);
    
    assert(evaluate("t|!!!f&!y", trues, falses, pf, answer) == 0 && pf == "tf!!!y!&|" && answer);
    assert(evaluate("(t|!!!f)&!y", trues, falses, pf, answer) == 0);
    assert(evaluate("t|(f|!t|f)", trues, falses, pf, answer) == 0);
    assert(evaluate("!(f & t) | !(f | t) ", trues, falses, pf, answer) == 0);
    assert(evaluate("!t|!(!(f))", trues, falses, pf, answer) == 0 && pf == "t!f!!|" && !answer);
    assert(evaluate("!!!!!!!f", trues, falses, pf, answer) == 0);
    assert(evaluate("!!!!!f|t", trues, falses, pf, answer) == 0);
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("!((x))", trues, falses, pf, answer) == 0  &&  pf == "x!"  &&  !answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    assert(evaluate("t&!(f|y&w|n)|!!!(f&y&n)", trues, falses, pf, answer) == 0 && pf == "tfyw&|n|!&fy&n&!!!|" && answer);
    
    cout << "Passed all tests" << endl;
}
