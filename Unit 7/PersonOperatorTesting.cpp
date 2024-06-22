#include <iostream>
#include "Person.h"
using namespace std;

int main() {
    Person bt("Bart", 10);
    Person hm("Homer", 42);
    Person mg("Marge", 42);

    // Comparing using >
    if (hm > bt) {
        cout << "Older: " << hm << endl;
        cout << "Younger: " << bt << endl << endl;;
    }
    
    // Comparing using <
    if (bt < mg) {
        cout << "Younger: " << bt << endl;
        cout << "Older: " << mg << endl << endl;
    }

    // Comparing using >=
    if (hm >= bt) {
        cout << "Greater than or Equal:" << endl;
        cout << hm << endl;
        cout << bt << endl << endl;
    }

    // Comparing using <=
    if (hm <= mg) {
        cout << "Less than or Equal:" << endl;
        cout << hm << endl;
        cout << mg << endl << endl;
    }

    // Comparing using ==
    if (hm == mg) {
        cout << "Same Age:" << endl;
        cout << hm << endl;
        cout << mg << endl << endl;
    }

    // Comparing using !=
    if (hm != bt) {
        cout << "Not Same Age:" << endl;
        cout << hm << endl;
        cout << bt << endl << endl;
    }

    // < with int
    if (bt < 21) {
		cout << bt << "  too young for Moes" << endl;
	} 

    // == with int
    if (hm == 42) {
        cout << "42 years old: " << hm << endl;
    }

    if (21 > bt) {
		cout << bt << " less than 21" << endl;
	}


}
