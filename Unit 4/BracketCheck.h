#pragma once
#include <stack>
#include <queue>
using namespace std;

class BracketCheck {
    public:
    BracketCheck(string exp): expression(exp) {} 

    int numBrackets() const {
        int num = 0;
        for (char c: expression) {
            if (c == 40 || c == 41 || c == 91 || c == 93 || c == 123 || c == 125) {
                num++;
            }
        }
        num /= 2;
        return num;
    }

    bool isBalanced() const {
        bool bal = true;
        stack<char> brack;
        for (char c: expression) {
            // Starting 
            if (c == 40 || c == 91 || c == 123) {
                brack.push(c);
            }
            // Ending
            else if (c == 41 || c == 93 || c == 125) {
                // No unfinished brackets before
                if (brack.empty()) {
                    bal = false;
                    break;
                }
                // Correct Bracket
                if (c == 41) {
                    if (brack.top() != '(') {
                        bal = false;
                        break;
                    }
                    brack.pop();
                }
                else if (c == 93) {
                    if (brack.top() != '[') {
                        bal = false;
                        break;
                    }
                    brack.pop();
                }
                else if (c == 125) {
                    if (brack.top() != '{') {
                        bal = false;
                        break;
                    }
                    brack.pop();
                }
            }
        }

        // If there are any unfinshed brackets
        if (!brack.empty()) {
            bal = false;
        }
        return bal;
    }

    friend ostream& operator << (ostream& out, const BracketCheck& b) {
        if (b.isBalanced()) {
            out << "Balanced";
        }
        else {
            out << "Not Balanced";
        }
        return out;
    }

    private:
    string expression;
};