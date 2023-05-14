#include <iostream>
#include <fstream>

int raise_to_the_power (const int value, const int power) {
    int result;
    if (power < 0) {
        result = 0;
        std::cout << "Not positive power" << std::endl;
    }
    else if (power == 0) result = 1;
    else result = value;

    for (int i = 0; i < power-1; i++) {
        result = result * value;
    }
    
    return result;
}

template <typename T>
class Matrix {
    T** M;
    int height;
    int width;
    const char* name;
public:
    Matrix(const char* Matrix_Name) {
        height  = 0;
        width   = 0;
        name    = Matrix_Name;
        M       = nullptr;
    }

    Matrix(const char* Matrix_Name, const int n, const int m) {
        height  = n;
        width   = m;
        name    = Matrix_Name;

        M = (T**) new T*[height];
        
        for (int i = 0; i < height; i++) {
            M[i] = (T*) new T[width];
            for (int j = 0; j < width; j++) {
                M[i][j] = 0;
            }
        }
    }

    Matrix(const char* Matrix_Name, const char* File_Name) {
        name    = Matrix_Name;
        std::ifstream in(File_Name);
        if (in.is_open()) {
            in >> height >> width;
            M = (T**) new T*[height];

            for (int i = 0; i < height; i++) {
                M[i] = (T*) new T[width];
                for (int j = 0; j < width; j++) {
                    in >> M[i][j];
                }
            }
        }
        else std::cout << "File cannot be read" << std::endl;
        in.close();
    }

    void set_matrix() {
        if ((height == 0)&&(width == 0)) {
            std::cout << "Enter the height and width of the matrix " << name << ": " << std::endl;
            std::cin >> height >> width;

            M = (T**) new T*[height];
            for (int i = 0; i < height; i++) M[i] = (T*) new T[width];
        }
        std::cout << "Enter the elements of the matrix " << name << ": " << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cin >> M[i][j];
            }
        }
    }

    void set_fromfile_matrix(const char* File_Name) {
        std::ifstream in(File_Name);
        if (in.is_open()) {
            if ((height == 0)&&(width == 0)) {
                in >> height >> width;

                M = (T**) new T*[height];
                for (int i = 0; i < height; i++) M[i] = (T*) new T[width];
            }
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    in >> M[i][j];
                }
            }
        }
        else std::cout << "File cannot be read" << std::endl;
        in.close();
    }

    void set_infile_matrix(const char* File_Name) {
        std::ofstream out(File_Name);
        if (out.is_open()) {
            out << height << " " << width << std::endl;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    out << M[i][j] << " ";
                }
                out << std::endl;
            }
        }
        else std::cout << "File cannot be written" << std::endl;
        out.close();
    }

    T** get_matrix() {
        return M;
    }

    int get_size() const {
        if (height != width) {
            std::cout << "The matrix is not square" << std::endl;
            return 0;
        }
        return height;
    }

    int get_row() const { return height;  }
    int get_col() const { return width;   }

    void print_matrix() {
        std::cout << "Matrix " << name << ": " << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << M[i][j] << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    Matrix& operator=(const Matrix& matrix) {
        // protection from self-copying
        if (this == &matrix) return *this;
        if (width > 0) {
            for (int i = 0; i < height; i++) {
                delete[] M[i];
            }
        }
        if (height > 0) delete[] M;

        height  = matrix.height;
        width   = matrix.width;

        M = (T**) new T*[height];
        for (int i = 0; i < height; i++) M[i] = (T*) new T[width];
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                M[i][j] = matrix.M[i][j];
            }
        }
        return *this;
    }

    Matrix& operator+(const Matrix& matrix) {
        if ((height != matrix.height)||(height != matrix.height)) {
            std::cout << "The matrix sizes are not equal" << std::endl;
            return *this;
        }
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                M[i][j] = M[i][j] + matrix.M[i][j];
            }
        }

        return *this;
    }

    Matrix& operator-(const Matrix& matrix) {
        if ((height != matrix.height)||(height != matrix.height)) {
            std::cout << "The matrix sizes are not equal" << std::endl;
            return *this;
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                M[i][j] = M[i][j] - matrix.M[i][j];
            }
        }

        return *this;        
    }

    Matrix& operator*(const Matrix& matrix) {
        if (width != matrix.height) {
            std::cout << "The matrix sizes are not parity" << std::endl;
            return *this;
        }

        // creating an auxiliary matrix
        T **mat = new T* [height];
        for (int i = 0; i < height; i++) {
            mat[i] = new T [matrix.width];
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < matrix.width; j++) {
                int Sum = 0;
                for (int k = 0; k < width; k++) {
                    Sum = Sum + M[i][k] * matrix.M[k][j];
                }
                mat[i][j] = Sum;
            }
        }

        if (width > 0) {
            for (int i = 0; i < height; i++) {
                delete[] M[i];
            }
        }
        if (height > 0) delete[] M;

        width   = matrix.width;

        M = (T**) new T*[height];
        for (int i = 0; i < height; i++) M[i] = (T*) new T[width];

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                M[i][j] = mat[i][j];
            }
        }

        // deleting an auxiliary matrix
        if (matrix.width > 0) {
            for (int i = 0; i < height; i++) {
                delete[] mat[i];
            }
        }
        if (height > 0) delete[] mat;  

        return *this;
    }

    Matrix& operator*(int value) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                M[i][j] = M[i][j] * value;
            }
        }

        return *this;
    }

    bool operator==(const Matrix& matrix) {
        if ((height != matrix.height)||(width != matrix.width)) return false;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (M[i][j] != matrix.M[i][j]) return false;
            }
        }

        return true;
    }

    bool operator!=(const Matrix& matrix) {
        if ((height != matrix.height)||(width != matrix.width)) return true;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (M[i][j] != matrix.M[i][j]) return true;
            }
        }

        return false;
    }

    //переписать, возможен лучший вариант - аргумент
    bool operator==(int value) {
        if ((value != 0)&&(value != 1)) return false;

        if (value == 1) {
            if (height != width) return false;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if ((i == j)&&(M[i][j] != 1)) return false;
                    if ((i != j)&&(M[i][j] != 0)) return false;
                }
            }
        }
        else {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (M[i][j] != 0) return false;
                }
            }
        }

        return true;
    }

    //переписать, возможен лучший вариант - аргумент
    bool operator!=(int value) {
        if ((value != 0)&&(value != 1)) return true;

        if (value == 1) {
            if (height != width) return true;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if ((i == j)&&(M[i][j] != 1)) return true;
                    if ((i != j)&&(M[i][j] != 0)) return true;
                }
            }
        }
        else {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (M[i][j] != 0) return true;
                }
            }
        }

        return false;
    }

    void set_zero_matrix(int n, int m) {
        if ((n == 0)||(m == 0)) std::cout << "The size are not suitable" << std::endl;
        else {
            if (width > 0) {
                for (int i = 0; i < height; i++) {
                    delete[] M[i];
                }
            }
            if (height > 0) delete[] M;

            height  = n;
            width   = m;

            M = (T**) new T*[height];
            for (int i = 0; i < height; i++) M[i] = (T*) new T[width];
            
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    M[i][j] = 0;
                }
            }
        }
    }

    void set_identity_matrix(int n, int m) {
        if ((n != m)||(n == 0)||(m == 0)) std::cout << "The size are not suitable" << std::endl;
        else {
            if (width > 0) {
                for (int i = 0; i < height; i++) {
                    delete[] M[i];
                }
            }
            if (height > 0) delete[] M;

            height  = n;
            width   = m;

            M = (T**) new T*[height];
            for (int i = 0; i < height; i++) M[i] = (T*) new T[width];
            
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (i == j) M[i][j] = 1;
                    else M[i][j] = 0;
                }
            }
        }
    }

    void reformed_matrix(T **base_matr, T **matr, int sz, int row, int col) {
        int new_row = 0;
        for (int i = 0; i < sz; i++) {
            if (i != row) {
                int new_col = 0;
                for (int j = 0; j < sz; j++) {
                    if (j != col) {
                        matr[new_row][new_col] = base_matr[i][j];
                        new_col ++;
                    }
                }
                new_row ++;
            }
        }
    }

    void transpose_matrix(T **matr, int row, int col) {
        
        // creating an auxiliary matrix
        T **new_matr = new T* [col];
        for (int i = 0; i < col; i++) {
            new_matr[i] = new T [row];
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                new_matr[j][i] = matr[i][j];
            }
        }

        if (row != col) {
            if (col > 0) {
                for (int i = 0; i < row; i++) {
                    delete[] matr[i];
                }
            }
            if (row > 0) delete[] matr;

            height  = col;
            width   = row;

            matr = (T**) new T*[col];
            for (int i = 0; i < col; i++) matr[i] = (T*) new T[row];
        }

        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                matr[i][j] = new_matr[i][j];
            }
        }
        // deleting an auxiliary matrix
        if (col > 0) {
            for (int i = 0; i < col; i++) {
                delete[] new_matr[i];
            }
        }
        if (row > 0) delete[] new_matr;
    }

    int Determinant(T **matrix, int size) {
        int value = 0;
        if (size == 0) std::cout << "The size is not suitable" << std::endl;
        else if (size == 1) value = matrix[0][0];
        else if (size == 2) value = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        else {
            int k = 1;
            for (int i = 0; i < size; i++) {

                T **new_matrix = new T* [size-1];
                for (int j = 0; j < size-1; j++) {
                    new_matrix[j] = new T [size-1];
                }

                reformed_matrix(matrix, new_matrix, size, 0, i);

                value = value + k * matrix[0][i] * Determinant(new_matrix, size-1);
                k = (-1) * k;

                if (size-1 > 0) {
                    for (int k = 0; k < size-1; k++) {
                        delete[] new_matrix[k];
                    }
                }
                if (size-1 > 0) delete[] new_matrix;
            }
        }
        return value;
    }
    
    void get_matrix_inverse() {
        int det = Determinant(M, height);
        if (det == 0) {
            std::cout << "Matrix is not invertible" << std::endl;
        }
        else {
            // creating an auxiliary matrix
            T **inv_mat = new T* [height];
            for (int i = 0; i < height; i++) {
                inv_mat[i] = new T [width];
            }

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    T **new_matrix = new T* [height-1];
                    for (int k = 0; k < height-1; k++) {
                        new_matrix[k] = new T [width-1];
                    }

                    reformed_matrix(M, new_matrix, height, i, j);

                    inv_mat[i][j] = raise_to_the_power(-1, (i+j+2)) * Determinant(new_matrix, height-1) / det;

                    if (height-1 > 0) {
                        for (int k = 0; k < height-1; k++) {
                            delete[] new_matrix[k];
                        }
                    }
                    if (height-1 > 0) delete[] new_matrix;
                }
            }

            transpose_matrix(inv_mat, height, width);
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    M[i][j] = inv_mat[i][j];
                }
            }

            // deleting an auxiliary matrix
            if (width > 0) {
                for (int i = 0; i < height; i++) {
                    delete[] inv_mat[i];
                }
            }
            if (height > 0) delete[] inv_mat;
        }
    }

    bool operator!() {
        if (Determinant(M, height) == 0) {
            std::cout << "Matrix is not invertible" << std::endl;
            return false;
        }
        return true;
    }
    
    ~Matrix() {
        if (width > 0) {
            for (int i = 0; i < height; i++) {
                delete[] M[i];
            }
        }
        delete[] M;
    }
};



int main() {

    Matrix<int> M_1("M_1");
    M_1.print_matrix();

    Matrix<int> M_2("M_2", 7, 3);
    M_2.print_matrix();

    Matrix<int> M_3("M_3");
    //M_3.set_matrix();
    M_3.print_matrix();

    Matrix<int> M_4("M_4", 2, 2);
    //M_4.set_matrix();
    M_4.print_matrix();  
    

    Matrix<int> M_5("M_5");
    M_5.set_fromfile_matrix("matrix_files/M_5.txt");
    M_5.print_matrix();
    M_5.set_infile_matrix("matrix_files/M_5_in.txt");

    Matrix<int> M_6("M_6", 2, 5);
    M_6.set_fromfile_matrix("matrix_files/M_6.txt");
    M_6.print_matrix();
    M_6.set_infile_matrix("matrix_files/M_6_in.txt");


    // set matrix from file constructor check
    Matrix<int> M_7("M_7", "matrix_files/M_7.txt");
    M_7.print_matrix();
    

    // assignment operator check
    Matrix<int> M_8("M_8", 3, 3);
    Matrix<int> M_9("M_9");
    M_8 = M_9 = M_6;
    M_8.print_matrix();
    M_9.print_matrix();


    // self-copying check
    M_8 = M_8;
    M_8.print_matrix();


    // arithmetic operator+ check (Вопрос об изменении матрицы, к которой применяется прибавление в формулле с =; можно создать доп поле M_dop или просто матрицу)
    M_8 + M_9;
    M_8.print_matrix();

    M_8 + M_9 + M_9;
    M_8.print_matrix();
    M_9.print_matrix();

    M_8 = M_9;
    Matrix<int> M_10("M_10");
    M_10 = M_8 + M_9;
    M_10.print_matrix();
    M_8.print_matrix();
    M_9.print_matrix();
    

    // arithmetic operator- check
    M_8 - M_9 - M_9;
    M_8.print_matrix();
    M_9.print_matrix();


    // arithmetic operator* check
        //square matrix
    Matrix<int> M_11("M_11", "matrix_files/M_umn_1.txt");
    Matrix<int> M_12("M_12", "matrix_files/M_umn_2.txt");
    M_11.print_matrix();
    M_12.print_matrix();
    M_11 * M_12;
    M_11.print_matrix();
        //rectangle matrix
    Matrix<int> M_13("M_13", "matrix_files/M_umn_3.txt");
    Matrix<int> M_14("M_14", "matrix_files/M_umn_4.txt");
    M_13.print_matrix();
    M_14.print_matrix();
    M_13 * M_14;
    M_13.print_matrix();


    // arithmetic operator* check
    M_14.print_matrix();
    M_14 * 5;
    M_14.print_matrix();


    // comparison operator check
    Matrix<int> M_15("M_15", "matrix_files/M_4.txt");
    Matrix<int> M_16("M_16", "matrix_files/M_5.txt");
    if (M_15 == M_16) std::cout << "equal" << std::endl;
    else std::cout << "NOT equal" << std::endl;
    if (M_15 != M_16) std::cout << "NOT equal" << std::endl;
    else std::cout << "equal" << std::endl;


    // comparison operator check - Identity/Zero matrix
    Matrix<int> M_17("M_17", "matrix_files/M_17.txt");
    if (M_17 == 1) std::cout << "Identity matrix" << std::endl;
    else std::cout << "Not Identity matrix" << std::endl;

    Matrix<int> M_18("M_18", "matrix_files/M_18.txt");
    if (M_18 != 0) std::cout << "Not Zero matrix" << std::endl;
    else std::cout << "Zero matrix" << std::endl;
    

    // creating Identity/Zero matrix check
    Matrix<int> M_19("M_19");
    M_19.set_zero_matrix(3, 5);
    M_19.print_matrix();
    
    Matrix<int> M_20("M_20");
    M_20.set_identity_matrix(5, 5);
    M_20.print_matrix();


    // searching inverse matrix method check
    Matrix<int> M_21("M_21", "matrix_files/M_21.txt");
    M_21.print_matrix();
    std::cout << "Determinant: " << M_21.Determinant(M_21.get_matrix(), M_21.get_size()) << std::endl;

    Matrix<int> M_22("M_22", "matrix_files/M_22.txt");
    M_22.print_matrix();
    std::cout << "Determinant: " << M_22.Determinant(M_22.get_matrix(), M_22.get_size()) << std::endl;

    if (!M_22) std::cout << "Matrix is invertible" << std::endl;
    !M_21;

    Matrix<int> M_23("M_23", "matrix_files/M_23.txt");
    M_23.print_matrix();
    std::cout << "Determinant: " << M_23.Determinant(M_23.get_matrix(), M_23.get_size()) << std::endl;
    M_23.get_matrix_inverse();
    M_23.print_matrix();

    Matrix<float> M_24("M_24", "matrix_files/M_24.txt");
    M_24.print_matrix();
    M_24.get_matrix_inverse();
    M_24.print_matrix();

    Matrix<double> M_25("M_25", "matrix_files/M_25.txt");
    M_25.print_matrix();

    return 0;
}
