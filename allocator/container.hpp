#pragma once

#include <cassert>
#include <memory>
#include <utility>

template<
  class T,
  class Allocator = std::allocator<T>
> class List
{
  template<class U>
  class Node
  {
    Node<U>* m_next{nullptr};
    U        m_value;

  public:
    Node() = default;
  
    template <class... Args>
    Node(Args&&... args) :
      m_next(nullptr),
      m_value(std::forward<Args>(args)...)
    {}

    ~Node() { m_next = nullptr; }

    U& get() { return m_value; }
    Node<U>* next() { return m_next; }
    void set_next(Node<U>* ptr) { m_next = ptr; }
  };

  std::size_t m_size{0};
  Node<T>*    m_tail{nullptr};
  Node<T>     m_head;

  using NodeAllocator = typename Allocator::rebind<Node<T>>::other;
  NodeAllocator* m_alloc;

public:
  List() { m_alloc = new NodeAllocator(); m_tail = &m_head; }

  ~List()
  { 
    auto node = m_head.next();
    while (node)
    {
        auto nextNode = node->next();
        m_alloc->deallocate(node, 1);
        m_alloc->destroy(node);
        node = nextNode;
    }
  }

  std::size_t size() const { return m_size; }

  template <class... Args>
  void push_back(Args&&... args)
  {
    auto n = m_alloc->allocate(1);
    m_alloc->construct(n, std::forward<Args>(args)...);
    m_tail->set_next(n);
    m_tail = n;
    m_size++;
  }

  class iterator
  {
    Node<T>* m_ptr;

  public:
    iterator(Node<T>* ptr) : m_ptr(ptr) {}
    Node<T>* get_node() { return m_ptr; }

    iterator operator ++ () { m_ptr = m_ptr->next(); return *this; }
    T& operator * () { return m_ptr->get(); }
    bool operator == (const iterator& rhs) { return m_ptr == rhs.m_ptr; }
    bool operator != (const iterator& rhs) { return m_ptr != rhs.m_ptr; }
  };

  iterator begin() { return iterator(m_head.next()); }
  iterator end() { return iterator(m_tail->next()); }
};
