#include <iostream>
#include <string>

void print_numbers(int nmin, int nmax);

int main(int argc , char **argv) {
    int NMIN = std::stoi(argv[1]);
    int NMAX = std::stoi(argv[2]);
    print_numbers(NMIN, NMAX);

  return 0;
}

void print_numbers(int nmin, int nmax)
{
  for (int i = nmin; i <= nmax; i++) {
    if (i % 3 == 0 and i % 7 == 0) {
      std::cout << i << ' ';
    }
  }
  std::cout << "\n";
}