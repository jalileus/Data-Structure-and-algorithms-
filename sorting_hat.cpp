#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

template <class T>
struct MinStack {
 public:
  std::stack<T>* stack;
  std::stack<T>* min_stack;
  MinStack() {
    stack = new std::stack<T>();
    min_stack = new std::stack<T>();
  }
  ~MinStack() {
    delete stack;
    delete min_stack;
  }

  void Push(const T& value) {
    stack->push(value);
    if (min_stack->empty() || value <= min_stack->top()) {
      min_stack->push(value);
    }
  }

  T Pop() {
    if (stack->empty()) {
      throw("error");
    }
    T val = stack->top();
    stack->pop();
    if (val == min_stack->top()) {
      min_stack->pop();
    }
    return val;
  }

  T Top() const {
    if (stack->empty()) {
      throw("error");
    }
    return stack->top();
  }

  size_t Size() const { return stack->size(); }

  void Empty() {
    while (!stack->empty()) {
      stack->pop();
    }
    while (!min_stack->empty()) {
      min_stack->pop();
    }
  }

  T Min() const { return min_stack->top(); }
};

template <class T>
class SortingHat {
 public:
  MinStack<T> stack1, stack2;
  void Enqueue(const T& value) { stack1.Push(value); }
  T Dequeue() {
    if (stack2.stack->empty()) {
      while (!stack1.stack->empty()) {
        stack2.Push(stack1.Pop());
      }
    }
    return stack2.Pop();
  }
  T Front() {
    if (stack2.stack->empty()) {
      while (!stack1.stack->empty()) {
        stack2.Push(stack1.Pop());
      }
    }
    return stack2.Top();
  }
  void Clear() {
    stack1.Empty();
    stack2.Empty();
  }
  T GetMin() {
    if (stack1.stack->empty() && stack2.stack->empty()) {
      throw("error");
    }
    if (stack1.stack->empty()) {
      return stack2.Min();
    }
    if (stack2.stack->empty()) {
      return stack1.Min();
    }
    return std::min(stack1.Min(), stack2.Min());
  }
  size_t GetSize() const { return stack1.Size() + stack2.Size(); }
};

int main() {
  SortingHat<int> my_hat;
  int frequence, data;
  std::string order;
  std::cin >> frequence;
  for (; frequence > 0; frequence--) {
    std::cin >> order;
    if (order == "clear") {
      my_hat.Clear();
      std::cout << "ok" << std::endl;
    } else if (order == "size") {
      std::cout << my_hat.GetSize() << std::endl;
    }
    try {
      if (order == "enqueue") {
        std::cin >> data;
        my_hat.Enqueue(data);
        std::cout << "ok" << std::endl;
      } else if (order == "dequeue") {
        std::cout << my_hat.Dequeue() << std::endl;
      } else if (order == "front") {
        std::cout << my_hat.Front() << std::endl;
      } else if (order == "min") {
        std::cout << my_hat.GetMin() << std::endl;
      }
    } catch (const char* output) {
      std::cout << output << std::endl;
    }
  }
}
