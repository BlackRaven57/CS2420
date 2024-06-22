#pragma once
#include <memory>
using namespace std;

class Subsequences {
    public:
    Subsequences(string w): word(w), max(w.length()) {}

    // Will return true if sub is a subsequence of the original word
    bool isSubsequence(string sub) {
        subString = sub;
        if (sub.empty() || sub == " ") {
            return false;
        }
        index = 0;
        for (char c: sub) {
            if (!isEqual(c, index)) {
                return false;
            }
        }
        return true;
    }

    bool isEqual(char c, int i) {
        if (i >= max) {
            return false;
        }
        if (c == word[i]) {
            index = i + 1;
            return true;
        }
        isEqual(c, i + 1);
    }

    // Such that information is given about the class.
    // This will be used for your own debugging
    friend ostream& operator << (ostream& out, const Subsequences& s) {
        out << "Word: " << s.word;
        out << "Subword: " << s.subString;
        return out;
    }

    private:
    string word;
    string subString;
    int index;
    int max;
};