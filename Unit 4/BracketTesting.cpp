#include <iostream>
#include "BracketCheck.h"

using namespace std;

bool check(string, string, bool);
bool numCheck(string, string, int);

int main()
{
    check("Easy", "()", true);
    check("Not Matched", "(}", false);
    check("Mixed but valid", "({}[])", true);
    check("Too Many Closing", "({}[])]", false);
    check("Not Matched", "({)(})", false);
    check("Too Many Opening", "{()", false);
    check("Code", "if (num == 7) { cout << num; }", true);
    check("Bad Code", "if (num == 7)  cout << num; }", false);

    numCheck("Easy", "()", 1);
    numCheck("Mixed but valid", "({}[])", 3);

    return 0;
}

bool check(string name, string expression, bool shouldBe){
    BracketCheck b(expression);
    if(shouldBe == b.isBalanced()){
        cout << "Passed: " << name << endl;
        return true;
    }
    else{
        cout << "Failed: " << name << " " << b << endl;
    }

    return false;
}

bool numCheck(string name, string expression, int should) {
    BracketCheck b(expression);
    if (should == b.numBrackets()) {
        cout << "Passed: " << name << endl;
        return true;
    }
    else {
        cout << "Failed: " << name << " Should be: " << should << ", was: " << b.numBrackets() << endl;
    }
    return false;
}
