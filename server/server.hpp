#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <string_view>

#include "handler.hpp"

#define MAX_PACKET_SIZE 4096

namespace nett
{
  using boost::asio::ip::tcp;
  
  class connection : public boost::enable_shared_from_this<connection>
  {
  public:
    using pointer = boost::shared_ptr<connection>;

    static pointer create(tcp::socket socket, boost::shared_ptr<async_blk::Handler> h)
    {
      return pointer(new connection(std::move(socket), std::move(h)));
    }
    
    ~connection() = default;

    void receive() { read(); }

  private:
    connection(tcp::socket socket, boost::shared_ptr<async_blk::Handler> h)
    : m_socket(std::move(socket)),
      m_handler(h)
    {}
  
    void read()
    {
      auto self(shared_from_this());
      m_socket.async_read_some(boost::asio::buffer(m_data, MAX_PACKET_SIZE),
          [this, self](boost::system::error_code ec, std::size_t length)
          {
            if (!ec)
            {
              m_handler->handle(std::string{m_data, length});
              read();
            }
          });
    }

    tcp::socket                           m_socket;
    char                                  m_data[MAX_PACKET_SIZE];
    boost::shared_ptr<async_blk::Handler> m_handler;
  };
    
  class server
  {
  public:
    server(short unsigned int port, boost::asio::io_service& svc, boost::shared_ptr<async_blk::Handler> handler)
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
    boost::asio::io_service               m_svc;
    tcp::acceptor                         m_acceptor;
    boost::shared_ptr<async_blk::Handler> m_handler;
  };
} // namespace nett;
