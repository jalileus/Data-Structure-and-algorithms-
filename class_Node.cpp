#include <iostream>

struct Node {
  char item;
  struct Node *Next;
  Node(char item) {
    this->item = item;
    Next = nullptr;
  }
};

class Linked_List {
  Node *Head;

public:
  Linked_List(std::string data) {
    Head = nullptr;

    for (int i = 0; i < data.length(); i++) {
      Node *New = new Node(data[i]);

      if (Head == nullptr) {
        Head = New;
      } else {
        Node *Last = Head;
        while (Last->Next != nullptr)
          Last = Last->Next;
        Last->Next = New;
      }
    }
  }

  ~Linked_List() {
    Node *CURRENT = Head;
    while (CURRENT != nullptr) {
      Node *Temp = CURRENT;
      CURRENT = CURRENT->Next;
      delete Temp;
    }
  }

  void Reversed() {
    Node *Current = Head;
    Node *Next = nullptr;
    Node *Previous = nullptr;

    while (Current != nullptr) {
      Next = Current->Next;
      Current->Next = Previous;
      Previous = Current;
      Current = Next;
    }
    Head = Previous;
  }
  void Print() {
    struct Node *New = Head;
    while (New != nullptr) {
      std::cout << New->item;
      New = New->Next;
    }
  }
};
int main() {
  std::string data;
  std::getline(std::cin, data);
  Linked_List List(data);
  List.Reversed();
  List.Print();

  return 0;
}
