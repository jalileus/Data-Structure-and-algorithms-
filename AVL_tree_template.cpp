/*
Time limit: 3 seconds
Memory limit: 256Mb
Input: standard input or input.txt
Output: standard output or output.txt

problem :
Dominic takes inventory (again). He is sure that the cars can and should be compared by the number of milliseconds to accelerate from zero to 100 km/h. He asks you to help him, namely, 
your algorithm must work with a lot of Dominic's cars. You need to implement the following operations:

add(i) — add a car with an acceleration of i milliseconds to the set of cars (if it's already there, then Dominic was distracted by family talk and slipped you the same car a second time);
next(i) — find out the car with the minimum acceleration time of at least i. If the car you're looking for is missing, print -1 and tell Dominic to be more careful.
Input format:
The original machine set is empty. The first line of the input file contains the number n — the number of Dominic's requests (1 < n < 3 ⋅ 10^5).

The next n lines contain operations. Each operation has the form:

+ i — add(i)
? i — next(i)
If the + operation comes in the input file at the beginning or after another + operation, it sets up the add(i) operation. If it comes after the query, and the result of that query was y, then the operation continues. This is to make sure Dominic makes sure you're a decent family member and haven't implemented an offline algorithm.

In all queries and addition operations, the parameters lie in the range from 0 to 10^9.

Output format:
For each query, print one number — the answer to the query.

Sample 1:
Input:
6
+ 1
+ 3
+ 3
? 2
+ 1
? 4
output:
3
4

Sample 2:
input:
30
+ 50
+ 29
+ 77
? 94
? 26
+ 41
? 9
+ 72
? 93
+ 12
+ 19
+ 59
+ 21
? 2
? 75
+ 75
+ 55
+ 52
+ 10
? 58
+ 85
+ 49
+ 82
+ 99
? 66
+ 58
+ 77
+ 22
+ 7
? 36

output:
-1
29
29
101
19
77
59
70
49
*/

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
