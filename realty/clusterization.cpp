#include <cmath>
#include <iostream>
#include <vector>

#include "common.hpp"

int main(int argc, char** argv)
{
  try
  {
    if(argc != 3)
    {
      std::cerr << "number of clusters and filename are required as arguments\n";
      return 1;
    }

    unsigned int n = std::stoi(argv[1]);
    std::string fname = argv[2];
    
    std::vector<sample_t> samples;
    char sep;
    std::size_t floor, total_floors;
    for(std::string line; std::getline(std::cin,line);)
    {
      if(std::size_t p = line.find(empty_field); p != std::string::npos)
        line.insert(p, zero_str);
      
      if (!line.empty())
      {
        sample_t m;
        std::stringstream stream(std::move(line));
        stream >> m(0) >> sep >> m(1) >> sep >> m(2) >> sep
              >> m(3) >> sep >> m(4) >> sep >> m(5) >> sep
              >> floor >> sep >> total_floors;
        m(6) = (floor == 0 || floor == total_floors) ? 0 : 1;
        samples.push_back(m);
      }
    }
    
    dlib::kcentroid<rbf_kernel> kc(rbf_kernel(0.1),0.01, 8);
    dlib::kkmeans<rbf_kernel> test{kc};
    
    std::vector<sample_t> initial_centers;
    test.set_number_of_centers(n);
    dlib::pick_initial_centers(n, initial_centers, samples, test.get_kernel());
    test.train(samples, initial_centers);
    
    std::vector<double> results;
    results.reserve(samples.size());
    for (const auto& s : samples)
      results.emplace_back(test(s));

    std::ofstream out(fname + results_file_postfix);
    int i = 0;
    for (const auto& s : samples)
    {
      out << (int) results[i] << separator
          << s(0) << separator << s(1) << separator << (int) s(2) << separator
          << (int) s(3) << separator << s(4) << separator << s(5) << separator
          << (int) s(6) << newline;
      ++i;
    }
    
    ovo_trainer trainer;
    dlib::krr_trainer<rbf_kernel> rbf_trainer;
    dlib::svm_nu_trainer<poly_kernel> poly_trainer;
    rbf_trainer.set_kernel(rbf_kernel(0.1));
    poly_trainer.set_kernel(poly_kernel(0.1, 1, 2));

    trainer.set_trainer(rbf_trainer);
    trainer.set_trainer(poly_trainer, 1, 2);

    dlib::one_vs_one_decision_function<ovo_trainer> df = trainer.train(samples, results);
    dlib::one_vs_one_decision_function<ovo_trainer,
                                      dlib::decision_function<poly_kernel>,
                                      dlib::decision_function<rbf_kernel>> df2;
    df2 = df;
    dlib::serialize(fname + model_file_postfix) << df2;

  }
  catch(std::exception& ex) { std::cerr << ex.what() << std::endl; }
  
  return 0;
}
