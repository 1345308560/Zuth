#ifndef _ADVANCED_ALGEBRA_H
#define _ADVANCED_ALGEBRA_H

#include"Core.h"
namespace Zuth {
// 密集矩阵
#include"Dense.h"
// 稀疏矩阵

// 数值积分 

const int N = 1000 * 1000;

double simpsonIntegration(double (*f)(double),double a, double b) {
  double h = (b - a) / N;
  double s = f(a) + f(b);
  for (int i = 1; i <= N - 1; ++i) {
    double x = a + h * i;
    s += f(x) * ((i & 1) ? 4 : 2);
  }
  s *= h / 3;
  return s;
}
// 自适应辛普森
double simpson(double (*f)(double),double l, double r) {
    double mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;  // 辛普森公式
}

double asr(double (*f)(double),double l, double r, double eqs, double ans, int step) {
    double mid = (l + r) / 2;
    double fl = simpson(f,l, mid), fr = simpson(f,mid, r);
    if (abs(fl + fr - ans) <= 15 * eqs && step < 0)
        return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
    return asr(f,l, mid, eqs / 2, fl, step - 1) +
        asr(f,mid, r, eqs / 2, fr, step - 1);  // 否则分割成两段递归求解
}

double zSimpsonIntegration(double (*f)(double),double l, double r, double eps) {
    return asr(f,l, r, eps, simpson(f,l, r), 12);
}

}

#endif
