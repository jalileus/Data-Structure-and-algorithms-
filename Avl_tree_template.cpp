#include <algorithm>
#include <iostream>

template <class T>
struct Node {
  Node* right;
  Node* left;
  T key;
  int height;
  Node(T key) {
    this->key = key;
    height = 1;
    left = right = 0;
  }
};

template <class T>
class AvlTree {
 public:
  AvlTree();
  ~AvlTree();
  void Add(T key);
  void Delete();
  T Next(T i);

 private:
  void DeleteCars(Node<T>* node);
  Node<T>* RightRotation(Node<T>* node);
  Node<T>* LeftRotation(Node<T>* node);
  Node<T>* BalanceTree(Node<T>* node);
  Node<T>* AddAcceleration(Node<T>* node, T key);
  Node<T>* NextAcceleration(Node<T>* node, T val);
  int GetFactor(Node<T>* n);
  int GetHeight(Node<T>* n);
  Node<T>* root_;
};

template <class T>
AvlTree<T>::AvlTree() : root_(0) {}

template <class T>
void AvlTree<T>::DeleteCars(Node<T>* node) {
  if (node != 0) {
    DeleteCars(node->left);
    DeleteCars(node->right);
    delete node;
  }
}

template <class T>
AvlTree<T>::~AvlTree() {
  DeleteCars(root_);
}

template <class T>
int AvlTree<T>::GetHeight(Node<T>* n) {
  if (n == 0) {
    return 0;
  }
  return n->height;
}

template <class T>
int AvlTree<T>::GetFactor(Node<T>* n) {
  if (n == 0) {
    return 0;
  }
  return GetHeight(n->left) - GetHeight(n->right);
}

template <class T>
Node<T>* AvlTree<T>::RightRotation(Node<T>* node) {
  Node<T>* child = node->left;

  node->left = child->right;
  child->right = node;

  node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  child->height = std::max(GetHeight(child->left), GetHeight(child->right)) + 1;

  return child;
}

template <class T>
Node<T>* AvlTree<T>::LeftRotation(Node<T>* node) {
  Node<T>* child = node->right;

  node->right = child->left;
  child->left = node;

  node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  child->height = std::max(GetHeight(child->left), GetHeight(child->right)) + 1;

  return child;
}

template <class T>
Node<T>* AvlTree<T>::BalanceTree(Node<T>* node) {
  int balance = GetFactor(node);
  if (balance > 1 && GetFactor(node->left) >= 0) {
    return RightRotation(node);
  }

  if (balance > 1 && GetFactor(node->left) < 0) {
    node->left = LeftRotation(node->left);
    return RightRotation(node);
  }

  if (balance < -1 && GetFactor(node->right) <= 0) {
    return LeftRotation(node);
  }

  if (balance < -1 && GetFactor(node->right) > 0) {
    node->right = RightRotation(node->right);
    return LeftRotation(node);
  }
  return node;
}

template <class T>
Node<T>* AvlTree<T>::AddAcceleration(Node<T>* node, T key) {
  if (node == 0) {
    Node<T>* new_node = new Node<T>(key);
    return new_node;
  }
  if (key < node->key) {
    node->left = AddAcceleration(node->left, key);
  } else if (key > node->key) {
    node->right = AddAcceleration(node->right, key);
  } else if (key == node->key) {
    return node;
  }
  node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  return BalanceTree(node);
}

template <class T>
void AvlTree<T>::Add(T key) {
  root_ = AddAcceleration(root_, key);
}

template <class T>
Node<T>* AvlTree<T>::NextAcceleration(Node<T>* node, T val) {
  if (node == 0) {
    return 0;
  }
  Node<T>* res = 0;
  while (node != 0) {
    if (node->key >= val) {
      res = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return res;
}

template <class T>
T AvlTree<T>::Next(T i) {
  Node<T>* node = NextAcceleration(root_, i);
  if (node == 0) {
    return -1;
  }
  return node->key;
}

int main() {
  AvlTree<long long> my_tree;
  int n;
  long long y = 0;
  std::cin >> n;
  for (int k = 0; k < n; k++) {
    char input;
    long long i;
    std::cin >> input >> i;
    if (input == '+') {
      long long x = ((i + y) % 1000000000);
      my_tree.Add(x);
      y = 0;
    } else if (input == '?') {
      long long res = my_tree.Next(i);
      if (res != -1) {
        y = res;
        std::cout << res << std::endl;
      } else {
        std::cout << res << std::endl;
      }
    }
  }
}