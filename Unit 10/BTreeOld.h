#include <iostream>
#include <memory>
using namespace std;

template <typename T>
struct Node {
  Node(T d): data(d), left(nullptr), right (nullptr) {}
  T data;
  shared_ptr<Node<T>> left;
  shared_ptr<Node<T>> right;
};

template <typename T>
class BTree {
public:
  BTree(): root(nullptr) {}
  BTree(const BTree<T>& b);
  BTree<T>& operator= (const BTree<T>&);
  void insert(const T& item);
  void remove(const T& item);
  void preOrder();
  void inOrder();
  void postOrder();
  int nodeCount();
  int leavesCount();


private:
  shared_ptr<Node<T>> copyNode(shared_ptr<Node<T>> ptr);
  void insert(const T& item, shared_ptr<Node<T>> ptr);
  void preOrder(shared_ptr<Node<T>> ptr);
  void inOrder(shared_ptr<Node<T>> ptr);
  void postOrder(shared_ptr<Node<T>> ptr);
  int nodeCount(shared_ptr<Node<T>> ptr);
  int leavesCount(shared_ptr<Node<T>> ptr);
  
  shared_ptr<Node<T>> root;
};

// Copy Constructor
template <typename T>
BTree<T>::BTree(const BTree<T>& b) {
  root = copyNode(b.root);
}
  
// Equal Operator
template <typename T>
BTree<T>& BTree<T>::operator= (const BTree<T>&) {
  return BTree(*this);
}

// Copy Node
template <typename T>
shared_ptr<Node<T>> BTree<T>::copyNode(shared_ptr<Node<T>> ptr) {
  if (ptr == nullptr) {
    return nullptr;
  }
  auto ptrCopy = make_shared<Node<T>>(ptr->data);
  ptrCopy->left = copyNode(ptr->left);
  ptrCopy->right = copyNode(ptr->right);
  return ptrCopy;
}

//// Insert
template <typename T>
void BTree<T>::insert(const T& item) {
  if (root == nullptr) {
    root = make_shared<Node<T>>(item);
    return;
  }
  insert(item, root);
}

template <typename T>
void BTree<T>::insert(const T& item, shared_ptr<Node<T>> ptr) {
  if (item < ptr->data) {
    if (ptr->left == nullptr) {
      ptr->left == make_shared<Node<T>>(item);
      return;
    }
    insert(item, ptr->left);
  }
  else {
    if (ptr->right == nullptr) {
      ptr->right == make_shared<Node<T>>(item);
      return;
    }
    insert(item, ptr->right);
  }
}

//// Pre-Order 
template <typename T>
void BTree<T>::preOrder() {
  preOrder(root);
}

template <typename T>
void BTree<T>::preOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    cout << ptr->data << " ";
    preOrder(ptr->left);
    preOrder(ptr->right);
  }
}

//// In-Order 
template <typename T>
void BTree<T>::inOrder() {
  inOrder(root);
}

template <typename T>
void BTree<T>::inOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    inOrder(ptr->left);
    cout << ptr->data << " ";
    inOrder(ptr->right);
  }
}

//// Post-Order
template <typename T>
void BTree<T>::postOrder() {
  postOrder(root);
}

template <typename T>
void BTree<T>::postOrder(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    postOrder(ptr->left);
    postOrder(ptr->right);
    cout << ptr->data << " ";
  }
}

//// Node Count 
template <typename T>
int BTree<T>::nodeCount() {
  return nodeCount(root);
}

template <typename T>
int BTree<T>::nodeCount(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    return 1 + nodeCount(ptr->left) + nodeCount(ptr->right);
  }
  return 0;
}

//// Leaves Count 
template <typename T>
int BTree<T>::leavesCount() {
  return leavesCount(root);
}

template <typename T>
int BTree<T>::leavesCount(shared_ptr<Node<T>> ptr) {
  if (ptr) {
    if (ptr->left == nullptr && ptr->right == nullptr) {
      return 1;
    }
    return leavesCount(ptr->left) + leavesCount(ptr->right);
  }
  return 0;
}