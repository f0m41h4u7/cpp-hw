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

  Allocator()
  {
    new(m_pool) value_type[limit];
    for(std::size_t i = 0; i < limit; ++i)
      m_free_ptrs[i] = &m_pool[i];
  }

  ~Allocator(){}

  template <typename U>
  Allocator(const Allocator<U, limit>&);

  template<typename U>
  struct rebind { using other = Allocator<U, limit>;};

  pointer allocate(std::size_t n = 1)
  {
    if (n > m_offset+1) throw std::bad_alloc{};
    pointer ptr = m_free_ptrs[m_offset];
    m_offset -= n;
    return ptr;
  }

  void deallocate(pointer p, std::size_t n = 1)
  {
    if (n > limit-m_offset-1) throw std::bad_alloc{};
    for(std::size_t i = 0; i < n; ++i)
    {
      m_free_ptrs[m_offset+1] = p;
      m_offset++;
      p += sizeof(pointer);
    }
  }

  template<typename U, typename ...Args>
  void construct(U *p, Args &&...args)
  {
    new(p) U(std::forward<Args>(args)...);
  }

  void destroy(pointer p) { p->~T(); }

private:
  std::size_t m_offset{limit-1};
  value_type  m_pool[limit];
  pointer     m_free_ptrs[limit];
};
