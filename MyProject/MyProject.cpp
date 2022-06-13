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

}
