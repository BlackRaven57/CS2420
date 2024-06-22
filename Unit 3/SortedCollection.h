#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include "Collection.h"
using namespace std;

template<typename Type>
class SortedCollection: private Collection<Type> {
  public:
  /*Create an additional overload operator for the + operator.
  This time we will use it to add an Item to the Collection class (and thus SortedCollection class).
  When implementing the operator, you are welcome to call the add method that has already been coded. */
  template<Type>
  void operator + (SortedCollection<Type> c, Type e) {
    c.add(e);
  }
  
  /*Create an additional overload operator for the << operator.
  This time we will use it to add and Item to the Collection class (and thus SortedCollection class).
  This will NOT be a friend function. Watch out, there will be different parameters than the operater<< used to display the object. 
  When implementing the operator, you are welcome to call the add method that has already been coded. */
  template<Type>
  void operator << (Type e) {
    this->add(e);
  }


  /*Overload the three constructors such that you can make a call to SortedCollection using no parameters, 
  a single int parameter to specify the max size, and with a parameter of another SortedCollection to start with a given collection. */
  template<typename Type>
  SortedCollection() {
    elements = make_unique<Type[]>(capacity);
    curSize = 0;
  }
  
  template<typename Type>
  SortedCollection(Type max) {
    elements = make_unique<Type[]>(max);
    curSize = max - 1;
  }

  template<typename Type>
  SortedCollection(SortedCollection<Type> s) {

  }

  /*Overload the add method such that it adds items in the correct order from lowest to highest. 
  For example, given a collection with the following values 2 5 9, add(3) would produce 2 3 5 9. 
  Do not use a sort algorithm, as that would have a quadratic efficiency.
  Instead use an insert algorithm, and push the item forward in the list to the correct position. This would give a linear algorithm. */

};