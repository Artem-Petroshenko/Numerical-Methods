#include "NM.h"

vector<double> t = { -1 / sqrt(2), 0, 1 / sqrt(2) };

double f(double x) {
	return pow(0.5, x) + 1 - pow(x - 2, 2);
}

vector<double> Nodes(double a, double b) {
	vector<double> vec;
	for (int j = 0; j < 3; j++) 
		vec.push_back((a + b) / 2 + (b - a) * t.at(j) / 2);
	return vec;
}

double Integrate(double a, double h, int n) {
	double I = 0;
	for (int i = 0; i < n; i++) {
		vector<double> x = Nodes(a + h * i, a + h * (i + 1.0));
		I += f(x.at(0)) + f(x.at(1)) + f(x.at(2));
	}
	return I * h / 3;
}

pair<double, int> Chebyshev(double a, double b, double eps) {
	pair<double, int> p;
	double I_cur, I_next;
	double h = b - a;
	int n = 1;
	I_next = Integrate(a, h, n);
	do {
		I_cur = I_next;
		h /= 2;
		n *= 2;
		I_next = Integrate(a, h, n);
	} while (abs(I_cur - I_next) > 15 * eps);
	p = make_pair(I_next, n);
	return p;
}