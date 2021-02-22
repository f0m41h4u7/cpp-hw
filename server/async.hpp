#pragma once

#include <boost/asio/streambuf.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>
#include <cstdio>

#include "handler.cpp"

namespace async_blk
{
  using boost::asio::ip::tcp;
  using boost::asio::awaitable;
  using boost::asio::co_spawn;
  using boost::asio::detached;
  using boost::asio::use_awaitable;
  namespace this_coro = boost::asio::this_coro;
  
  awaitable<void> session(std::shared_ptr<Handler> h, tcp::socket socket)
  {
    try
    {
      for (;;)
      {
        boost::asio::streambuf b;
        boost::asio::streambuf::mutable_buffers_type bufs = b.prepare(1024);
        std::size_t n = co_await socket.async_read_some(bufs, use_awaitable);
        b.commit(n);
        h->handle(&b);
      }
    }
    catch (std::exception& e)
    {
      std::printf("%s\n", e.what());
    }
  }

  awaitable<void> listen(std::shared_ptr<Handler> h, short unsigned int port)
  {
    auto executor = co_await this_coro::executor;
    tcp::acceptor acceptor(executor, {tcp::v4(), port});
    for (;;)
    {
      tcp::socket socket = co_await acceptor.async_accept(use_awaitable);
      co_spawn(executor, session(h, std::move(socket)), detached);
    }
  }

  void run_server(std::size_t bulk, short unsigned int port)
  {
    try
    {
      auto h = std::make_shared<Handler>(bulk, port);
      
      boost::asio::io_context ctx;
      boost::asio::signal_set signals(ctx, SIGINT, SIGTERM);
      signals.async_wait([&](auto, auto){ ctx.stop(); h->stop(); });
      
      co_spawn(ctx, listen(h, port), detached);

      ctx.run();
    }
    catch(std::exception& e) { std::printf("exception: %s\n", e.what()); }
  }
} // namespace async_blk
