#include "Matrices.h"

namespace Matrices 
{
    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols), a(_rows, vector<double>(_cols, 0)) {}

    Matrix operator+(const Matrix& a, const Matrix& b) 
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) 
        {
            throw runtime_error("Matrix dimensions must match for addition.");
        }

        Matrix result(a.getRows(), a.getCols());
        for (int i = 0; i < a.getRows(); i++) 
        {
            for (int j = 0; j < a.getCols(); j++) 
            {
                result(i, j) = a(i, j) + b(i, j);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& a, const Matrix& b) 
    {
        if (a.getCols() != b.getRows()) 
        {
            throw runtime_error("Matrix multiplication requires first matrix columns to match second matrix rows.");
        }

        Matrix result(a.getRows(), b.getCols());
        for (int i = 0; i < a.getRows(); i++) 
        {
            for (int j = 0; j < b.getCols(); j++) 
            {
                for (int k = 0; k < a.getCols(); k++) 
                {
                    result(i, j) += a(i, k) * b(k, j);
                }
            }
        }
        return result;
    }

    bool operator==(const Matrix& a, const Matrix& b) 
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) 
        {
            return false;
        }
        for (int i = 0; i < a.getRows(); i++) 
        {
            for (int j = 0; j < a.getCols(); j++) 
            {
                if (a(i, j) != b(i, j)) 
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& a, const Matrix& b) 
    {
        return !(a == b);
    }

    ostream& operator<<(ostream& os, const Matrix& a) 
    {
        for (int i = 0; i < a.getRows(); i++) 
        {
            for (int j = 0; j < a.getCols(); j++) 
            {
                os << setw(10) << a(i, j) << " ";
            }
            os << endl;
        }
        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        (*this)(0, 0) = cos(theta);
        (*this)(0, 1) = -(sin(theta));
        (*this)(1, 0) = sin(theta);
        (*this)(1, 1) = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        (*this)(0, 0) = scale;
        (*this)(0, 1) = 0;
        (*this)(1, 0) = 0;
        (*this)(1, 1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {   
        for (int i = 0; i < nCols; i++)
        {
            (*this)(0, i) = xShift;
            (*this)(1, i) = yShift;
        }
    }
}