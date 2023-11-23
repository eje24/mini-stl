#include <iostream>
#include "vector.h"

void print_vector_info(const ministl::vector<int>& v){
  std::cout << "size: " << v.size() << std::endl;
  std::cout << "capacity: " << v.capacity() << std::endl;
  // Print elements
  for(std::size_t i = 0; i < v.size(); ++i){
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

int main(){
  ministl::vector<int> v = {1,2,3,4};
  std::cout << v.size() << std::endl;
  v.push_back(3);
  v.push_back(4);
  print_vector_info(v);
  v.emplace_back(5);
  v.emplace(v.begin() + 1, 10);
  print_vector_info(v);
  return 0;
}
