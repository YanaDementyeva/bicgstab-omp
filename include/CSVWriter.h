#pragma once


#include <fstream>


class CSVWriter {
    std::ofstream fs;
public:
    CSVWriter() {
        fs.open("data.csv");
        fs << "Size,Parallel BiCGStab (2CORES),Eigen BiCGStab (2CORES),";
        fs << "Parallel BiCGStab (4CORES),Eigen BiCGStab (4CORES),Sequential BiCGStab";
        fs << std::endl;
    }

    template <typename T>
    CSVWriter& operator<<(const T& x) {
        fs << x;
        return (*this);
    }

    CSVWriter& endl() {
        fs << std::endl;
        return (*this);
    }

    ~CSVWriter() noexcept {
        fs.close();
    }
};