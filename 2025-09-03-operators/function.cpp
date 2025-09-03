//#include <iostream>
#include <print> // compile with -std=c++23
#include <iostream>

// function declaration: name and types
double average(double a, double b); // a and b are LOCAL variables

// main function. Execution starts here
int main(int argc, char **argv) {
    double x{2.35};
    double y{4.987};
    double avg = average(x, y); // x value copied to a, y value copied to b, result of calling assigned to avg
    std::cout << "avg: " << avg << "\n";
    std::print("avg: {0:20.16f}\n", avg);
    std::printf("avg: %20.16e\n", avg);
    
    return 0;
}

// function implementation: how it does that
double average(double a, double b) 
{
    return (a+b)/2;
}