#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>

namespace topit {
  template< class T >
  class Vector {
    public:
      ~Vector();
      Vector();
      Vector(const Vector&);
      Vector(Vector&&);
      Vector& operator=(const Vector&);
      Vector& operator=(Vector&&);
      
      bool isEmpty() const noexcept;
      size_t getSize() const noexcept;
      size_t getCapacity() const noexcept;

      void reallocate(size_t capacity);
      void pushBack(const T& v);
      void popBack();
      void insert(size_t pos, const T* v);
      void erase(size_t pos);
    private:
      T* data_;
      size_t size_, capacity_;
  };
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

void topit::Vector< T >::reallocate(size_t capacity)
{
  T* data = new T[capacity];
  for (size_t i =0; i < size_; i++) {
    data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = data;
  capacity_ = capacity;
}

void topit::Vector< T >::pushBack(const T& v)
{
  if (size_ >= capacity_) {
    size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reallocate(new_capacity);
  }
  data_[size_] = std::move(value);
  ++size_;
}

void topit::Vector< T >::popBack()
{
  if(size_ > 0) {
    size_--;
    data_[size_].~T();
  }
}

#endif
