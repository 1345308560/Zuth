#ifndef _MATRIX_H
#define  _MATRIX_H

template <typename dataType>
class Matrix {
	// 矩阵指针
	dataType* pointer;
	// 行数与列数
	int rowSize;
	int colSize;
public:
	// 无参数的构造函数
	Matrix(int rows = 0, int cols = 0) {
		rowSize = rows;
		colSize = cols;
		pointer = new dataType[rows * cols];
	}
	// 使用数组构造
	Matrix(int rows, int cols, dataType* dataPointer) {
		rowSize = rows;
		colSize = cols;
		pointer = new dataType[rows * cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				pointer[i * cols + j] = dataPointer[i * cols + j];
	}
	// 拷贝构造函数
	Matrix(const Matrix& tempMatrix) {
		rowSize = tempMatrix.rowSize;
		colSize = tempMatrix.colSize;
		pointer = new dataType[rowSize * colSize];
		for (int i = 0; i < rowSize; i++)
			for (int j = 0; j < colSize; j++)
				pointer[i * colSize + j] = tempMatrix.pointer[i * colSize + j];
	}
	// 行数
	int getRowSize() {
		return rowSize;
	}
	// 列数
	int getColSize() {
		return colSize;
	}
	// 元素
	dataType & getNum(int i, int j) {
		return pointer[i * colSize + j];
	}
	// 块
	Matrix block(int i, int j, int p, int q) {
		int rows = p-i+1;
		int cols = q-j+1;
		dataType* newMat = new dataType[rows * cols];
		for (int ii = 0; ii < rows; ii++)
			for (int jj = 0; jj < cols; jj++)
				newMat[ii * cols + jj] = pointer[(ii+i) * colSize + j+jj];
		Matrix<dataType> tempMat(rows, cols, newMat);
		return tempMat;
	}
	Matrix row(int i) {
		dataType* newMat = new dataType[colSize];
		for (int j = 0; j < colSize; j++)newMat[j] = pointer[i * colSize + j];
		Matrix<dataType> tempMat(1, colSize, newMat);
		return tempMat;
	}
	Matrix col(int i) {
		dataType* newMat = new dataType[rowSize];
		for (int j = 0; j < rowSize; j++)newMat[j] = pointer[j * colSize + i];
		Matrix<dataType> tempMat(rowSize, 1, newMat);
		return tempMat;
	}
	//逆矩阵
	Matrix adgMatrix() {
		Matrix<dataType> newM(rowSize,colSize);
		for (int i = 0; i < rowSize; i++)
			for (int j = 0; j < colSize; j++)
				if((i+j)%2==0)
					newM.getNum(i, j) = Del(modMatrix(i,j));
				else
					newM.getNum(i, j) = -Del(modMatrix(i, j));
		int d = Del(newM);
		for (int i = 0; i < rowSize; i++)
			for (int j = 0; j < colSize; j++)
				newM.getNum(i, j) /= d;
		return Transpose(newM);
	}
	// 代数余子式
	Matrix modMatrix(int k, int l) {
		Matrix<dataType> newM(rowSize-1, colSize-1);
		int ii = 0, jj = 0;
		for (int i = 0; i < colSize; i++) {
			if (k == i)continue;
			for (int j = 0; j < colSize; j++) {
				if (l == j)continue;
				newM.getNum(ii, jj) = getNum(i, j);
				jj++;
			}
			ii++;
		}
		return newM;
	}
	//重载运算符+
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
	//重载运算符-
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
	//重载运算符*
	Matrix operator*(double num) {
		int rows = rowSize;
		int cols = colSize;
		dataType* newMat = new dataType[rows * cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				newMat[i * cols + j] =pointer[i * cols + j]* num;
		Matrix<dataType> tempMat(rows, cols, newMat);
		return tempMat;
	}
	Matrix operator*(int num) {
		int rows = rowSize;
		int cols = colSize;
		dataType* newMat = new dataType[rows * cols];
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				newMat[i * cols + j] = pointer[i * cols + j] * num;
		Matrix<dataType> tempMat(rows, cols, newMat);
		return tempMat;
	}
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
	// 重载运算符<<
	friend std::ostream& operator<<(std::ostream& os, Matrix& m)
	{
		int rows = m.rowSize;
		int cols = m.colSize;
		// 输出矩阵大小
		os << "Matrix " << rows << " X " << cols << " \n";
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (j != cols - 1)os << m.pointer[i * cols + j] << "\t";
				else os << m.pointer[i * cols + j] << "\n";
		return os;
	}
};
// 零矩阵
template<typename Type>
Matrix<Type> Zeros(int i) {
	Type* newMat = new Type[i * i];
	for (int j = 0; j < i; j++)
		for (int k = 0; k < i; k++)
			newMat[j * i + k] = 0;
	Matrix<Type> m(i, i, newMat);
	return m;
}
template<typename Type>
Matrix<Type> Zeros(int i, int j) {
	Type* newMat = new Type[i * j];
	for (int ii = 0; ii < i; ii++)
		for (int jj = 0; jj < j; jj++)
			newMat[ii * j + jj] = 0;
	Matrix<Type> m(i, j, newMat);
	return m;
}
// 单位矩阵
template<typename Type>
Matrix<Type> Eye(int i) {
	Type* newMat = new Type[i * i];
	for (int j = 0; j < i; j++)
		for (int k = 0; k < i; k++)
			if (k == j)newMat[j * i + k] = 1;
			else newMat[j * i + k] = 0;
	Matrix<Type> m(i, i, newMat);
	return m;
}
// 矩阵转置
template<class Type>
Matrix<Type> Transpose(Matrix<Type>& m) {
	Matrix<Type> newMat = m;
	// 只对换下三角
	for (int i = 0; i < newMat.getRowSize(); i++)
		for (int j = 0; j < i; j++) {
			Type temp = newMat.getNum(i, j);
			newMat.getNum(i, j) = newMat.getNum(j, i);
			newMat.getNum(j, i) = temp;
		}
	return newMat;
}
#endif 


