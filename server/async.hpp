#pragma once

#include "handler.cpp"
#include "server.hpp"

namespace async_blk
{
  void run_server(std::size_t bulk, short unsigned int port)
  {
    try
    {
      boost::shared_ptr<Handler> h(new Handler(bulk, port));
      
      boost::asio::io_service svc;
      nett::server server(port, svc, h);

      svc.run();
    }
    catch(std::exception& e) { std::printf("exception: %s\n", e.what()); }
  }
} // namespace async_blk
