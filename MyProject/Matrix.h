#ifndef _MATRIX_H
#define  _MATRIX_H

template <typename dataType>
class Matrix {
	// ����ָ��
	dataType* pointer;
	// ����������
	int rowSize;
	int colSize;
public:
	// �޲����Ĺ��캯��
	Matrix(int rows = 0, int cols = 0) {
		rowSize = rows;
		colSize = cols;
		pointer = new dataType[rows * cols];
	}
	// ʹ�����鹹��
	Matrix(int rows, int cols, dataType* dataPointer) {
		rowSize = rows;
		colSize = cols;
		pointer = new dataType[rows * cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				pointer[i * cols + j] = dataPointer[i * cols + j];
	}
	// �������캯��
	Matrix(const Matrix& tempMatrix) {
		rowSize = tempMatrix.rowSize;
		colSize = tempMatrix.colSize;
		pointer = new dataType[rowSize * colSize];
		for (int i = 0; i < rowSize; i++)
			for (int j = 0; j < colSize; j++)
				pointer[i * colSize + j] = tempMatrix.pointer[i * colSize + j];
	}
	//���������+
	Matrix operator+(const Matrix& otherMat) {
		int rows = rowSize;
		int cols = colSize;
		dataType* newMat = new dataType[rows * cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				newMat[i * cols + j] = this->pointer[i * cols + j] + otherMat.pointer[i * cols + j];
		Matrix<dataType> tempMat(rows, cols, newMat);
		return tempMat;
	}
	//���������-
	Matrix operator-(const Matrix& otherMat) {
		int rows = rowSize;
		int cols = colSize;
		dataType* newMat = new dataType[rows * cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				newMat[i * cols + j] = this->pointer[i * cols + j] - otherMat.pointer[i * cols + j];
		Matrix<dataType> tempMat(rows, cols, newMat);
		return tempMat;
	}
	//���������*
	Matrix operator*(const Matrix& otherMat) {
		int rows = rowSize;
		int cols = colSize;
		int otherCols = otherMat.colSize;
		dataType* newMat = new dataType[rows * otherCols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < otherCols; j++) {
				newMat[i * otherCols + j] = 0;
				for (int k = 0; k < cols; k++)
					newMat[i * otherCols + j] += pointer[i * cols + k] * otherMat.pointer[k * otherCols + j];
			}
		Matrix<dataType> tempMat(rows, otherCols, newMat);
		return tempMat;
	}
	// ���������<<
	friend std::ostream& operator<<(std::ostream& os, Matrix& m)
	{
		int rows = m.rowSize;
		int cols = m.colSize;
		// ��������С
		os << "Matrix " << rows << " X " << cols << " \n";
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (j != cols - 1)os << m.pointer[i * cols + j] << "\t";
				else os << m.pointer[i * cols + j] << "\n";
		return os;
	}
};


#endif 


