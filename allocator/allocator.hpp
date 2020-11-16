#pragma once

#include <new>
#include <utility>

template <typename T, std::size_t limit>
class Allocator
{
public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  Allocator() { new(m_pool) value_type[limit]; }
  ~Allocator(){}

  template <typename U>
  Allocator(const Allocator<U, limit>&);

  template<typename U>
  struct rebind { using other = Allocator<U, limit>;};

  pointer allocate(std::size_t n = 1)
  {
    if (n > limit - m_offset) throw std::bad_alloc{};
    pointer ptr = &m_pool[m_offset];
    m_offset += n;
    return ptr;
  }

  void deallocate(pointer p, std::size_t n = 1)
  {
    if (n > m_offset) throw std::bad_alloc{};
    m_offset -= n;
  }

  template<typename U, typename ...Args>
  void construct(U *p, Args &&...args)
  {
    new(p) U(std::forward<Args>(args)...);
  }

  void destroy(pointer p) { p->~T(); }

private:
  std::size_t m_offset{0};
  value_type  m_pool[limit];
};
