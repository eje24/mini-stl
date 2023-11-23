#include <iostream>
#include "vector.h"

int main(){
  ministl::vector<int> v = {1,2,3,4};
  std::cout << v.size() << std::endl;
  for(std::size_t i = 0; i < v.size(); ++i){
    std::cout << v[i] << std::endl;
  }
  return 0;
}
