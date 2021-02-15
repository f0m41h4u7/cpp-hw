#pragma once

#include "handler.cpp"

namespace async_blk
{
  using handle_t = Handler*;

  handle_t connect(std::size_t bulk)
  {
    return new Handler(bulk);
  }

  void receive(handle_t handler, std::string_view data)
  {
    handler->handle(data);
  }

  void disconnect(handle_t handler)
  { 
    handler->stop();
  }
} // namespace async_blk
