#ifndef MINISTL_VECTOR_H
#define MINISTL_VECTOR_H

namespace ministl {
  template<typename T, typename Allocator = std::allocator<T>>
  class vector{
  public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = T&;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  private:
    T* _data = nullptr;
    size_type _size = 0;
    size_type _capacity = 0;
    allocator_type _alloc;

    int capacity_from_size(std::size_t size){
      return std::max((size_type) 3, (size_type) (size * 1.5));
    }

  public:
    // Constructors
    vector() = default;
    
    vector(std::initializer_list<T> initializer_list, const Allocator& alloc = Allocator()): _alloc(alloc){
      _size = initializer_list.size();
      _capacity = capacity_from_size(_size);
      _data = _alloc.allocate(_capacity);
      for(auto it = initializer_list.begin(); it != initializer_list.end(); ++it){
        _data[it - initializer_list.begin()] = *it;
      }
    }

    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _alloc(alloc) {
      _size = count;
      _capacity = capacity_from_size(_size);
      _data = _alloc.allocate(_capacity);
      // loop through and copy vector
      for(int idx = 0; idx < _size; idx++){
        _data[idx] = value;
      }
    }

    vector(const vector& other): _size(other.size()), _capacity(other.capacity()), _alloc(other.alloc()){
      _alloc.allocate(_capacity);
      for(int idx = 0; idx < _size; idx++){
        _data[idx] = other[idx];
      }
    }

    vector(vector&& other): _size(other.size()), _capacity(other.capacity()), _data(other.data()), _alloc(std::move(other.alloc())){
      other._size = 0;
      other._capacity = 0;
      other._data = nullptr;
    }

    // Destructor
    ~vector(){
      for(size_type idx = 0; idx < _size; idx++){
        _data[idx].~T();
      }
      _alloc.deallocate(_data, _capacity);
    }

    // Assignment Operators
    vector& operator=(const vector& other){
      if(this == &other){
        return *this;
      }
      vector tmp(other);
      swap(tmp);
      return *this;
    }

    vector& operator=(vector&& other){
      swap(other);
      return *this;
    }

    vector& operator=(std::initializer_list<T> initializer_list){
      vector tmp(initializer_list);
      swap(tmp);
      return *this;
    }

    allocator_type& get_allocator() const{
      return _alloc;
    }

    // Element Access
    T& at(const std::size_t idx){
      if(idx >= _size){
        throw std::out_of_range("Index out of range");
      }
      return _data[idx];
    }
    T& operator[](const std::size_t idx) const {
      // hopefully this returns a reference?
      return _data[idx];
    }
    T& front(){
      return _data[0];
    }
    T& back(){
      return _data[_size - 1];
    }
    T* data(){
      return _data;
    }
    
    // Iterators
    iterator begin(){
      return iterator(_data);
    }
    const_iterator cbegin(){
      return const_iterator(_data);
    }
    iterator end(){
      return iterator(_data) + _size;
    }
    const_iterator cend(){
      return const_iterator(_data) + _size;
    }
    reverse_iterator rbegin(){
      return reverse_iterator(_data + _size - 1);
    }
    reverse_iterator rend(){
      return reverse_iterator(_data - 1);
    }
    const_reverse_iterator crbegin(){
      return const_reverse_iterator(_data + _size - 1);
    }
    const_reverse_iterator crend(){
      return const_reverse_iterator(_data - 1);
    }

    // Capacity
    constexpr bool empty() const {
      return _size == 0;
    }

    constexpr size_type size() const {
      return _size;
    }

    constexpr void max_size() const {
      return std::allocator_traits<allocator_type>::max_size(_alloc);
    }

    constexpr void reserve(size_type new_capacity){
      grow_capacity(new_capacity);
    }

    constexpr size_type capacity() const {
      return _capacity;
    }

    constexpr void shrink_to_fit(){
      shrink_capacity(_size);
    }

    // Modifiers
    constexpr void push_back(const T& value){
      // grow if necessary
      if(_size == _capacity){
        grow_capacity(capacity_from_size(_size + 1));
      }
      // copy over data
      _data[_size] = value;
      _size += 1;
    }

    constexpr void push_back(T&& value){
      // grow if necessary
      if(_size == _capacity){
        grow_capacity(capacity_from_size(_size + 1));
      }
      // copy over data
      _data[_size] = std::move(value);
      _size += 1;
    }

    template<typename... Args>
    void emplace_back(Args&&... args){
      emplace(end(), std::forward<Args>(args)...);
    }

    template<typename... Args>
    iterator emplace(const_iterator cpos, Args&&... args){
      // underlying memory might change, but offset will stay the same
      size_t offset = cpos - cbegin();
      // grow if necessary
      if(_size == _capacity){
        grow_capacity(capacity_from_size(_size + 1));
      }
      // recover iterator to desired position in memory
      iterator pos = begin() + offset;
      // copy over data, unless we're inserting at the end
      if(pos != end()){
        std::copy_backward(pos, end(), end() + 1);
      }
      // insert new data
      std::allocator_traits<allocator_type>::construct(_alloc, pos, std::forward<Args>(args)...);
      _size += 1;
      return pos;
    }
    void swap(vector& other){
      // check that allocators are swappable
      if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_swap::value){
        swap(_alloc, other._alloc);
      } else if constexpr (std::allocator_traits<allocator_type>::is_always_equal::value){
        assert(_alloc == other._alloc);
      } else {
        throw std::exception();
      }
      std::swap(_size, other._size);
      std::swap(_capacity, other._capacity);
      std::swap(_data, other._data);
    }
  private:
    // update capacity to be at least new capacity
    // no-op if new capacity is less than or equal to current capacity
    void grow_capacity(size_type new_capacity){
      if(new_capacity > _capacity){
        realloc_capacity(new_capacity);
      }
    }
    // shrink capacity to be exactly new capacity
    // no-op if new capacity is greater than or equal to current capacity
    void shrink_capacity(size_type new_capacity){
      if(new_capacity < _capacity){
        realloc_capacity(new_capacity);
      }
    }

    // update capacity to be exactly capacity
    void realloc_capacity(size_type new_capacity){
      // allocate new memory
      T* new_data = _alloc.allocate(new_capacity);
      // copy over old data
      size_type copy_len = std::min(_size, new_capacity);
      std::uninitialized_move(begin(), begin() + copy_len, new_data);
      // deallocate old data
      _alloc.deallocate(_data, _size);
      // set new data
      _data = new_data;
      _capacity = new_capacity;
      _size = std::min(_size, _capacity);
    }
  };
}

#endif
