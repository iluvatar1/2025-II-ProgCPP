# include <iostream>
# include <eigen3/Eigen/Dense>
# include <string>
# include <chrono>

int main(int argc, char **argv)
{
    const int N = std::stoi(argv[1]);

    Eigen::MatrixXd A = Eigen::MatrixXd::Random(N, N);
    Eigen::VectorXd b = Eigen::VectorXd::Random(N);;
    //std::cout.precision(16);
    //std::cout.setf(std::ios::scientific);

    //std::cout << "Here is the matrix A:\n" << A << std::endl;
    //std::cout << "Here is the vector b:\n" << b << std::endl;

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();   
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
    // Stop timing
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time spent solving: " << elapsed.count() << " s\n";

    //std::cout << "The solution is:\n" << x << std::endl;
    std::cout << (A*x - b).norm()/b.norm() << "\n";
    return 0;
}