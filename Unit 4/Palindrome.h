#pragma once
#include <stack>
#include <queue>
using namespace std;

class Palindrome {
    public:
    Palindrome(string sent): sentence(sent) {}

    bool isPalindrome() const {
        bool b = true;
        string clean = stripSentence();
        stack<char> s;
        queue<char> q;
        for (char c: clean) {
            s.push(c);
            q.push(c);
        }
        while(!s.empty()) {
            if(s.top() != q.front()) {
                b = false;
                break;
            }
            s.pop();
            q.pop();
        }
        return b;
    }

    friend ostream& operator << (ostream& out, const Palindrome& p) {
        out << p.sentence << " is ";
        if (!p.isPalindrome()) {
            out << "not ";
        }
        out << "a palindrome";
        return out;
    }

    private:
    string sentence;
    string stripSentence() const {
        string clean = "";
        for (char c: sentence) {
            c = tolower(c);
            if (c >= 'a' && c <= 'z') {
                clean += c;
            }
        }
        return clean;
    }
};