#include <iostream>
using namespace std;
bool isPalindrome(string word, int first, int last) {
    //TODO: Complete the recursive method to test true for a palindrome
    if (word.at(first) == word.at(last)) {
        if ((first == last) || (first + last == word.length())) {
            return true;
        }
        else {
            isPalindrome(word, first + 1, last - 1);
        }
    }
    else {
        return false;
    }
}

//Facilitate Recursive method call
bool isPalindrome(string word) {
    return isPalindrome(word, 0, word.length() - 1);
}

int main() {
    string words[] = {"madam", "palindrome", "racecar"};
    for(int i = 0; i < 3; i++){
       cout << words[i] << ": " << (isPalindrome(words[i]) ? "Palindrome\n": "Not\n");
    }
	return 0;
}
