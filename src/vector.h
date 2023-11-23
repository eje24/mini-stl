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
      size_t res = size & (size - 1);
      if(res){
        // not power of two
        return res << 1; 
      }else{
        // otherwise, return twice the size
        return size << 1;
      }
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



    // Element Access
    T& operator[](const std::size_t idx){
      // hopefully this returns a reference?
      return _data[idx];
    }
    
    // Iterators

    // Capacity
    size_type size(){
      return _size;
    }

    size_type capacity(){
      return _capacity;
    }

    const allocator_type& allocator(){
      return _alloc;
    }

    // Modifiers
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

  };
}

