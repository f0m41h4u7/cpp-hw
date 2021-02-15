#pragma once

#include <array>
#include <condition_variable>
#include <map>
#include <mutex>
#include <string_view>
#include <sstream>
#include <thread>
#include <queue>

namespace async_blk
{
  constexpr int threads_qty = 3;
  
  enum class Event 
  {
    Sleep,
    Write,
    Terminate
  };
  
  enum class StateType
  {
    Pending,
    Writing,
    Terminating,
    Stopped
  };
  
  class State
  {
  public:
    State() = default;
    ~State() = default;
    
    StateType m_type{StateType::Pending};
    bool m_done{false};
  };
  
  class Handler
  {
  public:
    Handler(std::size_t);
    ~Handler();

    void handle(std::string_view);
    void stop();
      
  private:
    void write();
    void stdoutWriter();
    void fileWriter();
    
    std::size_t m_default_size{1};
    std::size_t m_counter{0};
    bool m_block_started{false};

    std::map<std::thread::id, State> m_threadStates;
    std::array<std::thread, threads_qty> m_threads;
    
    std::mutex m_mutex;
    std::condition_variable m_cv;
    
    std::queue<Event> m_events;
    
    std::stringstream m_lines;
  };
  
} //namespace async_blk
