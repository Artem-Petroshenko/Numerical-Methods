#include "NM.h"

double f(double x, double y) {
	return (3 * x * x * exp(-x) - (x + 1) * y) / x;
}

double y(double x) {
	return x * x * exp(-x);
}

double Calculate(double h, double x_j, double y_j) {
	double k1 = f(x_j, y_j);
	double k2 = f(x_j + h / 2, y_j + k1 * h / 2);
	double k3 = f(x_j + h, y_j - h * k1 + 2 * h * k2);
	return y_j + h * (k1 + 4 * k2 + k3) / 6;
}

void Error(double a, double f_a, double b, ofstream* F) {
	F->precision(20);
	double h = b - a;
	for (int i = 0; i < 15; i++) {
		double tmp_h = h / pow(2, i);
		double tmp1 = Calculate(tmp_h, a, f_a);
		*F << abs(tmp1 - y(a + tmp_h)) << ';';
		for (int j = 1; j < pow(2, i); j++) {
			tmp1 = Calculate(tmp_h, a + tmp_h * j, tmp1);
		}
		*F << abs(tmp1 - y(b)) << ';' << tmp_h << endl;
	}
	return;
}

vector<double> Runge_Kutta(double a, double f_a, double b, int n) {
	vector<double> res;
	double h = (b - a) / n;
	res.push_back(h);
	double x = a;
	double f_x = f_a;
	double y;
	while (x < b) {
		y = Calculate(h, x, f_x);
		x += h;
		res.push_back(y);
		f_x = y;
	}
	return res;
}

double Pertubation(double a, double f_a, double df_a, double b, int n) {
	double res;
	double h = (b - a) / n;
	double x = a;
	double f_x = f_a - df_a;
	double y;
	while (x <= b) {
		y = Calculate(h, x, f_x);
		x += h;
		f_x = y;
	}
	res = y;
	return res;
}