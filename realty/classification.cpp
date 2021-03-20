#include <cmath>
#include <iostream>
#include <map>
#include <vector> 

#include "common.hpp"

int main(int argc, char** argv)
{
  try
  {
    if(argc != 2)
    {
      std::cerr << "model filename is required as an argument\n";
      return 1;
    }
    std::string fname = argv[1];
    
    std::ifstream in(fname + results_file_postfix);
    if(!in)
    {
      std::cerr << "failed to open file " << fname << results_file_postfix << std::endl;
      return 1;
    }
    
    std::map<int, std::vector<sample_t>> results;
    char sep;
    int cluster;
    for(std::string line; std::getline(in, line);)
    {
      if (!line.empty())
      {
        sample_t m;
        std::stringstream stream(std::move(line));
        stream >> cluster >> sep >> m(0) >> sep >> m(1) >> sep
              >> m(2) >> sep >> m(3) >> sep >> m(4) >> sep
              >> m(5) >> sep >> m(6);
        results[cluster].push_back(m);
      }
    }
    in.close();

    dlib::one_vs_one_decision_function<ovo_trainer,
                                      dlib::decision_function<poly_kernel>,
                                      dlib::decision_function<rbf_kernel>> df;
    dlib::deserialize(fname + model_file_postfix) >> df;

    for(std::string line; std::getline(std::cin,line);)
    {
      sample_t m;
      std::stringstream stream(std::move(line));
      stream >> m(0) >> sep >> m(1) >> sep >> m(2) >> sep >> m(3)
            >> sep >> m(4) >> sep >> m(5) >> sep >> m(6);

      auto predicted = results[(int) df(m)];
      std::sort(predicted.begin(), predicted.end(),
        [&](const auto& lhs, const auto& rhs)
        {
          return (pow(lhs(0) - m(0),2) + pow(lhs(1) - m(1),2)) < 
                (pow(rhs(0) - m(0),2) + pow(rhs(1) - m(1),2));
        }
      );
      
      for(const auto& p : predicted)
        std::cout << p(0) << separator << p(1) << separator << (int) p(2) << separator
                  << (int) p(3) << separator << p(4) << separator << p(5) << separator
                  << (int) p(6) << newline;
    }

  }
  catch(std::exception& ex) { std::cerr << ex.what() << std::endl; }
  
  return 0;
}
