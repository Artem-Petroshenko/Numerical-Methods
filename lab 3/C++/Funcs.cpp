#include "NM.h"

double f(double x) {
	return pow(0.5, x) + 1 - pow(x - 2, 2);
}

double Integrate(double h, double a, int n) {
	double I = 0;
	for (int j = 0; j < n - 1; j += 3) 
		I += 3 * (f(a + h * (j + 1.0)) + f(a + h * (j + 2.0))) + 2 * f(a + h * (j + 3.0));
	I += f(a) - f(a + h * (n - 1.0));
	I *= 3 * h / 8;
	return I;
}

pair<double, int> Newton_Cotes(double a, double b, double eps) {
	pair<double, int> x;
	double I_cur, I_next;
	int n = 4;
	double h = (b - a) / (n - 1.0);
	I_next = Integrate(h, a, n);
	int i = 1;
	do {
		I_cur = I_next;
		n = 2 * n - 1;
		h /= 2;
		I_next = Integrate(h, a, n);
		i *= 2;
	} while (abs(I_next - I_cur) > 15 * eps);
	x = make_pair(I_next, i);
	return x;
}