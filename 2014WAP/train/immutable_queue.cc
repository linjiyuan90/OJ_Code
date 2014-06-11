#include "iostream"
#include "memory"

template<typename T>
class List {
  T _head;
  std::shared_ptr<List<T>> _tail;

public:
  List(){}
  List(T _head): _head(_head) {
  }
  List(T _head, std::shared_ptr<List<T>> _tail): _head(_head), _tail(_tail) {
  }
  
  int size() {
    return _tail == nullptr ? 1 : 1 + _tail->size();
  }

  T head() {
    return _head;
  }

  std::shared_ptr<List<T>> tail() {
    return _tail;
  }
};

void testList() {
  std::shared_list<List<int>> list;
  std::cout << a.size() << std::endl;
}

template<typename T>
class immutable_queue {
  
};


int main() {
  testList();
  
  return 0;
}
