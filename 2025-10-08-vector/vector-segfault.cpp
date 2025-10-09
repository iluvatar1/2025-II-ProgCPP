// g++ -g -fsanitize=address
#include <numeric>
#include <algorithm>
#include <iostream>
#include <array>

int main(void)
{
  const int N = 10;
  //double data[N] {0};
  std::array<double, N> data;

  std::cout << "size: " << data.size() << std::endl;
  std::cout << "max_size: " << data.max_size() << std::endl;
  std::cout << "&data[0]: " << &data[0] << std::endl;
  std::cout << "&data[1]: " << &data[1] << std::endl;
  std::cout << "&data[2]: " << &data[2] << std::endl;
  //std::cout << "&data[10]: " << &data[10] << std::endl;


  std::cout << data[10] << std::endl; // detected by sanitizers address

// initialize the array with even numbers
  int ii = 0 ;
  auto init  = [&ii](double & x){ x = 2*ii; ii++; };
  std::for_each(data.begin(), data.end(), init);

// print the array
  auto print = [](const int & x) { std::cout << x << "  " ; };
  std::for_each(data.begin(), data.end(), print);
  std::cout << "\n";

// compute mean
  double avg = std::accumulate(data.begin(), data.end(), 0.0)/data.size();
  std::cout << "Average = " << avg << std::endl;
}