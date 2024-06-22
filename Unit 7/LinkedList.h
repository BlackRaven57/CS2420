#pragma once
#include <iostream>
#include <memory>
using namespace std;

template<class Type>
struct Node {
    Type data;
    shared_ptr<Node<Type>> next;
};

template<class Type>
class LinkedList;

template<class Type>
ostream& operator << (ostream& out, const LinkedList<Type>& list);

template<class Type>
class LinkedList {
    public:
        LinkedList(): front(nullptr), back(nullptr), count(0) {}
        LinkedList(const LinkedList<Type> &lst);
        void insert(Type data);   //Adds to the back of the list
        Type peek(int ndx)const;  //Looks at an element at the given ndx value
        void remove(int ndx);     //Removes an element at the given ndx position
        void operator = (const LinkedList &l);
        friend ostream& operator << <>(ostream& out, const LinkedList<Type>& list);// Returns an output stream for displaying the LinkedList
        void pointerPractice(Type toInsert, Type toRemove);

    protected:
        shared_ptr <Node<Type>> front;
        shared_ptr <Node<Type>> back;
        int count;
};

template<class Type>
LinkedList<Type>::LinkedList(const LinkedList<Type> &lst) {
    auto temp = lst.front;
    for (int i = 0; i < lst.count; i++) {
      insert(temp->data);
      temp = temp->next;
    }
}

template<class Type>
void LinkedList<Type>::operator = (const LinkedList<Type> &l) {
    auto temp = l.front;
    for (int i = 0; i < l.count; i++) {
      insert(temp->data);
      temp = temp->next;
    }
}

template<class Type>
void LinkedList<Type>::insert(Type data) {
    auto temp = make_shared<Node<Type>>();
    temp->data = data;
    temp->next = nullptr;
    if (!front) {
        front = temp;
        back = temp;
    }
    else {
        back->next = temp;
        back = temp;
    }
    count++;
}

template<class Type>
Type LinkedList<Type>::peek(int ndx)const {
    if (ndx >= count || ndx < 0) {
        throw runtime_error("Out of range");
    }
    int currNodeNum = 0;
    auto currentNode = front;
    while (currNodeNum < ndx) {
        currNodeNum++;
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

template<class Type>
void LinkedList<Type>::remove(int ndx) {
    if (ndx >= count || ndx < 0) {
        throw runtime_error("Out of range");
    }
    // Deleting the front
    if (ndx = 0) {
        auto toDelete = front;
        front = toDelete->next;
        return;
    }
    // Deleting others
    int currNodeNum = 0;
    auto currentNode = front;
    while (currNodeNum < ndx - 1) {
        currNodeNum++;
        currentNode = currentNode->next;
    }
    auto toDelete = currentNode->next;
    if (toDelete->next) {
        currentNode->next = toDelete->next;
    }
    // Deleting Last Node
    else{
        currentNode->next = nullptr;
        back = currentNode;
    }
    count--;
}

template<class Type>
ostream& operator << (ostream& out, const LinkedList<Type>& list) {
    auto curr = list.front;
    while (curr) {
        out << curr->data;
        if (curr->next) {
            out << " ";
        }
        curr = curr->next;
    }
    return out;
}

template<class Type>
void LinkedList<Type>::pointerPractice(Type toInsert, Type toRemove) {
	auto newNode = make_shared<Node<Type>>();
	newNode->data = toInsert;
    auto curr = front;
    int currNum = 0;
    while (currNum < 2) {
        curr = curr->next;
        currNum++;
    }
    cout << curr->data;
    newNode->next = curr->next;
    curr->next = newNode;
    while (currNum < 4) {
        curr = curr->next;
        currNum++;
    }
    cout << curr->data;
    auto temp = curr->next->next;
    curr->next = temp;
}
