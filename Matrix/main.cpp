#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** data;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new T[cols];
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
    }

    void fillRandom() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<T> dis(0, 100);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = dis(gen);
            }
        }
    }

    void fillFromKeyboard() {
        cout << "Enter matrix elements row by row:\n";
        for (int i = 0; i < rows; ++i) {
            cout << "Row " << (i + 1) << ": ";
            for (int j = 0; j < cols; ++j) {
                cin >> data[i][j];
            }
        }
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << setw(8) << data[i][j] << " ";
            }
            cout << "\n";
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const T& scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    T maxElement() const {
        T max = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] > max)
                    max = data[i][j];
            }
        }
        return max;
    }

    T minElement() const {
        T min = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] < min)
                    min = data[i][j];
            }
        }
        return min;
    }
};

int main() {
    int rows, cols;
    cout << "Enter the number of rows and columns for the matrix: ";
    cin >> rows >> cols;

    Matrix<double> mat1(rows, cols);
    mat1.fillRandom();
    cout << "Matrix 1:\n";
    mat1.print();

    Matrix<double> mat2(rows, cols);
    mat2.fillFromKeyboard();
    cout << "Matrix 2:\n";
    mat2.print();

    Matrix<double> sum = mat1 + mat2;
    cout << "Sum of matrices:\n";
    sum.print();

    Matrix<double> difference = mat1 - mat2;
    cout << "Difference of matrices:\n";
    difference.print();

    Matrix<double> product = mat1 * mat2;
    cout << "Product of matrices:\n";
    product.print();

    double scalar;
    cout << "Enter a scalar value for division: ";
    cin >> scalar;
    Matrix<double> division = mat1 / scalar;
    cout << "Matrix 1 divided by scalar:\n";
    division.print();

    cout << "Maximum element in Matrix 1: " << mat1.maxElement() << "\n";
    cout << "Minimum element in Matrix 1: " << mat1.minElement() << "\n";

    return 0;
}
