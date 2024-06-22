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
  shared_ptr<Node<T>> find(const T& item);
  shared_ptr<Node<T>> findRightMostNode(shared_ptr<Node<T>> ptr);
  shared_ptr<Node<T>> findParent(shared_ptr<Node<T>> ptr);

private:
  shared_ptr<Node<T>> copyNode(shared_ptr<Node<T>> ptr);
  void insert(const T& item, shared_ptr<Node<T>> ptr);
  void preOrder(shared_ptr<Node<T>> ptr);
  void inOrder(shared_ptr<Node<T>> ptr);
  void postOrder(shared_ptr<Node<T>> ptr);
  int nodeCount(shared_ptr<Node<T>> ptr);
  int leavesCount(shared_ptr<Node<T>> ptr);
  shared_ptr<Node<T>> find(shared_ptr<Node<T>> ptr, const T& item);
  shared_ptr<Node<T>> findParent(shared_ptr<Node<T>> ptr, shared_ptr<Node<T>> toFind);
  
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
      ptr->left = make_shared<Node<T>>(item);
      return;
    }
    insert(item, ptr->left);
  }
  else {
    if (ptr->right == nullptr) {
      ptr->right = make_shared<Node<T>>(item);
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

//// Find
template <typename T>
shared_ptr<Node<T>> BTree<T>::find(const T& item) {
  return find(root, item);
}

template <typename T>
shared_ptr<Node<T>> BTree<T>::find(shared_ptr<Node<T>> ptr, const T& item) {
  if(ptr) {
    if (ptr->data == item) {
      return ptr;
    }
    else if (item < ptr->data) {
      return find(ptr->left, item);
    }
    else {
      return find(ptr->right, item);
    }
  }
  return nullptr;
}

//// Find Right Most Node 
template <typename T>
shared_ptr<Node<T>> BTree<T>::findRightMostNode(shared_ptr<Node<T>> ptr) {
  while(ptr->right) {
    ptr = ptr->right;
  }
  return ptr;
}

//// Find Parent
template <typename T>
shared_ptr<Node<T>> BTree<T>::findParent(shared_ptr<Node<T>> ptr) {
  return findParent(root, ptr);
}

template <typename T>
shared_ptr<Node<T>> BTree<T>::findParent(shared_ptr<Node<T>> ptr, shared_ptr<Node<T>> toFind) {
  if (ptr) {
    if ((ptr->left == toFind) || (ptr->right == toFind)) {
      return ptr;
    }
    else if (toFind->data < ptr->data) {
      return findParent(ptr->left, toFind);
    }
    else {
      return findParent(ptr->right, toFind);
    }
  }
  return nullptr;
}

//// Remove
template <typename T>
void BTree<T>::remove(const T& item) {
  auto toDelete = find(item);
  auto leftPtr = toDelete->left;
  auto rightPtr = toDelete->right;

  // No Children
  if ((!leftPtr) && (!rightPtr)) {
    auto pPtr = findParent(toDelete);
    // To the Left
    if (pPtr->left == toDelete) {
      pPtr->left = nullptr;
    }
    // To the Right
    else {
      pPtr->right = nullptr;
    }
  }

  // Left Child
  else if ((!rightPtr) && (leftPtr)) {
    if (toDelete == root) {
      root = leftPtr;
      return;
    }
    auto pPtr = findParent(toDelete);
    // To the Left
    if (pPtr->left == toDelete) {
      pPtr->left = leftPtr;
    }
    // To the Right
    else {
      pPtr->right = leftPtr;
    }
  }

  // Right Child
  else if ((!leftPtr) && (rightPtr)) {
    if (toDelete == root) {
      root = rightPtr;
      return;
    }
    auto pPtr = findParent(toDelete);
    // To the Left
    if (pPtr->left == toDelete) {
      pPtr->left = rightPtr;
    }
    // To the Right
    else {
      pPtr->right = rightPtr;
    }
  }

  // Two Children
  else {
    // Right Most Node to the left
    auto rightMost = findRightMostNode(leftPtr);
    auto leftRM = rightMost->left;
    // Removing Node from the Bottom
    auto rightMP = findParent(rightMost);

    // If Right Most doesn't have Children
    if ((!rightMost->left) && (!rightMost->right)) {
      if (rightMP->right == rightMost) {
        rightMP->right = nullptr;
      }
      else {
        rightMP->left = nullptr;
      }
    }
    else {
      if (rightMP->right == rightMost) {
        rightMP->right = leftRM;
      }
      else {
        rightMP->left = leftRM;
      }
    }
    
    // Resetting the Children
    rightMost->left = leftPtr;
    rightMost->right = rightPtr;
    // If root
    if (toDelete == root) {
      root = rightMost;
      return;
    }
    auto pPtr = findParent(toDelete);
    // To the Left
    if (pPtr->left == toDelete) {
      pPtr->left = rightMost;
    }
    // To the Right
    else {
      pPtr->right = rightMost;
    }
  }
}