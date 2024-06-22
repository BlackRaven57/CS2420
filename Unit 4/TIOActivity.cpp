#include <iostream>
#include <stack>
#include <queue>
using namespace std;


int main() {
    //Stack Code
    stack<int>myStack;
    queue<int>myQueue;
    for(int i = 10; i < 100; i+= 10 ){
        myStack.push(i);
        myQueue.push(i);
    }
    cout << "Stack top: " << myStack.top() << endl;
    cout << "Queue Front: " << myQueue.front() << endl;
    cout << "Stack size: " << myStack.size() << endl;
    cout << "Queue size: " << myQueue.size() << endl;

    myQueue.pop();
    myStack.pop();
    cout << "Stack top: " << myStack.top() << endl;
    cout << "Queue Front: " << myQueue.front() << endl;

    while (!myQueue.empty()) {
        myQueue.pop();
    }

    while (!myStack.empty()) {
        myQueue.push(myStack.top());
        myStack.pop();
    }
    cout << "Queue Front: " << myQueue.front() << endl;
    cout << "Queue Back: " << myQueue.back() << endl;
}
