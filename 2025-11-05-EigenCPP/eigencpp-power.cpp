#include <iostream>
#include <string>
#include <eigen3/Eigen/Dense>
#include <complex>

void mypow(Eigen::MatrixXd & M, int p, Eigen::MatrixXcd & R);

int main(int argc, char **argv) {
  const int N = std::stoi(argv[1]);
  const int K = std::stoi(argv[2]);

  Eigen::MatrixXd A = Eigen::MatrixXd::Random(N,N);
  std::cout << "Here is a random matrix, A:" << std::endl 
            << A << std::endl << std::endl;

  Eigen::MatrixXcd B; // = Eigen::MatrixXcd::Zero(N,N);;
  mypow(A, 1, B);
  std::cout << B << "\n\n";
  mypow(A, 6, B);
  std::cout << B << "\n\n";
  mypow(A, 16, B);
  std::cout << B << "\n\n";


  return 0;
}

void mypow(Eigen::MatrixXd & M, int p, Eigen::MatrixXcd & R)
{
    Eigen::EigenSolver<Eigen::MatrixXd> es(M);
    Eigen::VectorXcd v = es.eigenvalues();
    for(int ii = 0; ii < v.size(); ii++) {
        v[ii] = std::pow(v[ii], p);
    }
    Eigen::MatrixXcd D = v.asDiagonal();
    Eigen::MatrixXcd V = es.eigenvectors();
    R = V*D*V.inverse();
}
