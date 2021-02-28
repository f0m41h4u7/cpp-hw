#include "cmd.hpp"
#include "server.hpp"
#include "storage.hpp"

int main(int argc, char** argv)
{
  try
  {
    if(argc != 2)
    {
      std::cout << "port is required as argument\n";
      return 1;
    }
    
    short unsigned int port = std::stoi(argv[1]);
    
    db::storage<2> storage;
    
    boost::asio::io_service svc;
    auto ctx = std::make_tuple(cmd::operation{}, std::string{}, std::size_t{}, std::string{});
    int table_id;
    
    nett::server s(port,
                   svc,
                   [&](std::string_view sv) -> std::string
                   {
                     tao::pegtl::memory_input<tao::pegtl::tracking_mode::eager> in{sv.data(), ""};
                     if(!tao::pegtl::parse<cmd::command, cmd::action>(in, ctx))
                       return cmd::parse_error.data();
                     
                     table_id = int(std::get<1>(ctx)[0])%65;
                     switch(std::get<0>(ctx))
                     {
                       case cmd::operation::INSERT:
                       {
                         int ec = storage.insert(table_id, std::get<2>(ctx), std::get<3>(ctx));
                         if (ec == 0)
                           return cmd::success_result.data();
                         else if (ec == 1)
                           return cmd::duplicate_error.data() + std::to_string(std::get<2>(ctx)) + "\n";
                         else
                           return cmd::table_error.data();
                       }
                       
                       case cmd::operation::TRUNCATE:
                       {
                         if(!storage.truncate(table_id))
                           return cmd::success_result.data();
                         else
                           return cmd::table_error.data();
                       }
                       
                       case cmd::operation::INTERSECT:
                       {
                         return storage.intersect() + cmd::success_result.data();
                       }
                       
                       case cmd::operation::SYMDIF:
                       {
                         return storage.symdif() + cmd::success_result.data();
                       }
                     }
                     
                     return cmd::unknown_error.data();
                   }
                  );
    svc.run();
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}
