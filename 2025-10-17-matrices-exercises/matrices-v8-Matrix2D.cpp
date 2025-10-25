#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <print>
#include <cassert>

// class declarations
//class Matrix2D;

// functions 
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
void test_inverse(int m, int n);

bool check_commute(const std::vector<double> & A, int mA, int nA,
                    const std::vector<double> & B, int mB, int nB,
                    double eps);
void test_commute(int m, int n);

// class impl
class Matrix2D
{
  public:
  int m{0}, n{0};
  std::vector<double> data;

  Matrix2D(int M, int N) {
    m = M;
    n = N;
    data.resize(m*n);
  }

  double & operator()(int i, int j) {
    return data[i*n + j];
  }
  
};



// functions for matrix2D
void print_matrix(const Matrix2D & data);



int main(int argc, char **argv)
{
  const int M = std::stoi(argv[1]);
  const int N = std::stoi(argv[2]);

  Matrix2D matriz(M, N);
  matriz(0, 0) = 1.9;
  matriz(M-1, N-1) = -9.876;

  print_matrix(matriz);

  return 0;
}

// class impl
class Matrix2D
{
  public:
  int m{0}, n{0};
  std::vector<double> data;

  Matrix2D(int M, int N) {
    m = M;
    n = N;
    data.resize(m*n);
  }

  double & operator()(int i, int j) {
    return data[i*n + j];
  }
  
};

// function impl
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
    // calculo la multiplicacion
    std::vector<double> R;
    matmul(A, mA, nA, B, mB, nB, R);
    print_matrix(R, mA, nB);

    // chequear elemento a elemento la condicion con la inversa
    int mC = mA;
    int nC = nB; 
    for(int irow = 0; irow < mC; ++irow){
        for(int icol = 0; icol < nC; ++icol){
            double I = (irow == icol) ? 1.0 : 0.0; 
            if (std::fabs(R[irow*nC + icol] - I) > eps) {
                return false;
            }
        }
    }
    return true;
}

void test_inverse(int m, int n)
{
  m = 2; n = 2;
  std::vector<double> A2d {2, 1, 4, 3}; // original matrix
  std::vector<double> B2d {3.0/2 + 1.0e-10, -1.0/2, -2.0, 1.0}; // inverse

  // setup original matrix
  print_matrix(A2d, m, n);
  print_matrix(B2d, n, m);

  bool flag1 = check_inverse(A2d, m, n, B2d, n, m, 1.0e-6);
  bool flag2 = check_inverse(B2d, n, m, A2d, m, n, 1.0e-6);
  std::println("{} {}", flag1, flag2);
}


bool check_commute(const std::vector<double> & A, int mA, int nA,
                    const std::vector<double> & B, int mB, int nB,
                    double eps)
{
    // checks
    assert(mA == nA);
    assert(mB == nB);
    assert(mA == nB);

    // calculo la multiplicacion
    std::vector<double> R1;
    matmul(A, mA, nA, B, mB, nB, R1);
    print_matrix(R1, mA, nB);
    std::vector<double> R2;
    matmul(B, mB, nB, A, mA, nA, R2);
    print_matrix(R2, mA, nB);

    // chequear elemento a elemento la condicion con la inversa
    for(int irow = 0; irow < mA; ++irow){
        for(int icol = 0; icol < nA; ++icol){
            if (std::fabs(R1[irow*nA + icol] - R2[irow*nA + icol]) > eps) {
                return false;
            }
        }
    }
    return true;
}


void test_commute(int m, int n)
{
  m = 2; n = 2;
  std::vector<double> A2d {2, 1, 0, 3}; // A
  std::vector<double> B2d {4 + 1.0e-4, 1, 0, 5}; // B

  // setup original matrix
  print_matrix(A2d, m, n);
  print_matrix(B2d, n, m);

  bool flag1 = check_commute(A2d, m, n, B2d, n, m, 1.0e-2);
  bool flag2 = check_commute(A2d, m, n, B2d, n, m, 1.0e-6);
  std::println("{} {}", flag1, flag2);
}

// matriz2d impl

void print_matrix(const Matrix2D & data)
{
  for (int ii = 0; ii < data.m; ++ii) {
    for (int jj = 0; jj < data.n; ++jj) {
      std::cout << data(ii, jj) << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
