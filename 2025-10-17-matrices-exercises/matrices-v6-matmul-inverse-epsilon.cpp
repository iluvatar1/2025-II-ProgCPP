#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <print>
#include <cassert>

void fill_matrix(std::vector<double> & data, int m, int n);
void print_matrix(const std::vector<double> & data, int m, int n);
void transpose_matrix(const std::vector<double> & indata, int m, int n,
                      std::vector<double> & outdata);
void fill_matrix_random(std::vector<double> & M, const int nrows, const int ncols, 
                        const int seed);
double trace(const std::vector<double> & data, int m, int n);
void matmul(const std::vector<double> & A, int mA, int nA, 
              const std::vector<double> & B, int mB, int nB,
              std::vector<double> & C
              );
bool check_inverse(const std::vector<double> & A, int mA, int nA,
                    const std::vector<double> & B, int mB, int nB,
                    double eps);


int main(int argc, char **argv)
{
  const int M = std::stoi(argv[1]);
  const int N = std::stoi(argv[2]);

  std::vector<double> A2d(M*N, 0.0); // original matrix
  std::vector<double> B2d(N*M, 0.0); // transpose
  std::vector<double> C2d; // result

  // setup original matrix
  fill_matrix(A2d, M, N);
  print_matrix(A2d, M, N);

  // tranpose
  transpose_matrix(A2d, M, N, B2d);
  print_matrix(B2d, N, M);
  
  // matmul
  matmul(A2d, M, N, B2d, N, M, C2d);
  print_matrix(C2d, M, M);

  return 0;
}

void fill_matrix(std::vector<double> & data, int m, int n)
{
  for (int ii = 0; ii < m; ++ii) {
    for (int jj = 0; jj < n; ++jj) {
      data[ii*n + jj] = ii*n+jj; // A_(i, j) = i*n + j = id
    }
  }
}

void print_matrix(const std::vector<double> & data, int m, int n)
{
  for (int ii = 0; ii < m; ++ii) {
    for (int jj = 0; jj < n; ++jj) {
      std::cout << data[ii*n + jj] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void transpose_matrix(const std::vector<double> & datain, int m, int n,
                      std::vector<double> & dataout)
{
  // TODO
  // redimensinar a dataout para que tenga tamanho m*n
  // for irow in [0, m)
  //  for icol in [0, n)
  //    dataout[jj][ii] = datain[ii*n + jj]

  dataout.resize(n*m);
  for(int irow = 0; irow < m; irow++) {
    for(int icol = 0; icol < n; icol++) {
        dataout[icol*m + irow] = datain[irow*n + icol];
    }
  }
}

void fill_matrix_random(std::vector<double> & M, const int nrows, const int ncols, const int seed){
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(-1, 1);
    for (int ii = 0; ii < nrows; ii++){
        for (int jj = 0; jj < ncols; jj++){
            M[ii*ncols + jj] = dis(gen);
        }
    }
}

double trace(const std::vector<double> & data, int m, int n)
{
    if (m != n) {
        std::println("ERROR: trace requires m == n, got {}, {}", m, n);
        return 0;
    }

    double suma = 0.0;
    for (int ii = 0; ii < m; ++ii) {
        suma += data[ii*n + ii];
    }
    return suma; 
}


void matmul(const std::vector<double> & A, int mA, int nA, 
              const std::vector<double> & B, int mB, int nB,
              std::vector<double> & C
              )
{
  // checks
  assert(nA == mB);

  // setup result matrix
  int mC = mA, nC = nB;
  C.resize(mC*nC);

  // matmul kernel
  for (int ic = 0; ic < mC; ic++) {
    for (int jc = 0; jc < mC; jc++) {
      C[ic*nC + jc] = 0.0;
      for(int k = 0; k < nA; ++k) {
        C[ic*nC + jc] += A[ic*nA + k]*B[k*nB + jc]; 
      }
    }
  }

}

bool check_inverse(const std::vector<double> & A, int mA, int nA,
                    const std::vector<double> & B, int mB, int nB,
                    double eps)
{
    
}
