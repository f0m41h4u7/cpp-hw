#pragma once

#include <iostream>
#include <map>
#include <tuple>
#include <type_traits>

template< typename T >
using is_int = std::enable_if_t< std::is_integral_v< T >, bool >;

template <class T, T default_value, is_int<T> = true>
class Matrix
{
public:
  using matrix_map = std::map<const std::pair<std::size_t, std::size_t>, T>;
  using matrix_tuple = std::tuple<std::size_t, std::size_t, T>;

  Matrix() = default;
  ~Matrix() = default;

  class value_proxy
  {
  public:
    value_proxy(Matrix* m, std::size_t row, std::size_t col)
      : m_pMatrix(m),
        m_row(row),
        m_col(col)
    { m_value = m_pMatrix->get(m_row, m_col);}

    ~value_proxy() = default;

    bool operator == (const int int_val) const { return m_value == int_val; }
    bool operator != (const int int_val) const { return m_value != int_val; }

    value_proxy& operator = (T value)
    {
      m_value = value;
      m_pMatrix->set(m_row, m_col, value);

      return *this;                                            
    }

    friend std::ostream& operator<<(std::ostream& os, value_proxy&& v)
    {
      os << v.m_value;
      return os;          
    }

    friend T Matrix::get(std::size_t row, std::size_t col);
    friend void Matrix::set(std::size_t, std::size_t, T);

  private:
    std::size_t m_row{0};
    std::size_t m_col{0};

    T m_value;

    Matrix<T, default_value>* m_pMatrix;
  };

  class proxy
  {
  public:
    proxy(Matrix* m, std::size_t row) : m_pMatrix(m), m_row(row){}
    ~proxy() = default;

    value_proxy operator[] (std::size_t col) { return value_proxy(m_pMatrix, m_row, col); }

  private:
    std::size_t m_row{0};
    Matrix<T, default_value>* m_pMatrix;
  };

  class iterator
  {
  public:
    iterator(matrix_map::iterator&& it) : m_iter(it) {}
    ~iterator() = default;

    iterator operator++() { m_iter++; return *this; }

    bool operator==(const iterator& other) const { return m_iter == other.m_iter;  }
    bool operator!=(const iterator& other) const { return m_iter != other.m_iter;  }

    const matrix_tuple operator*() const
    {
      return std::forward_as_tuple(
        (*m_iter).first.first,
        (*m_iter).first.second,
        (*m_iter).second                                                           
      );
    }

  private:
    matrix_map::iterator m_iter;
  };

  iterator begin() { return iterator(m_items.begin()); }
  iterator end() { return iterator(m_items.end()); }

  proxy operator[] (std::size_t row) { return proxy(this, row); }

  std::size_t size() const { return m_items.size(); }

private:
  T get(std::size_t row, std::size_t col)
  {
    const std::pair<std::size_t, std::size_t> p(row, col);
    if(!m_items.contains(p)) return default_value;
    return m_items[p];
  }

  void set(std::size_t row, std::size_t col, T val)
  {
    const std::pair<std::size_t, std::size_t> p(row, col);
    if(val == default_value) m_items.erase(p);
    else m_items[p] = val;
  }

  matrix_map m_items;
};
