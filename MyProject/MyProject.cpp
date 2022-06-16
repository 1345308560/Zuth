#include <iostream>
#include <vector>
#include "Core.h"
#include "MachineLearning.h"
#include "AdvancedAlgebra.h"
#include "AdvancedAlgorithm.h"
#include "IntelligentAlgorithm.h"
using namespace std;
void test_algorithm();// 核心算法代码测试
void test_algebra();
void test_class();
void test_advanced_algorithm();// 测试高级算法
void test_advanced_algebre();
void test_machine_learning();
void test_Inte_algorithm();// 测试智能优化算法
double func1(double n) { return n; }// 线性函数
double func2(double n) { return n * n; }// 二次函数
int main()
{	
	 //test_algorithm();
	 //test_algebra();
	//test_class();
	test_advanced_algorithm();
	//test_advanced_algebre();
	//test_machine_learning();
	 //test_Inte_algorithm();
}
void test_Inte_algorithm() {
	// 爬山
	Zuth::MounClimbling MC(func2, -10, 10);
	cout << MC.getAns() << endl;
	// 模拟退火
	Zuth::SA S(func2, -10, 10);
	cout << S.getAns() << endl;
}
void test_machine_learning() {
	Zuth::BpNet testNet;
	// 学习样本
	vector<double> samplein[4];
	vector<double> sampleout[4];
	samplein[0].push_back(0); samplein[0].push_back(0); sampleout[0].push_back(0);
	samplein[1].push_back(0); samplein[1].push_back(1); sampleout[1].push_back(1);
	samplein[2].push_back(1); samplein[2].push_back(0); sampleout[2].push_back(1);
	samplein[3].push_back(1); samplein[3].push_back(1); sampleout[3].push_back(0);
	Zuth::sample sampleInOut[4];
	for (int i = 0; i < 4; i++)
	{
		sampleInOut[i].in = samplein[i];
		sampleInOut[i].out = sampleout[i];
	}
	vector<Zuth::sample> sampleGroup(sampleInOut, sampleInOut + 4);
	testNet.training(sampleGroup, 0.0001);

	// 测试数据
	vector<double> testin[4];
	vector<double> testout[4];
	testin[0].push_back(0.1);   testin[0].push_back(0.2);
	testin[1].push_back(0.15);  testin[1].push_back(0.9);
	testin[2].push_back(1.1);   testin[2].push_back(0.01);
	testin[3].push_back(0.88);  testin[3].push_back(1.03);
	Zuth::sample testInOut[4];
	for (int i = 0; i < 4; i++) testInOut[i].in = testin[i];
	vector<Zuth::sample> testGroup(testInOut, testInOut + 4);

	// 预测测试数据，并输出结果
	testNet.predict(testGroup);
	for (int i = 0; i < testGroup.size(); i++)
	{
		for (int j = 0; j < testGroup[i].in.size(); j++) cout << testGroup[i].in[j] << "\t";
		cout << "-- prediction :";
		for (int j = 0; j < testGroup[i].out.size(); j++) cout << testGroup[i].out[j] << "\t";
		cout << endl;
	}
}
void test_advanced_algebre() {
	// 辛普森
	cout << Zuth::simpsonIntegration(func1, 0, 1)<<endl;
	// 自适应辛普森
	cout << Zuth::zSimpsonIntegration(func1, 0, 1, 0.0001)<<endl;
	// 高斯消元
	double data[12] = { 2,1,-1,8,-3,-1,2,-11,-2,1,2,-3 };
	Zuth::Matrix<double> m(3, 4, data);
	Zuth::Matrix<double> m2 = Zuth::gaussianElimination(m);
	cout << m << m2 << endl;
	// LU分解求解线性方程组
	Zuth::Vector<double> ans1 = Zuth::LUsolve(m);
	cout << m << endl;
	for (int i = 0; i < ans1.getsize(); i++)cout << ans1[i] << ' ';
	cout <<endl;
	// QR分解
	double datan[9] = { 2,-2,3,1,1,1,1,3,-1 };
	Zuth::Matrix<double> M2(3,3,datan);
	cout << M2 << endl;
	Zuth::Vector<Zuth::Matrix<double> >ans2=Zuth::QR<double>(M2);
	cout << ans2[0] << ans2[1] << endl;
	// QR分解求解方程
	Zuth::Vector<double>  ans3=Zuth::QRsolve(m);
	for (int i = 0; i < ans3.getsize(); i++)cout << ans3[i] << ' ';
	cout << endl;
	// 曲线拟合
	double arry1[5] = { 0,0.25,0,5,0.75 };
	double arry2[5] = { 1,1.283,1.649,2.212,2.178 };
	double coefficient[5];
	memset(coefficient, 0, sizeof(double) * 5);
	std::vector<double> vx, vy;
	for (int i = 0; i < 5; i++)
	{
		vx.push_back(arry1[i]);
		vy.push_back(arry2[i]);
	}
	Zuth::CurveFit<double> cf(vx, vy, 5, 3, coefficient);
	printf("拟合方程为：y = %lf + %lfx + %lfx^2 \n", coefficient[1], coefficient[2], coefficient[3]);
	// 稀疏矩阵构造
	Zuth::Matrix<double> ms1 = Zuth::Eye<double>(4);
	Zuth::SparseMatrix<double> ms2(ms1);
	Zuth::Matrix<double> ms3 = ms2.orignMatrix();
	cout << "原矩阵\n"<<ms1<<"压缩矩阵\n"<<ms2<<"还原矩阵\n"<<ms3<<endl;
	// 稀疏矩阵加法
	Zuth::SparseMatrix<double> ms4 = ms1 + ms1;
	ms3 = ms4.orignMatrix();
	cout << ms3<<endl;
	ms4 = ms1 - ms1;
	ms3 = ms4.orignMatrix();
	cout << ms3 << endl;
	// 稀疏转置
	double data7[4] = { 1,2,3,4 };
	Zuth::Matrix<double> m7(2, 2, data7);
	Zuth::SparseMatrix<double> sm7(m7);
	sm7 = sm7.Transpose();
	ms3 = sm7.orignMatrix();
	cout << m7<<endl<<ms3;
	// 卡特兰数
	cout << Zuth::Catalan(10);
	cout << endl;
	// 贝尔数
	cout << Zuth::Bell(4);
	// 开方
	cout << endl << "sqrt(67)=" << Zuth::sqrtNewton(67) << endl;
}
void test_advanced_algorithm() {
	// 线段树
	Zuth::SegmentTree seg(51);
	std::vector<int> nums{ 1,2,3,4,5,6,2,2,7,8,9,0 };
	for (auto i : nums) {
		seg.insert(i);
	}
	cout << seg.count(2, 3) << endl;
	seg.erase(3);
	cout << seg.count(2, 3) << endl;
	// 乘法逆元
	int n1=5, n2=7, n3, n4;
	Zuth::exgcd(n1, n2, n3, n4);
	cout << n1 << " " << n2 << " " << n3 << " " << n4 << endl;
	// 树状数组
	Zuth::Vector<int> Zu;
	for (int i = 0; i < 9; i++)Zu.pushback(i+1);
	Zuth::BitTree Zb(Zu);
	cout << Zb.qSum(1, 2);
}
void test_class() {
	// 矩阵运算
	double data[4] = { 1,2,3,4 };
	Zuth::Matrix<double> m11(2, 2, data);
	Zuth::Matrix<double> m12 = m11 + m11;
	cout << m11 << m12;
	Zuth::Matrix<double> m13 = m12 * m11;
	cout << m11 << m13;
	// 大数
	Zuth::BigNum b1(123);
	Zuth::BigNum b2= b1 * 99;
	cout << b2<<endl;
	// 矩阵的逆
	Zuth::Matrix<double> m1(2, 2,data );
	Zuth::Matrix<double> m2 = m1.adgMatrix();
	cout << m1 << m2;
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
	// 并查集
	Zuth::DisjointSet Ds(10);
	cout << "size is " << Ds.setNumber() << endl;
	Ds.dUnion(0, 1);
	Ds.dUnion(0, 5);
	cout << "size is "<<Ds.setNumber() << endl;
	// 快速排序
	int dataq[6] = { 5,7,3,9,3,7 };
	cout << "quick sort" << endl;
	for (int i = 0; i < 6; i++)cout << dataq[i] << " ";
	cout << endl;
	Zuth::quickSort(dataq,  6);
	for (int i = 0; i < 6; i++)cout << dataq[i] << " ";
	cout << endl;
	// 归并排序
	int datam[6] = { 5,7,3,9,3,7 };
	cout << "merge sort" << endl;
	for (int i = 0; i < 6; i++)cout << datam[i] << " ";
	cout << endl;
	Zuth::mergeSort(datam, 0,6);
	for (int i = 0; i < 6; i++)cout << datam[i] << " ";
	cout << endl;
	// 堆排序
	int datah[6] = { 5,7,3,9,3,7 };
	cout << "heap sort" << endl;
	for (int i = 0; i < 6; i++)cout << datah[i] << " ";
	cout << endl;
	Zuth::heapSort(datah, 6);
	for (int i = 0; i < 6; i++)cout << datah[i] << " ";
	cout << endl;
	// 希尔排序
	int datas[6] = { 5,7,3,9,3,7 };
	cout << "shell sort" << endl;
	for (int i = 0; i < 6; i++)cout << datas[i] << " ";
	cout << endl;
	Zuth::shellSort(datas, 6);
	for (int i = 0; i < 6; i++)cout << datas[i] << " ";
	cout << endl;
}