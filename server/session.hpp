#pragma once

#include <boost/asio/spawn.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/unyield.hpp>
#include <boost/asio/steady_timer.hpp>

#include "handler.hpp"

namespace async_blk
{
  using boost::asio::ip::tcp;
  using boost::asio::awaitable;
  using boost::asio::co_spawn;
  using boost::asio::detached;
  using boost::asio::use_awaitable;
  namespace this_coro = boost::asio::this_coro;
  
  constexpr int max_length = 1024;  
  
  struct session : public std::enable_shared_from_this<session>
  {
  public:
    session(tcp::socket socket, std::shared_ptr<Handler> h)
      : m_socket(std::move(socket)), m_handler(h)
    {}

    void start()
    {
      auto self(shared_from_this());
      boost::asio::streambuf::mutable_buffers_type bufs = m_buf.prepare(1024);
      m_socket.async_read_some(bufs, [this, self](boost::system::error_code ec, std::size_t length)
          {
            if (ec)
              return;
            {
              m_buf.commit(length);
              m_handler->handle(&m_buf);
            }
          });
    }

    tcp::socket m_socket;
    std::shared_ptr<Handler> m_handler;
    boost::asio::streambuf m_buf;
  };

  class server
  {
  public:
    server(boost::asio::io_context& io_context, short unsigned int port, std::shared_ptr<Handler> h)
      : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)), m_handler(h)
    {
      do_accept();
    }

  private:
    void do_accept()
    {
      m_acceptor.async_accept(
          [this](boost::system::error_code ec, tcp::socket socket)
          {
            if (!ec)
            {
              std::make_shared<session>(std::move(socket), m_handler)->start();
            }

            do_accept();
          });
    }

    tcp::acceptor m_acceptor;
    std::shared_ptr<Handler> m_handler;
  };
  
  /*
  class Session : public std::enable_shared_from_this<Session>
  {
  public:
    explicit Session(boost::asio::io_context& ctx, tcp::socket socket, std::shared_ptr<Handler> h)
      : socket_(std::move(socket)),
        timer_(ctx),
        strand_(ctx.get_executor()),
        m_handler(h)
    {}
    ~Session() = default;

    void go()
    {
      auto self(shared_from_this());
      boost::asio::spawn(strand_,
          [this, self](boost::asio::yield_context yield)
          {
            try
            {
              char data[max_length];
              for (;;)
              {
               // timer_.expires_from_now(std::chrono::seconds(100));
                std::size_t n = socket_.async_read_some(boost::asio::buffer(data), yield);
                m_handler->handle(data);
              }
            }
            catch (std::exception& e)
            {
              std::cout << e.what();
              socket_.close();
             // timer_.cancel();
            }
          });
    }

  private:
    tcp::socket socket_;
    boost::asio::steady_timer timer_;
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    std::shared_ptr<Handler> m_handler;
  };*/
  
} //namespace async_blk
