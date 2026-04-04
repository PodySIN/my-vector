#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace topit {
  template< class T >
  class Vector {
  public:
    ~Vector();
    Vector();
    Vector(const Vector< T >&);
    Vector(size_t size, const T& init);
    Vector(size_t size, const T* arr);
    explicit Vector(std::initializer_list< T >);
    Vector(Vector< T >&&) noexcept;
    Vector< T >& operator=(const Vector< T >&);
    Vector< T >& operator=(Vector< T >&&);

    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;
    
    Iterator< T > begin() const;
    CIterator< T > cbegin() const;
    Iterator< T > end() const;
    CIterator< T > cend() const;
    
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    
    void shrinkToFit();
    void reserve(size_t);
    void swap(Vector< T >& rhs) noexcept;
    void pushBack(const T& v);
    void pushBackCount(size_t k, const T& val);

    template< class IT >
    void pushBackRange(IT b, size_t k);

    void popBack();
    void insert(size_t pos, const T* v);
    void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end);
    void erase(size_t pos);
    void erase(size_t start, size_t end);
    T& at(size_t index);
    const T& at(size_t index) const;
  private:
    explicit Vector(size_t size);
    void unsafePushBack(const T& val);
    T* data_;
    size_t size_, capacity_;
  };

  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
}

template< class T >
topit::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t i = 0;
  for (auto it = il.begin(); it != il.end(); it++) {
    data_[i++] = *it;
  }
}

template< class T >
void topit::Vector< T >::reserve(size_t k)
{
  if (k == capacity_) {
    return;
  }
  size_t new_size = size_;
  if (size_ > k) {
    new_size = k;
  }
  T* new_data = new T[k];
  for (size_t i = 0; i < new_size; i++) {
    try {
      new_data[i] = data_[i];
    } catch (...) {
      delete[] new_data;
      throw;
    }
  }
  delete[] data_;
  data_ = new_data;
  size_ = new_size;
  capacity_ = k;
}

template< class T >
void topit::Vector< T >::shrinkToFit()
{
  reserve(size_);
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
  for (size_t i = 0; i < size_; i++) {
    data_[i].~T();
  }
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
topit::Iterator< T > topit::Vector< T >::begin() const
{
  return Iterator< T >{data_};
}

template< class T >
topit::Iterator< T > topit::Vector< T >::end() const
{
  return Iterator< T >{data_ + size_};
}

template< class T >
topit::CIterator< T > topit::Vector< T >::cbegin() const
{
  return CIterator< T >{data_};
}

template< class T >
topit::CIterator< T > topit::Vector< T >::cend() const
{
  return CIterator< T >{data_ + size_};
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
void topit::Vector< T >::pushBack(const T& v)
{
  if (size_ >= capacity_) {
    size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reserve(new_capacity);
  }
  data_[size_] = v;
  ++size_;
}

template< class T >
void topit::Vector< T >::unsafePushBack(const T& v)
{
  data_[size_] = v;
  size_++;
}

template< class T >
void topit::Vector< T >::pushBackCount(size_t k, const T& val)
{
  if (size_ + k >= capacity_) {
    size_t new_capacity = size_ + k;
    reserve(new_capacity);
  }
  for (size_t i = size_; i < size_ + k; i++) {
    unsafePushBack(val);
  }
}

template< class T >
template< class IT >
void topit::Vector< T >::pushBackRange(IT b, size_t k)
{
  if (size_ + k >= capacity_) {
    size_t new_capacity = size_ + k;
    reserve(new_capacity);
  }
  for (size_t i = 0; i < k; i++) {
    unsafePushBack(*b);
    b++;
  }
}

template< class T >
void topit::Vector< T >::popBack()
{
  if (size_ > 0) {
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
