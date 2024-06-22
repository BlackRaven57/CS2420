#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
using namespace std;

template<typename Item>
class Collection;

template<typename Item>
ostream& operator << (ostream&, const Collection<Item>& c);

template<typename Item>
class Collection {
public:
  Collection();
  Collection(int size);
  Collection(Collection<Item>& a);
  virtual int size();
  virtual Item get(int ndx) const;
  virtual void add(Item e);
  virtual void removeEnd();
  virtual Item operator [] (int ndx);
  virtual void operator - (int num);
  virtual Collection<Item>& operator = (Collection<Item>& a);
  friend ostream& operator<< <>(ostream&, const Collection& c);

protected:
  int capacity;
  int curSize;
  static const int INITIAL_CAPACITY = 8;
  virtual void expand();
  unique_ptr<Item[]> elements;

};

template<typename Item>
Collection<Item>::Collection(){
    capacity = INITIAL_CAPACITY;
    curSize = 0;
    elements = make_unique<Item[]>(capacity);
}

template<typename Item>
Collection<Item>::Collection(int size){
    capacity = size;
    curSize = 0;
}

template<typename Item>
Collection<Item>::Collection(Collection<Item>& a){
  capacity = a.capacity;
  curSize = a.curSize;
  elements = make_unique<Item[]>(capacity);
  for (int i = 0; i < curSize; i++) {
    elements[i] = a.elements[i];
  }
}

template<typename Item>
int Collection<Item>::size() {
  return curSize;
}

template<typename Item>
Item Collection<Item>::get(int ndx) const {
  return elements[ndx];
}

template<typename Item>
void Collection<Item>::add(Item e) {
    if (curSize == capacity) {
      expand();
    }
    elements[curSize] = e;
    curSize++;
}

template<typename Item>
void Collection<Item>::removeEnd() {
  curSize--;
  if (curSize < 0) {
    throw runtime_error("Empty List");
  }
}

template<typename Item>
void Collection<Item>::expand() {
  auto newElements = make_unique<Item[]>(capacity * 2);
  for (int i = 0; i < capacity; i++) {
    newElements[i] = elements[i];
  }
  elements = move(newElements);
  capacity *= 2;
}

template<typename Item>
Item Collection<Item>:: operator [] (int ndx) {
  return get(ndx);
}

template<typename Item>
void Collection<Item>:: operator - (int num) {
  for (int i = 0; i < num; i++) {
    removeEnd();
  }
}

template<typename Item>
Collection<Item>& Collection<Item>:: operator = (Collection<Item>& a) {
  auto newElements = make_unique<Item[]>(a.capacity);
  for (int i = 0; i < a.curSize; i++) {
    newElements[i] = a.elements[i];
  }
  elements = move(newElements);
  capacity = a.capacity;
  curSize = a.curSize;
  return *this;
}

template<typename Item>
ostream& operator << (ostream& out, const Collection<Item>& c) {
  for (int i =0; i < c.curSize; i++) {
    out << c.elements[i];
    if (i < c.curSize - 1) {
      out << " ";
    }
  }
  return out;
}

//// SORTED COLLECTION ////
template<typename Item>
class SortedCollection: public Collection<Item> {
  public:
  // + Operator
  SortedCollection<Item>& operator+ (Item e) {
    this->add(e);
    return *this;
  }
  
  // << Operator
  SortedCollection<Item>& operator << (Item e) {
    this->add(e);
    return *this;
  }

  SortedCollection<Item>() {
    this->capacity = this->INITIAL_CAPACITY;
    this->elements = make_unique<Item[]>(this->capacity);
    this->curSize = 0;
  }
  
  SortedCollection<Item>(int max) {
    this->capacity = max - 1;
    this->elements = make_unique<Item[]>(this->capacity);
    this->curSize = 0;
  }

  SortedCollection<Item>(const SortedCollection<Item>& s) {
    this->capacity = s.capacity;
    this->curSize = s.curSize;
    this->elements = make_unique<Item[]>(this->capacity);
    for (int i = 0; i < this->curSize; i++) {
      this->elements[i] = s.elements[i];
    }
  }

  void add(Item e) {
    // Expand capacity if it's not large enough
    if (this->curSize == this->capacity) {
      this->expand();
    }
    // Add to the list
    this->elements[this->curSize] = e;
    this->curSize++;
    // 
    for (int i = this->curSize - 1; i > 0; i--) {
      if (this->elements[i - 1] > this->elements[i]) {
        Item temp = this->elements[i];
        this->elements[i] = this->elements[i - 1];
        this->elements[i - 1] = temp;
      }
    }
  }

};
