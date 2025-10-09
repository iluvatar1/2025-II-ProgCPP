#include <print>
#include <vector>
#include <numeric>

// This program creates an array, fills it with the square of its indices,
// and calculates the sum of all its elements.

int main() {
    // Define the size of the array.
    const int ARRAY_SIZE = 2000000000;

    // Use std::vector for dynamic array management, which is safer for large sizes.
    // We are now using 'double' for the vector elements.
    std::vector<double> numbers(ARRAY_SIZE, 0.0);

    // Initialize a variable to store the sum of the elements.
    double totalSum = 0.0;

    // Loop through the array to populate it.
    // numbers[i] is set to i*i.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        // We cast 'i' to 'double' before multiplication to ensure floating-point arithmetic.
        numbers[i] = static_cast<double>(i) * i;
    }

    // Loop through the array again to calculate the sum.
    // This could be combined with the loop above, but separating them can be clearer.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        totalSum += numbers[i];
    }
    
    // An alternative way to sum using the <numeric> header:
    // double totalSum = std::accumulate(numbers.begin(), numbers.end(), 0.0);

    // Print the final sum to the console using std::print (C++23).
    std::print("The total sum of the {} elements is: {}\n", ARRAY_SIZE, totalSum);

    return 0;
}

