#ifndef _INTELLIGENTALGORITHM
#define _BP_NET_H
#include<cmath>
#include<ctime>
namespace Zuth{
	class IA {
	public:
		IA(){};
		virtual double getAns()=0;
		~IA(){};
	};

	class MounClimbling:public IA
	{
		double ans;
	public:
		MounClimbling(double (*f)(double), double a, double b) {
			double start = a;
			double step = (b - a) / 1000;
			for (int i = 0; i < 1000; i++) {
				if (f(start) > f(start + step)) {
					start += step;
				}
			}
			ans = f(start);
		}
		virtual double getAns() {
			return ans;
		}
	};
	class SA :public IA{
		double ans;
	public:
		SA(double (*f)(double), double a, double b) {
			srand(time(NULL));
			double T = 1000;//初始温度
			double Td = 0.96;//降温速度
			double Te = 10;//结束温度
			double r = (double)rand() / RAND_MAX;
			double start = (b - a) * r + a; // 初始解

			for (int i=1; T > Te; T *= Td,i++) {
				double step = (double)(b - a)/2/i;// 步长
				double r2 = pow(-1, rand());
				//cout << start << endl;
				while (step * r2 + start < a || step * r2 + start > b) {
					r2 = pow(-1, rand());
				}
				double newPos = step * r2 + start;
				if (f(newPos) < f(start))start = newPos;
				else {
					double r3= (double)rand() / RAND_MAX;
					double p = exp(-1*(f(newPos)-f(start))*1000/T);
					if(r3<p)start = newPos;
				}
			}
			ans = start;
		}
		double getAns() {
			return ans;
		}
	};
}

#endif
