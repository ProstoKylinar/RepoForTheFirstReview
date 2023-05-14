#ifndef MATRIX_MAT_HPP
#define MATRIX_MAT_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cmath>

template<typename T>
class Matrix {
    std::vector<std::vector<T>> data_;
    size_t n_ = 0u;
    size_t m_ = 0u;
public:

    Matrix(size_t n, size_t m) : n_(n), m_(m) {
        std::vector<T> a;
        for (size_t i = 0; i < n_; ++i) {
            data_.push_back(a);
            for (int j = 0; j < m_; ++j) {
                data_[i].push_back(0);
            }
        }
    }

    Matrix() {
        T value;
        std::cin >> n_ >> m_;
        std::vector<T> a;
        for (int i = 0; i < n_; ++i) {
            data_.push_back(a);
            for (int j = 0; j < m_; ++j) {
                std::cin >> value;
                data_[i].push_back(value);
            }
        }
    }

    Matrix(std::string name) {
        std::fstream file(name);
        if (file.is_open()) {
            std::string line;
            file >> n_ >> m_;
            for (size_t i = 0; i < n_; i++) {
                std::getline(file, line);
                std::stringstream(line);
                std::vector<T> a;
                T tmp;
                for (size_t j = 0; j < m_; j++) {
                    line >> tmp;
                    a.push_back(tmp);
                }
                data_.push_back(a);
            }
        }
    }

    ~Matrix() {
        data_ = {};
        n_ = 0;
        m_ = 0;
    }
    template<typename T1>
    friend Matrix<T1> operator+(Matrix<T1> &a, Matrix<T1> &b);

    template<typename T1>
    friend Matrix<T1> operator-(Matrix<T1> &a, Matrix<T1> &b);

    template<typename T1>
    friend Matrix<T1> operator*(Matrix<T1> &a, T1 scalar);

    template<typename T1>
    friend Matrix<T1> operator*(T1 scalar, Matrix<T1> &a);

    template<typename T1>
    friend Matrix<T1> operator*(Matrix<T1> &a, Matrix<T1> &b);

    size_t Get_size() {
        if (n_ != m_) {
            throw std::logic_error("Matrix is not square");
        }
        return n_;

    }


    bool operator!=(Matrix<T> &a) {
        if (n_ != a.n_ || m_ != a.m_)
            return true;
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < m_; ++j) {
                if (a[i][j] != data_[i][j])
                    return true;
            }
        }
        return false;
    }

    Matrix get_minor_of_matrix(size_t size, size_t row, size_t col) const{
        if (n_ != m_) {
            throw std::logic_error("Matrix should be square");
        }
        Matrix a(size - 1, size - 1);
        int off_set_row = 0;
        int off_set_col = 0;
        for (size_t i = 0; i < size - 1; i++) {
            if (i == row) {
                off_set_row = 1;
            }
            off_set_col = 0;
            for (size_t j = 0; j < size - 1; j++) {
                if (j == col) {
                    off_set_col = 1;
                }
                a.data_[i][j] = data_[i + off_set_row][j + off_set_col];
            }
        }
        return a;
    }
    Matrix<T> & operator=(const Matrix<T> &a) {
        n_ = a.n_;
        m_ = a.m_;
        data_ = a.data_;
        return *this;
    }

    T Det(size_t size) const {
        T det = 0;
        T degree = 1;

        if (size == 1) {
            return data_[0][0];
        } else if (size == 2) {
            return data_[0][0]* data_[1][1] - data_[0][1]* data_[1][0];
        }
        for (size_t j = 0; j < size; j++) {
            Matrix a = get_minor_of_matrix(size, 0, j);
            det = det + (degree * data_[0][j]*a.Det(size - 1));
            degree = -degree;
        }
        return det;

    }

    Matrix<T> Transpose() const{
        Matrix<T> transp(m_, n_);
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < m_; ++j) {
                transp.data_[i][j] = this->data_[j][i];
            }
        }
        return transp;
    }

    Matrix<T> operator!() const{
        if (this->Det(n_) == 0) {
            throw std::logic_error("There is no inverse matrix");
        }
        Matrix<T> a(n_, m_);
//        if (n_ == 1) {
//            Matrix<double> b(n_, m_);
//            b = (a * (1/this->Det(n_)));
//            return a;
//        } else if (n_ == 2) {
//            a.data_[0][0] = data_[1][1];
//            a.data_[0][1] = -data_[0][1];
//            a.data_[1][0] = -data_[1][0];
//            a.data_[1][1] = data_[0][0];
//            return (a * (1/this->Det(n_)));
//        }
        Matrix<T> z = Transpose();
        for (size_t i = 0; i < n_; i++) {
            for (size_t j = 0; j < m_; j++) {
                a.data_[i][j] = (z.get_minor_of_matrix(n_, i, j)).Det(n_-1) * pow(-1, i+j);
            }
        }
        Matrix<T> b(n_, m_);
         b = (a * (1/this->Det(n_)));
        return b;
    }

    bool operator==(const Matrix<T> &a) const{
        if (n_ != a.n_ || m_ != a.m_)
            return false;
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < m_; ++j) {
                if (a[i][j] != data_[i][j])
                    return false;
            }
        }
        return true;
    }

    bool operator==(int value) {
        if (value == 0) {
            for (int i = 0; i < n_; ++i) {
                for (int j = 0; j < m_; ++j) {
                    if (data_[i][j] != 0) {
                        return false;
                    }
                }
            }
        } else if (value == 1) {
            for (int i = 0; i < n_; ++i) {
                for (int j = 0; j < m_; ++j) {
                    if (data_[i][j] != 0 && i != j || data_[i][j] != 1 && i == j) {
                        return false;
                    }
                }
            }
        }
        return true;

    }
    template<typename T1>
    friend std::ostream &operator<<(std::ostream &out, Matrix<T1> M);
};


template<typename T>
std::ostream &operator<<(std::ostream &out, Matrix<T> a) {
    for (size_t i = 0; i < a.n_; ++i) {
        for (size_t j = 0; j < a.m_; ++j) {
            out << a.data_[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

template<typename T>
Matrix<T> operator+(Matrix<T> &a, Matrix<T> &b) {
    if (b.n_ != a.n_ || b.m_ != a.m_) {
        throw std::logic_error("Different dimensions to +");
    }
    Matrix<T> c(a.n_, a.m_);
    for (size_t i = 0; i < a.n_; i++) {
        for (size_t j = 0; j < a.m_; j++) {
            c.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        }
    }
    return c;
}

template<typename T>
Matrix<T> operator-(Matrix<T> &a, Matrix<T> &b) {
    if (b.n_ != a.n_ || b.m_ != a.m_) {
        throw std::logic_error("Different dimensions to +");
    }
    Matrix<T> c(a.n_, a.m_);
    for (size_t i = 0; i < a.n_; i++) {
        for (size_t j = 0; j < a.m_; j++) {
            c.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator*(Matrix<T> &a, T scalar) {
    Matrix<T> c(a.n_, a.m_);
    for (size_t i = 0; i < a.n_; ++i) {
        for (size_t j = 0; j < a.m_; ++j) {
            c.data_[i][j] = a.data_[i][j] * scalar;
        }
    }
    return c;
}

template<typename T>
Matrix<T> operator*(T scalar, Matrix<T> &a) {
    Matrix<T> c(a.n_, a.m_);
    for (size_t i = 0; i < a.n_; ++i) {
        for (size_t j = 0; j < a.m_; ++j) {
            c.data_[i][j] = a.data_[i][j] * scalar;
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator*(Matrix<T> &a, Matrix<T> &b) {
    if (a.m_ != b.n_) {
        throw std::logic_error("Different dimensions to *");
    }
    Matrix<T> c(a.n_, b.m_);
    for (size_t i = 0; i < a.n_; i++) {
        for (size_t j = 0; j < a.m_; j++) {
            T sum1 = 0;
            for (size_t k = 0; k < a.n_; k++) {
                sum1 += (a.data_[i][k] * b.data_[k][j]);
            }
            c.data_[i][j] = sum1;
        }
    }
    return c;
}



#endif //MATRIX_MAT_HPP