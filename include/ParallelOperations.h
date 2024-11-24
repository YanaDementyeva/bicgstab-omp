#pragma once

#include <iostream>
#include <omp.h>
#include <Eigen>
#include <chrono>

using namespace std;
using namespace Eigen;

class ParallelOperations
{   
    private:
        static const int round_robin_cycle = 1;
    public:
        ParallelOperations() = delete;
        static VectorXd mv_product(const SparseMatrix<double, Eigen::RowMajor>& A,
                                         const VectorXd& v);
        static VectorXd BiCGStab(const SparseMatrix<double, Eigen::RowMajor>& A,
                                 const VectorXd& b,
                                 const double& tolerance,
                                 const int& max_iter);
};

