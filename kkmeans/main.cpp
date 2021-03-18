#include <cmath>
#include <iostream>
#include <vector>

#include <dlib/clustering.h>

const char separator = ';';
const char* cluster = "cluster";

int main(int argc, char** argv)
{
  try
  {
    if(argc != 2)
    {
      std::cout << "number of clusters is required as an argument\n";
      return 1;
    }

    unsigned int n = std::stoi(argv[1]);

    typedef dlib::matrix<float,2,1> sample_type;
    typedef dlib::radial_basis_kernel<sample_type> kernel_type;

    dlib::kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8);
    dlib::kkmeans<kernel_type> instance(kc);

    std::vector<sample_type> samples;
    std::vector<sample_type> initial_centers;

    float x, y;
    char sep;
    sample_type m;
    while(std::cin >> x >> sep >> y && sep == separator)
    {
      m(0) = x;
      m(1) = y;
      samples.push_back(m);
    }

    instance.set_number_of_centers(n);
    dlib::pick_initial_centers(n, initial_centers, samples, instance.get_kernel());
    instance.train(samples, initial_centers);

    for (unsigned long i = 0; i < samples.size()/n; ++i)
        std::cout << samples[i](0) << separator << samples[i](1) << separator << cluster << instance(samples[i]) << std::endl;

  }
  catch(std::exception& ex) { std::cerr << ex.what() << std::endl; }
  
  return 0;
}
