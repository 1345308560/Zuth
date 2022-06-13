#ifndef _CORE_ALGEBRA_H
#define  _CORE_ALGEBRA_H

#include "CoreClass.h"
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
template<typename Type>
Matrix<Type> Transpose(Matrix<Type> & m) {
	Matrix<Type> newMat = m;
	// 只对换下三角
	for(int i=0;i<newMat.getRowSize(); i++)
		for (int j = 0; j < i; j++) {
			Type temp = newMat.getNum(i,j);
			newMat.getNum(i, j) = newMat.getNum(j, i);
			newMat.getNum(j, i) = temp;
		}	
	return newMat;
}



#endif

