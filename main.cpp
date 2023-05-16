#include "mat.hpp"

int main() {
    Matrix<double> N;
    size_t n = N.Get_size();
    //Matrix<int> Minor = N.get_minor_of_matrix(n, 0, 1);
    double det = N.Det(n);
    std::cout << det << std::endl;
    std::cout << !N << std::endl;
    return 0;
}


