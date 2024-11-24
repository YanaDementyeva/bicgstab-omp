#include <gtest/gtest.h>
#include "ParallelOperations.h"
#include <iostream>
#include <omp.h>
#include <Eigen>
#include <chrono>

using namespace std;
using namespace Eigen;
using namespace chrono;

// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
  
//   return RUN_ALL_TESTS();
// }

int main(int argc, char** argv) {
  // Eigen::initParallel();
  int n = 10000;
  VectorXd x(n), b(n);
  SparseMatrix<double, Eigen::RowMajor> A(n,n);
  for (int i = 0; i < n; i++) {
    A.insert(i, i) = static_cast<double>(i) + 123.172 + i*i;
    if (i > 0 && i < n - 1) {
      A.insert(i, i + 1) = i*i + 973.1;
      A.insert(i, i - 1) = i*i + 324.12324;
    }
  }
  b = VectorXd::Ones(n);

  auto begin_eigen = high_resolution_clock::now();
  BiCGSTAB<SparseMatrix<double, Eigen::RowMajor>> solver;
  solver.compute(A);
  VectorXd y = solver.solve(b);
  auto end_eigen = high_resolution_clock::now();
  duration<double> time_eigen = end_eigen - begin_eigen;
  std::cout << "TIME EIGEN " << time_eigen.count() << std::endl;

  auto begin_parallel = high_resolution_clock::now();
  VectorXd z = ParallelOperations::BiCGStab(A, b, solver.tolerance(), solver.maxIterations());
  auto end_parallel = high_resolution_clock::now();
  duration<double> time_parallel = end_parallel - begin_parallel;
  std::cout << "TIME PARALLEL " << time_parallel.count() << std::endl;



  
  // for (int i = 0; i < n; i++) {
  //   std::cout << "Eigen " << y[i] << "    Me " << z[i] << std::endl;
  // }


  // auto begin_eigen = high_resolution_clock::now();
  // VectorXd y = A * b;
  // auto end_eigen = high_resolution_clock::now();
  // duration<double> time_eigen = end_eigen - begin_eigen;
  // std::cout << "TIME EIGEN " << time_eigen.count() << std::endl;
  // // std::cout << "#iterations:     " << solver.iterations() << std::endl;
  // // std::cout << "estimated error: " << solver.error()      << std::endl;
  // // std::cout << "TIME " << t << std::endl; 
  // auto begin_parallel = high_resolution_clock::now();
  // VectorXd z = ParallelOperations::mv_product(A, b);
  // auto end_parallel = high_resolution_clock::now();
  // duration<double> time_parallel = end_parallel - begin_parallel;
  // std::cout << "TIME PARALLEL " << time_parallel.count() << std::endl;
  // std::cout << "WIN " << time_eigen.count()/time_parallel.count() << std::endl;

  assert((y - z).squaredNorm() < 1e-2);
  // for (int i = 0; i < n; i++) {
  //   std::cout << x[i] << " " << std::endl;
  // }
}