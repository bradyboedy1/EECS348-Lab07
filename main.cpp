
#include <iostream>

using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    Matrix(int size = 0) : matrix_size(size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;

        matrix_size = other.matrix_size;

        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }
};

void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    FILE *inputFile = fopen(file_name.c_str(), "r");

    //handles errors
    if (!inputFile){
        cout << "\nError opening this file." << endl;
        return;
    }

    int size; //size of matrix
    fscanf(inputFile, "%d", &size);

    matrix_1 = Matrix(size);
    matrix_2 = Matrix(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fscanf(inputFile, "%lf", &matrix_1.matrix_data[i][j]);
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fscanf(inputFile, "%lf", &matrix_2.matrix_data[i][j]);
        }
    }

    fclose(inputFile);
}

void print_matrix(const Matrix& matrix) {    
    for (int i = 0; i < matrix.matrix_size; ++i){
        for (int j = 0; j < matrix.matrix_size; ++j){
            cout << matrix.matrix_data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    print_matrix(matrix_1);
    print_matrix(matrix_2);
    
}

Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    Matrix result(matrix_1.matrix_size);

    for (int i = 0; i < result.matrix_size; ++i){
        for (int j = 0; j < result.matrix_size; ++j){
            result.matrix_data[i][j] = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
        }
    }
    return result;
}

Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    Matrix result(matrix_1.matrix_size);

    for (int i = 0; i < result.matrix_size; ++i){
        for (int j = 0; j < result.matrix_size; ++j){
            result.matrix_data[i][j] = matrix_1.matrix_data[i][j] * matrix_2.matrix_data[i][j];
        }
    }
    return result;
}

// Overloaded + operator for matrix addition
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2){
    Matrix result(matrix_1.matrix_size);
    result = add_matrices(matrix_1, matrix_2);
    return result;
}

// Overloaded * operator for matrix multiplication
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2){
    Matrix result(matrix_1.matrix_size);
    result = multiply_matrices(matrix_1, matrix_2);
    return result;
}


void get_diagonal_sum(const Matrix& matrix) {
    int mainD = 0;
    int secD = 0;

    for (int i = 0; i < matrix.matrix_size; ++i){
        mainD += matrix.matrix_data[i][i];
        secD += matrix.matrix_data[matrix.matrix_size-i-1][i];
    }
    cout << mainD + secD << endl << endl;
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    if (row1 >= 0 && row1 < matrix.matrix_size && row2 >= 0 && row2 < matrix.matrix_size){
        for (int i = 0; i < matrix.matrix_size; ++i){
            int temp = matrix.matrix_data[row1][i];
            matrix.matrix_data[row1][i] = matrix.matrix_data[row2][i];
            matrix.matrix_data[row2][i] = temp;
        }
        print_matrix(matrix);
    }
    else{
        cout << "Unsuccessful Swap (Invalid rows)" << endl;
    }
}

int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    cout << "add_matrices result:" << endl;
    Matrix add_result_1 = add_matrices(matrix_1, matrix_2);
    Matrix add_result_2 = matrix_1 + matrix_2;
    print_matrix(add_result_1);
    print_matrix(add_result_2);

    cout << "multiply_matrices result:" << endl;
    Matrix multiply_result_1 = multiply_matrices(matrix_1, matrix_2);
    Matrix multiply_result_2 = matrix_1 * matrix_2;
    print_matrix(multiply_result_1);
    print_matrix(multiply_result_2);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);

    return 0;
}