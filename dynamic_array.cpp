#include <iostream>
using namespace std;

template <class T> class Array {
public:
  Array();
  Array(size_t CAPACITY);
  ~Array();

  void push_back(T element);
  void clear();
  void finish();
  string resize(size_t new_capacity);
  size_t get_capacity() const;
  size_t get_size() const;
  void pop_back();
  void get_at(size_t index);

private:
  T *arr;
  size_t size;
  size_t capacity;
};

template <class T> Array<T>::Array() {
  arr = new T[1];
  capacity = 1;
  size = 0;
};

template <class T> Array<T>::Array(size_t CAPACITY) {
  arr = new T[CAPACITY];
  capacity = CAPACITY;
  size = 0;
}

template <class T> Array<T>::~Array() { delete[] arr; }

template <class T> string Array<T>::resize(size_t new_capacity) {
  while (size > new_capacity) {
    size--;
  }

  T *temp = new T[new_capacity];
  for (size_t i = 0; i < size; i++) {
    temp[i] = arr[i];
  }
  delete[] arr;
  arr = temp;
  capacity = new_capacity;
  const string array = "ok";
  return array;
}

template <class T> void Array<T>::push_back(T element) {
  if (size == capacity) {
    capacity *= 2;
    resize(capacity);
  }
  arr[size] = element;
  size++;
  cout << "ok" << endl;
}

template <class T> void Array<T>::pop_back() {
  if (size == 0) {
    cout << "error" << endl;
  }
  cout << arr[--size] << endl;
  if (size <= capacity / 2) {
    capacity = capacity / 2;
    resize(capacity);
  }
}

template <class T> void Array<T>::get_at(size_t index) {
  if (index >= size || index < 0) {
    cout << "error" << endl;
  } else
    cout << arr[index] << endl;
}

template <class T> size_t Array<T>::get_size() const { return size; }

template <class T> size_t Array<T>::get_capacity() const { return capacity; }

template <class T> void Array<T>::clear() {
  resize(1);
  cout << "ok" << endl;
}

template <class T> void Array<T>::finish() {
  cout << "bye" << endl;
  exit(0);
}

int main() {
  Array<int> array;
  int value;
  string input;
  int counter = 1;
  while (counter != 0) {
    cin >> input;
    if (input == "exit") {
      array.finish();
      counter = 0;
    }
    if (input == "push") {
      cin >> value;
      array.push_back(value);
    }
    if (input == "pop") {
      array.pop_back();
    }
    if (input == "capacity") {
      cout << array.get_capacity() << endl;
    }
    if (input == "size") {
      cout << array.get_size() << endl;
    }
    if (input == "at") {
      cin >> value;
      array.get_at(value);
    }
    if (input == "resize") {
      cout << array.resize(2) << endl;
    }
    if (input == "clear") {
      array.clear();
    }
  }
}