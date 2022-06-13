#include <iostream>
#include "Core.h"
using namespace std;
int main()
{	/*double data[4] = { 1,2,3,4 };
	double data2[6] = { 1,2,3,4,5,6 };
	Zuth::Matrix<double> A(2,2,data);
	Zuth::Matrix<double> B(2,3,data2);
	Zuth::Matrix<double> C;
	C = A * B;
	cout << A<<B<<C;*/

	//Zuth::Vector<int> V1;
	//V1.pushback(1);
	//V1.pushback(2);
	//V1.pushback(2); 
	//Zuth::Vector<int> V2=V1;
	//cout << V2[0];
	//V2[0] = 2;
	//cout << V2[0];
	string A = "999";
	Zuth::BigNum B(A);
	Zuth::BigNum C(999);
	Zuth::BigNum D= B *C;
	cout << D;
	cout << std::endl;
	// 矩阵乘法
	int data[4] = {1,2,3,4};
	Zuth::Matrix<int> m(2, 2, data);
	Zuth::Matrix<int> m2 = m * 10;
	cout << m2;
	// 分块
	cout << std::endl;
	int data2[9] = { 1,2,3,4,5,6,7,8,9 };
	Zuth::Matrix<int> m1(3,3,data2);
	Zuth::Matrix<int> m22=m1.block(0, 0, 1, 1);
	cout << m22;
	//行列
	cout << std::endl;
	Zuth::Matrix<int> m23 = m1.row(1);
	Zuth::Matrix<int> m24 = m1.col(1);
	cout << m23<<m24;
	// 零矩阵
	Zuth::Matrix<int> m25 = Zuth::Zeros<int>(2);
	cout << m25;
	Zuth::Matrix<int> m26 = Zuth::Zeros<int>(2,7);
	cout << m26;
	// 单位矩阵
	Zuth::Matrix<int> m27 = Zuth::Eye<int>(2);
	cout << m27;
	// 矩阵转置
	int data5[4] = { 1,2,3,4 };
	Zuth::Matrix<int> m28(2, 2, data5);
	Zuth::Matrix<int> m29= Transpose(m28);
	cout << m28<<m29;
}
