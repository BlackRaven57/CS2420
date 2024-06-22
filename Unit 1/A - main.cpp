#include <iostream>
#include "A - Distance.h"
using namespace std;

int main() {
    Distance d1;
    cout << "Distance 1: " << d1 << endl;
    
    Distance d2(1, 15);
    cout << "Distance 2: " << d2 << endl;

    Distance d3(5);
    cout << "Distance 3: " << d3 << endl;

    cout << "Enter number of feet and inches for d1: ";
    cin >> d1;
    cout << "New Distance 1: " << d1 << endl;

    Distance d4 = d2 + d3;
    cout << "Distance 4: " << d4 << endl;

    Distance d5 = d4 - d1;
    cout << "Distance 5: " << d5 << endl;
}