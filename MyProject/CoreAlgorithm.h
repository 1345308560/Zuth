#ifndef _CORE_ALGORITHM_H
#define _CORE_ALGORITHM_H

#include "CoreClass.h"
// һάǰ׺��
template<typename T>
Zuth::Vector<T> Prefix(Zuth::Vector<T>& V) {
	Vector<T> newV;
	for (int i = 0; i < V.getsize(); i++)
		newV.pushback(V[i]);
	for (int i = 1; i < V.getsize(); i++)
		newV[i] += newV[i - 1];
	return newV;
}
// һά���
template<typename T>
Zuth::Vector<T> Difference(Zuth::Vector<T> &V) {
	Vector<T> newV;
	for (int i = 0; i < V.getsize(); i++)
		newV.pushback(V[i]);
	for (int i = 1; i < V.getsize(); i++)
		newV[i] = V[i] - V[i - 1];
	return newV;
}
// ��άǰ׺��
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
// ��ά���
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
// ���鼯

class DisjointSet {
	// ��Ÿ��ڵ�
	int* f;
	// �ڵ�����
	int size;
	// ���ڼ��ϵ�����
	int setNum;
public:
	DisjointSet(int n) {
		size = n;
		setNum = n;
		f = new int[n];
		for (int i = 0; i < n; i++)f[i] = i;
	}
	// �ҵ����ڵ�
	int findFather(int i) {
		if (f[i] == i)return i;
		else {
			f[i] = findFather(f[i]);
			return f[i];
		}
	}
	// �ϲ�
	void dUnion(int i, int j) {
		int fi = findFather(i), fj = findFather(j);
		if (i != j)f[fi] = fj;
	}
	// ���еļ�������
	int setNumber() {
		setNum = 0;
		for (int i = 0; i < size; i++)if (f[i] == i)setNum++;
		return setNum;
	}
	~DisjointSet() { delete[] f; }
};

// ����
// ��������
struct Range {
	int start, end;

	Range(int s = 0, int e = 0) { start = s, end = e; }
};

template <typename T>
void quickSort(T arr[], const int len) {
	if (len <= 0) return;
	Zuth::Range *r=new Range[len];
	int p = 0;
	r[p++] = Zuth::Range(0, len - 1);
	while (p) {
		Zuth::Range range = r[--p];
		if (range.start >= range.end) continue;
		T mid = arr[range.end];
		int left = range.start, right = range.end - 1;
		while (left < right) {
			while (arr[left] < mid && left < right) left++;
			while (arr[right] >= mid && left < right) right--;
			std::swap(arr[left], arr[right]);
		}
		if (arr[left] >= arr[range.end])
			std::swap(arr[left], arr[range.end]);
		else
			left++;
		r[p++] = Zuth::Range(range.start, left - 1);
		r[p++] = Zuth::Range(left + 1, range.end);
	}
}
// �鲢����
template <typename T>
void mergeSort(T a[], int ll, int rr) {
	if (rr - ll <= 1) return;
	T* t = new T[rr - ll + 1];
	int mid = ll + ((rr - ll) >> 1);
	mergeSort(a,ll, mid);
	mergeSort(a,mid, rr);
	int p = ll, q = mid, s = ll;
	while (s < rr) {
		if (p >= mid || (q < rr && a[p] > a[q])) {
			t[s++] = a[q++];
		}
		else
			t[s++] = a[p++];
	}
	for (int i = ll; i < rr; ++i) a[i] = t[i];
}
// ������
void siftDown(int arr[], int start, int end) {
	// ���㸸�����ӽ����±�
	int parent = start;
	int child = parent * 2 + 1;
	while (child <= end) {  // �ӽ���±��ڷ�Χ�ڲ����Ƚ�
	  // �ȱȽ������ӽ���С��ѡ������
		if (child + 1 <= end && arr[child] < arr[child + 1]) child++;
		// ����������ӽ��󣬴��������ϣ�ֱ����������
		if (arr[parent] >= arr[child])
			return;
		else {  // ���򽻻��������ݣ��ӽ���ٺ�����Ƚ�
			std::swap(arr[parent], arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
	}
}

void heapSort(int arr[], int len) {
	// �����һ���ڵ�ĸ��ڵ㿪ʼ sift down ����ɶѻ� (heapify)
	for (int i = (len - 1 - 1) / 2; i >= 0; i--) siftDown(arr, i, len - 1);
	// �Ƚ���һ��Ԫ�غ��Ѿ��źõ�Ԫ��ǰһλ�������������µ������յ�����Ԫ��֮ǰ��Ԫ�أ���ֱ���������
	for (int i = len - 1; i > 0; i--) {
		std::swap(arr[0], arr[i]);
		siftDown(arr, 0, i - 1);
	}
}
// ϣ������
template <typename T>
void shellSort(T array[], int length) {
	int h = 1;
	while (h < length / 3) {
		h = 3 * h + 1;
	}
	while (h >= 1) {
		for (int i = h; i < length; i++) {
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
				std::swap(array[j], array[j - h]);
			}
		}
		h = h / 3;
	}
}
#endif
