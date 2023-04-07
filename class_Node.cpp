#include <iostream>

struct Node {
  char item;
  struct Node *next;
  Node(char item) {
    this->item = item;
    next = 0;
  }
};

class linked_list {
  Node *head;

public:
  linked_list(std::string data) {
    head = NULL;
    for (int i = 0; i < data.length(); i++) {
      Node *New = new Node(data[i]);

      if (head == 0) {
        head = New;
      } else {
        Node *last = head;
        while (last->next != 0)
          last = last->next;
        last->next = New;
      }
    }
  }

  ~linked_list() {}

  void Reversed() {
    Node *current = head;
    Node *next = 0;
    Node *previous = 0;

    while (current != 0) {
      next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }
    head = previous;
  }
  void Print() {
    struct Node *New = head;
    while (New != 0) {
      std::cout << New->item;
      New = New->next;
    }
  }
};
int main() {
  std::string data;
  std::getline(std::cin, data);
  linked_list list(data);
  list.Reversed();
  list.Print();

  return 0;
}
