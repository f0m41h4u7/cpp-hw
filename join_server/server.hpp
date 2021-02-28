#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <iostream>
#include <string_view>

#define MAX_PACKET_SIZE 4096

namespace nett
{
  using boost::asio::ip::tcp;
  
  using handler_t = std::function<std::string(std::string_view)>;
  
  class connection : public boost::enable_shared_from_this<connection>
  {
  public:
    using pointer = boost::shared_ptr<connection>;

    static pointer create(tcp::socket socket, handler_t h) { return pointer(new connection(std::move(socket), h)); }
    ~connection() = default;

    void receive() { handle(); }

  private:
    connection(tcp::socket socket, handler_t h)
    : m_socket(std::move(socket)),
      m_handler(h)
    {}
  
    void handle()
    {
      auto self(shared_from_this());
      m_socket.async_read_some(boost::asio::buffer(m_data, MAX_PACKET_SIZE),
          [this, self](boost::system::error_code ec, std::size_t length)
          {
            if (!ec)
            {
              auto res = m_handler(std::string{m_data, length});
              send(res, res.size());
            }
          });
    }

    void send(std::string_view sv, std::size_t length)
    {
      auto self(shared_from_this());
      boost::asio::async_write(m_socket,
                               boost::asio::buffer(sv.data(), length),
                               [this, self](boost::system::error_code ec, std::size_t)
                               {
                                 if (!ec) handle();
                               });
    }

    tcp::socket m_socket;
    char        m_data[MAX_PACKET_SIZE];
    handler_t   m_handler;
  };
    
  class server
  {
  public:
    server(short unsigned int port, boost::asio::io_service& svc, handler_t handler)
    : m_acceptor(svc, tcp::endpoint(tcp::v4(), port)),
      m_handler(handler)
    {
      listenAndServe();
    }
    
    ~server() = default;
    
    void listenAndServe()
    {
      m_acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            auto conn = connection::create(std::move(socket), m_handler);
            conn->receive();
          }
          listenAndServe();
        }
      );
    }
  
  private:
    boost::asio::io_service m_svc;
    tcp::acceptor           m_acceptor;
    handler_t               m_handler;
  };
} // namespace nett;
