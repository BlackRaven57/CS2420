#pragma once
#include <memory>
#include "LinkedList.h"
using namespace std;

// template<class T>
// struct Node {
//     LinkedList* data;
//     shared_ptr<Node>* next
// };

template<class T>
class FifthElement: public LinkedList<T>{
    public:
    // Returns the data at the fifth node
    T getFifthElement() {
        int currNodeNum = 0;
        auto currentNode = this->front;
        while (currNodeNum < 4) {
            if (!currentNode->next) {
                throw runtime_error("No Fifth Node");
            }
            currNodeNum++;
            currentNode = currentNode->next;
        }
        return currentNode->data;
    }

    // Inserts a node between 4 and 5 node.
    void insertNewFifthElement(const T& value) {
        int currNodeNum = 0;
        auto currentNode = this->front;
        auto temp = make_shared<Node<T>>();
        temp->data = value;
        temp->next = nullptr;;
        while (currNodeNum < 3) {
            if (!currentNode->next) {
                throw runtime_error("Out of Range");
            }
            currNodeNum++;
            currentNode = currentNode->next;
        }
        // More than 4 elements
        if (currentNode->next) {
            temp->next = currentNode->next;
            currentNode->next = temp;
        }
        // Only 4 elements, temp becomes back
        else {
            currentNode->next = temp;
            this->back = temp;
        }
    }

    // Deletes Fifth Node
    void deleteFifthElement() {
        int currNodeNum = 0;
        auto currentNode = this->front;
        while (currNodeNum < 3) {
            if (!currentNode->next) {
                throw runtime_error("Out of Range");
            }
            currNodeNum++;
            currentNode = currentNode->next;
        }
        auto tempFifth = currentNode->next;
        // At least 6 elements
        if (tempFifth->next) {
            currentNode->next = tempFifth->next;
        }
        // Only 5 elements, just deletes the back
        else {
            this->back = currentNode;
            currentNode->next = nullptr;
        }
    }

    // Rearranges the 4th and 5th nodes
    void swapFourthAndFifthElement() {
        int currNodeNum = 0;
        auto currentNode = this->front;
        while (currNodeNum < 2) {
            if (!currentNode->next) {
                throw runtime_error("Out of Range");
            }
            currNodeNum++;
            currentNode = currentNode->next;
        }
        // auto tempThird = currentNode;
        auto newFifth = currentNode->next;
        currentNode->next = newFifth->next;
        auto newFourth = currentNode->next;
        newFifth->next = newFourth->next;
        currentNode->next->next = newFifth;
    }
};