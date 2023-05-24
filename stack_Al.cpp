#include <iostream>
#include <string>

const size_t kMaxSize = 10000;
template <class T>
class Stack {
 public:
  Stack();
  ~Stack();
  void Resize(size_t new_capacity);
  T& Back();
  void Push(T element);
  void Clear();
  void Exit();
  T Pop();
  size_t GetSize() const;

 private:
  T* stack_;
  size_t capacity_;
  size_t size_;
};

template <class T>
Stack<T>::Stack() {
  size_ = 0;
  capacity_ = 1;
  stack_ = new T[capacity_];
}

template <class T>
Stack<T>::~Stack() {
  delete[] stack_;
}

template <class T>
void Stack<T>::Resize(size_t new_capacity) {
  T* new_stack = new T[new_capacity];
  for (size_t i = 0; i < size_; i++) {
    new_stack[i] = stack_[i];
  }
  delete[] stack_;
  stack_ = new_stack;
  capacity_ = new_capacity;
}
template <class T>
void Stack<T>::Push(T element) {
  if (size_ == kMaxSize) {
    throw("error");
  }
  if (size_ == capacity_) {
    Resize(capacity_ * 2);
  }
  stack_[size_] = element;
  size_ += 1;
}
template <class T>
T Stack<T>::Pop() {
  if (size_ == 0) {
    throw("error");
  }
  T var = stack_[size_ - 1];
  size_ -= 1;
  if (capacity_ == size_ * 2) {
    Resize(capacity_ / 2);
  }
  return var;
}
template <class T>
T& Stack<T>::Back() {
  if (size_ == 0) {
    throw("error");
  }
  return stack_[size_ - 1];
}
template <class T>
size_t Stack<T>::GetSize() const {
  return size_;
}
template <class T>
void Stack<T>::Clear() {
  size_ = 0;
  Resize(1);
}
template <class T>
void Stack<T>::Exit() {
  exit(0);
}

int main() {
  Stack<int> my_stack;
  std::string item;
  int val;
  while (true) {
    std::cin >> item;
    if (item == "exit") {
      std::cout << "bye" << std::endl;
      my_stack.Exit();
    }
    try {
      if (item == "push") {
        std::cin >> val;

        my_stack.Push(val);
        std::cout << "ok" << std::endl;
      } else if (item == "pop") {
        std::cout << my_stack.Pop() << std::endl;
      } else if (item == "back") {
        std::cout << my_stack.Back() << std::endl;
      } else if (item == "size") {
        std::cout << my_stack.GetSize() << std::endl;
      } else if (item == "clear") {
        my_stack.Clear();
        std::cout << "ok" << std::endl;
      }
    } catch (const char* output) {
      std::cout << output << std::endl;
    }
  }
}