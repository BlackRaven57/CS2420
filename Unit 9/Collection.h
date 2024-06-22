#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

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
    virtual Collection<Item>& operator=(Collection<Item>& a);
    virtual Item& operator[](int ndx);


    virtual Collection<Item>& operator+(Item e) { add(e); return *this;}
    virtual Collection<Item>& operator-(Item e) { for(int i = 0; i < e; i++)removeEnd(); return *this;}
    virtual Collection<Item>& operator<<(Item e);
    friend ostream& operator<<(ostream& out, const Collection& c) {
        for (int i = 0; i < c.curSize; i++) {
            out << c.elements[i];
            if(i<c.curSize-1) out << " ";
        }
        return out;
    }
    void swap(int, int);
    void sortByBubble();
    void sortBySelection();
    void sortByInsertion();
    void sortByQuick() {
        quicksort(0, curSize-1);
    }
    void quicksort(int start, int end);
    int partition(int start, int end);
    Item findMinInRange(int start);

protected:
    int capacity;
    int minIndex;
    int curSize;
    std::unique_ptr<Item[]> elements;
    static const int INITIAL_CAPACITY = 8;
    void expand();
};

template<typename Item>
Collection<Item>::Collection() {
    capacity = INITIAL_CAPACITY;
    curSize = 0;
    elements=make_unique<Item[]>(capacity);
}

template<typename Item>
Collection<Item>::Collection(int size) {
    capacity = size;
    curSize = 0;
    elements = make_unique<Item[]>(capacity);
}

template<typename Item>
Collection<Item>::Collection(Collection<Item>& a) {
    capacity = a.capacity;
    curSize = a.curSize;
    elements = make_unique<Item[]>(capacity);
    for (int i = 0; i < a.curSize; i++) {
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
    if(curSize < 0){
        throw runtime_error("Empty List");
    }
}

template<typename Item>
Item& Collection<Item>::operator[](int ndx) {
    return elements[ndx];
}

template<typename Item>
Collection<Item>& Collection<Item>::operator=(Collection<Item>& a) {
    auto newElements = std::make_unique<Item[]>(a.capacity);
    for (int i = 0; i < a.curSize; i++){
        newElements[i] = a.elements[i];
    }
    elements = move(newElements);
    capacity = a.capacity;
    curSize = a.curSize;
    return *this;
}

template<typename Item>
Collection<Item>& Collection<Item>::operator<<(Item e) {
    add(e);
    return *this;
}

template<typename Item>
void Collection<Item>::expand() {
    auto newElements = std::make_unique<Item[]>(capacity * 2);
    for (int i = 0; i < capacity; i++) newElements[i] = elements[i];
    elements = std::move(newElements);
    capacity *= 2;
}

template<typename Item>
void Collection<Item>::swap(int first, int second) {
    Item temp = elements[first];
    elements[first] = elements[second];
    elements[second] = temp;
}

template<typename Item>
void Collection<Item>::sortByBubble() {
    for (int i = 0; i < curSize - 1; i++) {
        for (int j = 1; j < curSize - i; j++) {
            if (elements[j] < elements [j - 1]) {
                swap(j, j - 1);
            }
        }
    }
}

template<typename Item>
void Collection<Item>::sortByInsertion() {
    for (int i = 1; i < curSize; i++) {
        for (int j = i; j >=1 && elements[j] < elements[j - 1]; j--) {
            swap(j, j - 1);
        }
    }
}

template<typename Item>
int Collection<Item>::partition(int start, int end) {
    int pivot = start;
    Item toCompare = elements[start];
    for (int i = start + 1; i <= end; i++) {
        if (elements[i] < toCompare) {
            pivot++;
            swap(i, pivot);
        }
    }
    swap(pivot, start);
    return pivot;
}

template<typename Item>
void Collection<Item>::quicksort(int start, int end) {
    if (start >= end) {
        return;
    }
    int pivot = partition(start, end);
    quicksort(start, pivot - 1);
    quicksort(pivot + 1, end);
}

template<typename Item>
Item Collection<Item>::findMinInRange(int start) {
    Item min = elements[start];
    for (int i = start; i < curSize - i; i++) {
        if (elements[i] < min) {
            min = elements[i];
            minIndex = i;
        }
    }
    return min;
}

template<typename Item>
void Collection<Item>::sortBySelection() {
    Item min;
    Item temp;
    for (int i = 0; i < curSize; i++) {
        min = elements[i];
        minIndex = i;
        for (int j = i; j < curSize; j++) {
            if (elements[j] < min) {
                min = elements[j];
                minIndex = j;
            }
        }
        temp = elements[i];
        elements[i] = min;
        elements[minIndex] = temp;
    }
}





