#include "NM.h"

double p(double x) {
	return exp(x) + 1;
}

double q(double x) {
	return -1;
}

double r(double x) {
	return -exp(x);
}

double f(double x) {
	return exp(x);
}

vector<vector<double>> CreateMatrix(double a, double b, int n, double alpha0, double alpha1, double beta0, double beta1, double A, double B) {
	vector<vector<double>> W(4);
	vector<double> w0(n);
	vector<double> w1(n + 1); //main diag
	vector<double> w2(n);
	vector<double> F(n + 1);
	double h = (b - a) / n;
	for (int i = 1; i < n; i++) {
		w0.at(i - 1) = -p(a + i * h) + q(a + i * h) * h / 2;
		w1.at(i) = -r(a + i * h) * h * h + 2 * p(a + i * h);
		w2.at(i) = -p(a + i * h) - q(a + i * h) * h / 2;
		F.at(i) = -f(a + i * h) * h * h;
	}
	double c1 = (-alpha1 / 2) / w2.at(1);
	double c2 = (beta1 / 2) / w0.at(n - 2);
	w1.at(0) = (alpha0 * h - alpha1 * 3.0 / 2) - c1 * w0.at(0);
	w2.at(0) = 2 * alpha1 - c1 * w1.at(1);
	F.at(0) = A * h - c1 * F.at(1);
	w1.at(n) = (beta0 * h + beta1 * 3.0 / 2) - c2 * w2.at(n - 1);
	w0.at(n - 1) = -2 * beta1 - c2 * w1.at(n - 1);
	F.at(n) = h * B - c2 * F.at(n - 1);
	W.at(0) = w0;
	W.at(1) = w1;
	W.at(2) = w2;
	W.at(3) = F;
	return W;
}

vector<double> ThomasAlgorithm(vector<double> w0, vector<double> w1, vector<double> w2, vector<double> F) {
	int n = w0.size();
	vector<double> delta(n + 1);
	vector<double> lambda(n + 1);
	delta.at(0) = -w2.at(0) / w1.at(0);
	lambda.at(0) = F.at(0) / w1.at(0);
	for (int i = 1; i < n; i++) {
		double b = w0.at(i - 1);
		double c = w1.at(i);
		double d = w2.at(i);
		delta.at(i) = -d / (b * delta.at(i - 1) + c);
		lambda.at(i) = (F.at(i) - b * lambda.at(i - 1)) / (b * delta.at(i - 1) + c);
	}
	double b = w0.at(n - 1);
	double c = w1.at(n);
	delta.at(n) = 0;
	lambda.at(n) = (F.at(n) - b * lambda.at(n - 1)) / (b * delta.at(n - 1) + c);
	vector<double> Y(n + 1);
	Y.at(n) = lambda.at(n);
	for (int i = n - 1; i >= 0; i--)
		Y.at(i) = delta.at(i) * Y.at(i + 1) + lambda.at(i);
	return Y;
}