#include "ParallelOperations.h"

VectorXd ParallelOperations::mv_product(const SparseMatrix<double, Eigen::RowMajor>& A,
                                             const VectorXd& v) {
  int rows = A.rows();
  VectorXd res = VectorXd(rows);
#pragma omp parallel for schedule(static, round_robin_cycle)
  for (int row = 0; row < rows; row++) {
    double res_row = 0.0;
    for (SparseMatrix<double, Eigen::RowMajor>::InnerIterator it(A, row); it; ++it) {
      res_row += it.value() * v(it.col());
    }
    res[row] = res_row;
  }

  return res;
}

VectorXd ParallelOperations::BiCGStab(const SparseMatrix<double, Eigen::RowMajor>& A,
                                      const VectorXd& b, 
                                      const double& tolerance,
                                      const int& max_iter) {
  // std::cout << "TIME PARALLEL " << time_parallel.count() << std::endl;
    VectorXd old_x = VectorXd::Zero(A.cols());
    VectorXd new_x = old_x;
    VectorXd old_r = b - mv_product(A, old_x);
    VectorXd co_r_0 = old_r;
    VectorXd new_r = old_r;
    VectorXd p = old_r;

    int current_iter = 0;

    double tolerance2 = tolerance * tolerance * b.squaredNorm();

    while (new_r.squaredNorm() > tolerance2 && current_iter < max_iter) {
        VectorXd Ap = mv_product(A, p);
        double alpha = old_r.dot(co_r_0)/Ap.dot(co_r_0);
        VectorXd s = old_r - alpha*Ap;

        VectorXd As = mv_product(A, s);
        double omega = As.dot(s)/As.dot(As);
        new_x = old_x + alpha * p + omega * s;

        new_r = s - omega * As;
        double beta = (alpha * new_r.dot(co_r_0))/(omega * old_r.dot(co_r_0));
        p = new_r + beta * (p - omega * Ap);

        old_r = new_r;
        old_x = new_x;

        current_iter++;
    }

    return new_x;
}