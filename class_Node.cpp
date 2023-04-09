#include <iostream>
#include <string>

struct Node {
  char item;
  struct Node *next;
  Node(char item) {
    this->item = item;
    next = nullptr;
  }
};

class List {
  Node *head;

 public:
  List(std::string data) {
    head = nullptr;
    for (int i = 0; i < data.length(); i++) {
      Node *new_node = new Node(data[i]);

      if (head == nullptr) {
        head = new_node;
      } else {
        Node *last = head;
        while (last->next != nullptr) last = last->next;
        last->next = new_node;
      }
    }
  }

  ~List() {
    Node *current = head;
    while (current != nullptr) {
      Node *temp = current;
      current = current->next;
      delete temp;
    }
  }
  void Reverse() {
    Node *current = head;
    Node *next = nullptr;
    Node *previous = nullptr;

    while (current != nullptr) {
      next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }
    head = previous;
  }
  void Print() {
    struct Node *new_node = head;
    while (new_node != nullptr) {
      std::cout << new_node->item;
      new_node = new_node->next;
    }
  }
};
int main() {
  std::string input;
  std::getline(std::cin, input);
  List MyList(input);
  MyList.Reverse();
  MyList.Print();

  return 0;
}
