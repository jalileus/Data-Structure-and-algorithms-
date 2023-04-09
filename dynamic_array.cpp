#include <iostream>
#include <string>

template <class T>
class Vector {
 public:
  Vector();
  ~Vector();

  void PushBack(T data);
  void Clear();
  void Finish();
  void Resize(size_t new_capacity);
  T PopBack();
  T GetAt(size_t index);
  size_t get_capacity() const;
  size_t get_size() const;

 private:
  T *array_;
  size_t size_;
  size_t capacity_;
};

template <class T>
Vector<T>::Vector() {
  capacity_ = 1;
  array_ = new T[capacity_];
  size_ = 0;
};

template <class T>
Vector<T>::~Vector() {
  delete[] array_;
}

template <class T>
void Vector<T>::Resize(size_t new_capacity) {
  while (size_ > new_capacity) {
    size_ -= 1;
  }
  T *temp = new T[new_capacity];
  for (size_t i = 0; i < size_; i++) {
    temp[i] = array_[i];
  }
  delete[] array_;
  array_ = temp;
  capacity_ = new_capacity;
}

template <class T>
void Vector<T>::PushBack(T element) {
  if (size_ == capacity_) {
    capacity_ *= 2;
    Resize(capacity_);
  }
  array_[size_] = element;
  size_ += 1;
}

template <class T>
T Vector<T>::PopBack() {
  if (size_ == 0) {
    throw("error");
  }
  size_ -= 1;
  T value = array_[size_];
  if (size_ = capacity_ / 2) {
    capacity_ = capacity_ / 2;
    Resize(capacity_);
  }
  return value;
}

template <class T>
T Vector<T>::GetAt(size_t index) {
  if (index >= size_ || index < 0) {
    throw("error");
  } else
    return array_[index];
}

template <class T>
size_t Vector<T>::get_size() const {
  return size_;
}

template <class T>
size_t Vector<T>::get_capacity() const {
  return capacity_;
}

template <class T>
void Vector<T>::Clear() {
  size_ = 0;
  Resize(1);
}

template <class T>
void Vector<T>::Finish() {
  exit(0);
}

int main() {
  Vector<int> MyArray;
  int variable;
  std::string input;
  int counter = 1;
  while (counter != 0) {
    std::cin >> input;
    if (input == "exit") {
      std::cout << "bye" << std::endl;
      MyArray.Finish();
      counter = 0;
    }
    if (input == "push") {
      std::cin >> variable;
      MyArray.PushBack(variable);
      std::cout << "ok" << std::endl;
    }
    if (input == "pop") {
      try {
        std::cout << MyArray.PopBack() << std::endl;
      } catch (const char *output1) {
        std::cout << output1 << std::endl;
      }
    }
    if (input == "capacity") {
      std::cout << MyArray.get_capacity() << std::endl;
    }
    if (input == "size") {
      std::cout << MyArray.get_size() << std::endl;
    }
    if (input == "at") {
      std::cin >> variable;
      try {
        std::cout << MyArray.GetAt(variable) << std::endl;
      } catch (const char *output2) {
        std::cout << output2 << std::endl;
      }
    }
    if (input == "resize") {
      std::cin >> variable;
      MyArray.Resize(variable);
      std::cout << "ok" << std::endl;
    }
    if (input == "clear") {
      MyArray.Clear();
      std::cout << "ok" << std::endl;
    }
  }
}
