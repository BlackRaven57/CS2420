#include "LinkedList.h"
using namespace std;

int main() {
    // List 1
    LinkedList<int> one;
    one.insert(1);


    // List 2
    LinkedList<int> two = one;
    two.insert(42);


    // List 3
    LinkedList<int> three = one;
    three.insert(60);


    // Display both Lists
    cout << one << endl;
    cout << two << endl;
    cout << three << endl;
}