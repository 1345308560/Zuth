#ifndef _CORE_ALGORITHM_H
#define _CORE_ALGORITHM_H

#include "CoreClass.h"
// 一维前缀和
template<typename T>
Zuth::Vector<T> Prefix(Zuth::Vector<T>& V) {
	Vector<T> newV;
	for (int i = 0; i < V.getsize(); i++)
		newV.pushback(V[i]);
	for (int i = 1; i < V.getsize(); i++)
		newV[i] += newV[i - 1];
	return newV;
}
// 一维差分
template<typename T>
Zuth::Vector<T> Difference(Zuth::Vector<T> &V) {
	Vector<T> newV;
	for (int i = 0; i < V.getsize(); i++)
		newV.pushback(V[i]);
	for (int i = 1; i < V.getsize(); i++)
		newV[i] = V[i] - V[i - 1];
	return newV;
}
// 二维前缀和
template<typename T>
Zuth::Matrix<T> Prefix(Zuth::Matrix<T> M) {
	int row = M.getRowSize();
	int col = M.getColSize();
	T* t = new T[row*col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			t[i * col + j] = M.getNum(i, j);
	for (int i = 1; i < col; i++)t[0 * col + i] += t[i - 1];
	for (int i = 1; i < row; i++)t[i * col + 0] += t[(i - 1)*col];
	for (int i = 1; i < row; i++)
		for (int j = 1; j < col; j++)
			t[i * col+ j] += t[(i-1) * col + j] + t[i * col + j-1] - t[(i-1) * col + j-1];
	Matrix<T> newM(row, col, t);
	return newM;
}
// 二维差分
template<typename T>
Zuth::Matrix<T> Difference(Zuth::Matrix<T> M) {
	int row = M.getRowSize();
	int col = M.getColSize();
	T* t = new T[row * col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			t[i * col + j] = M.getNum(i, j);
	for (int i = 1; i < col; i++)t[0 * col + i] -= t[i - 1];
	for (int i = 1; i < row; i++)t[i * col + 0] -= t[(i - 1) * col];
	for (int i = 1; i < row; i++)
		for (int j = 1; j < col; j++)
			t[i * col + j] -= t[(i - 1) * col + j] + t[i * col + j - 1] - t[(i - 1) * col + j - 1];
	Matrix<T> newM(row, col, t);
	return newM;
}
// 并查集

class DisjointSet {
	// 存放父节点
	int* f;
	// 存在集合的数量
	int setNum;
public:
	DisjointSet(int n) {
		f = new int[n];
		for (int i = 0; i < n; i++)f[i] = i;
	}
	int findFather() {

	}
};
#endif
