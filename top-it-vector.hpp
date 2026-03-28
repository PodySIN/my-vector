#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>

namespace topit {
  template< class T >
  class Vector {
    public:
      ~Vector();
      Vector();
      Vector(const Vector< T >&);
      Vector(size_t size, const T& init);
      Vector(size_t size, const T* arr);
      Vector(Vector< T >&&) noexcept;
      Vector< T >& operator=(const Vector< T >&);
      Vector< T >& operator=(Vector< T >&&);

      T& operator[](size_t index) noexcept;
      const T& operator[](size_t index) const noexcept;

      bool isEmpty() const noexcept;
      size_t getSize() const noexcept;
      size_t getCapacity() const noexcept;

      void reallocate(size_t capacity);
      void swap(Vector< T >& rhs) noexcept;
      void pushBack(const T& v);
      void popBack();
      void insert(size_t pos, const T* v);
      void erase(size_t pos);
      T& at(size_t index);
      const T& at(size_t index) const;
    private:
      explicit Vector(size_t size);
      T* data_;
      size_t size_, capacity_;
  };

  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
topit::Vector< T >::Vector(size_t size, const T* arr):
  Vector(size)
{
  for (size_t i = 0; i < size; i++) {
    try {
      data_[i] = arr[i];
    } catch (...) {
      delete[] data_;
      throw;
    }
  }
}

template< class T >
topit::Vector< T >::Vector(size_t size, const T& init):
  Vector(size)
{
  for (size_t i = 0; i < size; i++) {
    try {
      data_[i] = init;
    } catch (...) {
      delete[] data_;
      throw;
    }
  }
}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); i++) {
    data_[i] = rhs[i];
  }
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  Vector< T > cpy{rhs};
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy{std::move(rhs)};
  swap(cpy);
  return *this;
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return size_ == 0;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
void topit::Vector< T >::reallocate(size_t capacity)
{
  T* data = new T[capacity];
  for (size_t i = 0; i < size_; i++) {
    data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = data;
  capacity_ = capacity;
}

template< class T >
void topit::Vector< T >::pushBack(const T& v)
{
  if (size_ >= capacity_) {
    size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reallocate(new_capacity);
  }
  data_[size_] = std::move(v);
  ++size_;
}

template< class T >
void topit::Vector< T >::popBack()
{
  if(size_ > 0) {
    size_--;
    data_[size_].~T();
  }
}

template< class T >
T& topit::Vector< T >::operator[](size_t index) noexcept
{
  return data_[index];
}

template< class T >
const T& topit::Vector< T >::operator[](size_t index) const noexcept
{
  return data_[index];
}

template< class T >
T& topit::Vector< T >::at(size_t index)
{
  const Vector< T >* cthis = this;
  return const_cast< T& >(cthis->at(index));
}

template< class T >
const T& topit::Vector< T >::at(size_t index) const
{
  if (index >= size_) {
    throw std::out_of_range("Bad index");
  }
  return data_[index];
}

template< class T >
bool topit::operator==(const Vector< T >& lhs, const Vector< T >& rhs)
{
  bool is_equal = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && is_equal; i++) {
    is_equal = is_equal && (lhs[i] == rhs[i]);
  }
  return is_equal;
}

#endif
