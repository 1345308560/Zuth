#ifndef _SPRASE_H
#define  _SPRASE_H

template<typename T>
class SparseMatrix {
	Zuth::Matrix<T> m;
	int oRow, oCol;
	int size;
public:
	SparseMatrix(Zuth::Matrix<T> input) {
		size = 0;
		Zuth::Vector<T> tempV;
		int row = input.getRowSize();
		int col = input.getColSize();
		oRow = row;
		oCol = col;
		for(int i=0;i<row;i++)
			for(int j=0;j<col;j++)
				if (input.getNum(i, j) != 0) {
					size++;
					tempV.pushback(i);
					tempV.pushback(j);
					tempV.pushback(input.getNum(i, j));
				}
		Zuth::Matrix<T> newM(size, 3, tempV);
		m = newM;
	}
	// 拷贝构造函数
	SparseMatrix(const SparseMatrix& input) {
		size = input.size;
		oCol = input.oCol;
		oRow = input.oRow;
		m=input.m;
	}
	Zuth::Matrix<T> orignMatrix(){
		Zuth::Matrix<T> tempM(oRow, oCol);
		for (int i = 0; i < oRow; i++)
			for (int j = 0; j < oCol; j++)
				tempM.getNum(i, j) = 0;
		for (int i = 0; i < size; i++)
			tempM.getNum((int)m.getNum(i, 0), (int)m.getNum(i, 1)) += m.getNum(i, 2);
		return tempM;
	}
	SparseMatrix operator+(const SparseMatrix& otherMat) {
		int newSize = size + otherMat.size;
		SparseMatrix<T> newSM(this);
		Zuth::Matrix<T> newM(newSize, 3);
		for (int i = 0; i < size; i++) {
			newM.getNum(i, 0) = m.getNum(i, 0);
			newM.getNum(i, 1) = m.getNum(i, 1);
			newM.getNum(i, 2) = m.getNum(i, 2);
		}
		for (int i = 0; i < otherMat.size; i++) {
			newM.getNum(i + size, 0) = newM.getNum(i, 0);
			newM.getNum(i + size, 1) = newM.getNum(i, 1);
			newM.getNum(i + size, 2) = newM.getNum(i, 2);
		}
		newSM.m = newM;
		return newSM;
	}
	// 减法
	SparseMatrix operator-(const SparseMatrix& otherMat) {
		int newSize = size + otherMat.size;
		SparseMatrix<T> newSM(*this);
		Zuth::Matrix<T> newM(newSize, 3);
		for (int i = 0; i < size; i++) {
			newM.getNum(i, 0) = m.getNum(i, 0);
			newM.getNum(i, 1) = m.getNum(i, 1);
			newM.getNum(i, 2) = m.getNum(i, 2);
		}
		for (int i = 0; i < otherMat.size; i++) {
			newM.getNum(i + size, 0) = newM.getNum(i, 0);
			newM.getNum(i + size, 1) = newM.getNum(i, 1);
			newM.getNum(i + size, 2) = -newM.getNum(i, 2);
		}
		newSM.m = newM;
		return newSM;
	}
	SparseMatrix Transpose() {
		SparseMatrix<T> newSM(*this);
		for (int i = 0; i < size; i++) {
			int temp = (int)newSM.m.getNum(i, 0);
			newSM.m.getNum(i, 0) = newSM.m.getNum(i, 1);
			newSM.m.getNum(i, 1) = temp;
		}
		return newSM;
	}
	friend std::ostream& operator<<(std::ostream& os, SparseMatrix SM)
	{
		for (int i = 0; i<SM.size; i++)
			os << SM.m.getNum(i, 0) << " " << SM.m.getNum(i, 1)<<" "<< SM.m.getNum(i, 2) << "\n";
		return os;
	}
};

#endif
