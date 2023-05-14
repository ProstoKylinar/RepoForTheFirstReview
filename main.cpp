#include "mat.hpp"


/*
    Matrix<double> operator!() {
        if (n_ == m_) {
            Matrix<double> res = this->E(n_);
            for (int i = 0; i < n_; ++i) {
                if (arr_[i][i] == 0) {
                    bool flag = true;
                    for (int j = i + 1; j < n_; ++j) {
                        if (arr_[j][i] != 0) {
                            flag = false;
                            res.E1(i, j);
                            this->E1(i, j);
                            break;
                        }
                    }
                    if (flag) {
                        NulDet el;
                        throw el;
                    }
                }
                res.E2(i, (1 / arr_[i][i]));
                this->E2(i, (1 / arr_[i][i]));
                for (int j = 0; j < n_; ++j) {
                    if (i == j)
                        continue;
                    double value = arr_[j][i];
                    this->E3(j, i, (-1) * value);
                    res.E3(j, i, (-1) * value);
                }
            }
            return res;
        }
        NSquareMatrix error;
        throw error;
    }


  */

int main() {
    Matrix<double> N;
    size_t n = N.Get_size();
    //Matrix<int> Minor = N.get_minor_of_matrix(n, 0, 1);
    double det = N.Det(n);
    std::cout << det << std::endl;
    std::cout << !N << std::endl;
    return 0;
}


