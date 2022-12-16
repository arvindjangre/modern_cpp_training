#include <iostream>
#include <vector>

int main() {
  std::cout << "hello" << std::endl;
  std::vector<int> v;
  std::vector<char> c;

  std::cout << v.max_size() << std::endl;
  // 2 305 843 009 213 693 951
  std::cout << c.max_size() << std::endl;
  // 9 223 372 036 854 775 807 number of chars can store.
  
  return 0;
}

