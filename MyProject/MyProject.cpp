#include <iostream>
#include "Core.h"
using namespace std;
void test_algorithm();// 核心算法代码测试
void test_algebra();
void test_class();
int main()
{	
	// test_algorithm();
	// test_algebra();
	test_class();
}
void test_class() {
	Zuth::BigNum b1(123);
	Zuth::BigNum b2= b1 * 99;
	cout << b2;
}
void test_algebra() {
	// 素数筛
	Zuth::Vector<bool> Vb = Zuth::eratosthenesSieve(50);
	cout << "50以内的素数" << endl;
	for (int i = 2; i < Vb.getsize(); i++)if (!Vb[i])cout << i << " ";
	cout << endl;
	// 素数筛
	cout << "50以内的素数" << endl;
	Zuth::Vector<int> Vc = Zuth::eulerSieve(50);
	for (int i = 0; i < Vc.getsize(); i++)cout << Vc[i]<<" ";
	// 快速幂
	cout << "\n" << "pow(2,2)=" << Zuth::quickPower(2, 2) ;
	cout << "\n" << "pow(3,3)=" << Zuth::quickPower(3, 3) ;
	cout << "\n" << "pow(5,5)=" << Zuth::quickPower(5, 5) << endl;
	
}
void test_algorithm() {
	// 一维前缀和
	Zuth::Vector<int> V;
	for (int i = 1; i < 10; i++)V.pushback(i);
	cout << "orign vector" << endl;
	for (int i = 0; i < V.getsize(); i++)cout << V[i] << " ";
	cout << endl<<"prefix vector" << endl;
	Zuth::Vector<int> V1 = Zuth::Prefix(V);
	for (int i = 0; i < V1.getsize(); i++)cout << V1[i] << " ";
	cout << endl;
	// 一阶差分
	Zuth::Vector<int> V2 = Zuth::Difference(V);
	cout << "Difference vector" << endl;
	for (int i = 0; i < V2.getsize(); i++)cout << V2[i] << " ";
	cout << endl;
	// 二维前缀和
	int data[4] = { 1,2,3,4 };
	Zuth::Matrix<int> M(2, 2,data);
	Zuth::Matrix<int> M2 ;
	M2 = Zuth::Prefix(M);
	cout << "orign matrix\n"<<M << "prefix matrix\n" << M2<<endl;
	// 二维差分
	Zuth::Matrix<int> M3;
	M2 = Zuth::Difference(M);
	cout << "difference matrix\n" << M2 << endl;
}