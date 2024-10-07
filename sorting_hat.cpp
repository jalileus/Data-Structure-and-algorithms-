/*
Time limit: 2 seconds  
Memory limit: 64Mb  
Input: standard input or input.txt  
Output: standard output or output.txt  

problem :
Potter put on The Sorting Hat, and he was just right for Slytherin. Vladislav Hacker(c)

The Sorting Hat — an extremely ancient artifact capable of figuring out from its bearer which faculty would suit him for the fullest disclosure of his character. But someone decided to enchant the hat, and now it determines the wearer's IQ level. It is up to you to implement the enchanted hat to lift the curse on the original one.

You have the hat itself and a set of actions that will happen to it. There is a line of Hogwarts freshmen who want to test themselves against the hat. Possible actions:

- «enqueue n» Add the intelligence level of the next freshman n (1 ≤ n ≤ 10^9) (the n value is set after the command) to the hat's internal queue. The hat must say «ok».
- «dequeue» Remove from the hat's internal queue the intelligence level of the last student it still remembers. The hat should tell its value.
- «front» The hat must tell the intelligence level of the last student it still remembers without forgetting it.
- «size» The hat will tell you the intelligence level of how many students it remembers.
- «clear» Reload the hat, it forgets everything that came before. The hat must say «ok».
- «min» The hat must tell the level of intelligence of the most untalented freshman. At the same time, of course, not to forget him.

Before executing the «front», «dequeue» and «min» operations, the hat should check if the internal queue contains at least one item. If the hat remembers zero students at the time of such queries, it should say the word «error» instead of a numerical value.

Input format:
The first line of input contains a single number M (1 ≤ M ≤ 2 ⋅ 10^5) — the number of commands. The next M lines contain one command each of those above.

Output format:
For each command, print one line — what the hat says.

Sample
**Input**:  
9  
enqueue 2  
front  
dequeue  
size  
dequeue  
enqueue 1  
enqueue 2  
size  
min  

**Output**:  
ok  
2  
2  
0  
error  
ok  
ok  
2  
1

*/

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
