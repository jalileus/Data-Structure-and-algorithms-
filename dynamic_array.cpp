#include <iostream>

template <class T> class Vector {
public:
  Vector();
  ~Vector();

  void PushBack(T Data);
  void PopBack();
  void clear();
  void finish();
  void resize(size_t new_capacity);
  size_t get_capacity() const;
  size_t get_size() const;
  T GetAt(size_t index_);

private:
  T *Array;
  size_t size_;
  size_t capacity_;
};

template <class T> Vector<T>::Vector() {
  capacity_ = 1;
  Array = new T[capacity_];
  size_ = 0;
};

template <class T> Vector<T>::~Vector() { delete[] Array; }

template <class T> void Vector<T>::resize(size_t new_capacity) {
  while (size_ > new_capacity) {
    size_ -= 1;
  }
  T *temp = new T[new_capacity];
  for (size_t i_ = 0; i_ < size_; i_++) {
    temp[i_] = Array[i_];
  }
  delete[] Array;
  Array = temp;
  capacity_ = new_capacity;
}

template <class T> void Vector<T>::PushBack(T ELEMENT) {
  if (size_ == capacity_) {
    capacity_ *= 2;
    resize(capacity_);
  }
  Array[size_] = ELEMENT;
  size_ += 1;
}

template <class T> void Vector<T>::PopBack() {
  if (size_ == 0) {
    throw("error");
  }
  size_ -= 1;
  std::cout << Array[size_] << std::endl;
  if (size_ = capacity_ / 2) {
    capacity_ = capacity_ / 2;
    resize(capacity_);
  }
}

template <class T> T Vector<T>::GetAt(size_t index_) {
  if (index_ >= size_ || index_ < 0) {
    throw("error");
  } else
    return Array[index_];
}

template <class T> size_t Vector<T>::get_size() const { return size_; }

template <class T> size_t Vector<T>::get_capacity() const { return capacity_; }

template <class T> void Vector<T>::clear() { resize(1); }

template <class T> void Vector<T>::finish() { exit(0); }

int main() {
  Vector<int> arr;
  int value;
  std::string input;
  int counter = 1;
  while (counter != 0) {
    std::cin >> input;
    if (input == "exit") {
      std::cout << "bye" << std::endl;
      arr.finish();
      counter = 0;
    }
    if (input == "push") {
      std::cin >> value;
      arr.PushBack(value);
      std::cout << "ok" << std::endl;
    }
    if (input == "pop") {
      try {
        arr.PopBack();
      } catch (const char *output2) {
        std::cout << output2 << std::endl;
      }
    }
    if (input == "capacity") {
      std::cout << arr.get_capacity() << std::endl;
    }
    if (input == "size") {
      std::cout << arr.get_size() << std::endl;
    }
    if (input == "at") {
      std::cin >> value;
      try {
        std::cout << arr.GetAt(value) << std::endl;
      } catch (const char *output3) {
        std::cout << output3 << std::endl;
      }
    }
    if (input == "resize") {
      arr.resize(2);
      std::cout << "ok" << std::endl;
    }
    if (input == "clear") {
      arr.clear();
      std::cout << "ok" << std::endl;
    }
  }
}
