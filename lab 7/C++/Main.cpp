#include "NM.h"

int main() {
	double alpha0 = 1;
	double alpha1 = -1;
	double beta0 = 1;
	double beta1 = 1;
	double A = -1;
	double B = 2 * exp(1) - 1;

	const char* fileout = "y.csv";
	remove("y.csv");
	ofstream F(fileout, ios_base::app);
	double a = 0, b = 1;
	int n = 5;
	vector<vector<double>> W;
	W = CreateMatrix(a, b, n, alpha0, alpha1, beta0, beta1, A, B);
	vector<double> y;
	y = ThomasAlgorithm(W.at(0), W.at(1), W.at(2), W.at(3));
	F.precision(20);
	for (int i = 0; i <= n; i++)
		F << y.at(i) << endl;
	F.close();

	const char* filerr = "err.csv";
	remove("err.csv");
	ofstream F2(filerr, ios_base::app);
	for (n = 500; n >= 10; n--) {
		W = CreateMatrix(a, b, n, alpha0, alpha1, beta0, beta1, A, B);
		y = ThomasAlgorithm(W.at(0), W.at(1), W.at(2), W.at(3));
		for (int i = 0; i <= n; i++)
			F2 << y.at(i) << ";";
		F2 << endl;
	}
	F2.close();

	const char* filepert = "pertubation.csv";
	remove("pertubation.csv");
	ofstream F3(filepert, ios_base::app);
	n = 10;
	for (double pert = 1.0; pert >= 1e-10; pert /= 10) {
		double dA = A * pert;
		W = CreateMatrix(a, b, n, alpha0, alpha1, beta0, beta1, A - dA, B);
		y = ThomasAlgorithm(W.at(0), W.at(1), W.at(2), W.at(3));
		for (int i = 0; i <= n; i++)
			F3 << y.at(i) << ";";
		F3 << endl;
	}
	for (double pert = 1.0; pert >= 1e-10; pert /= 10) {
		double dB = B * pert;
		W = CreateMatrix(a, b, n, alpha0, alpha1, beta0, beta1, A, B + dB);
		y = ThomasAlgorithm(W.at(0), W.at(1), W.at(2), W.at(3));
		for (int i = 0; i <= n; i++)
			F3 << y.at(i) << ";";
		F3 << endl;
	}
	for (double pert = 1.0; pert >= 1e-10; pert /= 10) {
		double dA = A * pert;
		double dB = B * pert;
		W = CreateMatrix(a, b, n, alpha0, alpha1, beta0, beta1, A - dA, B + dB);
		y = ThomasAlgorithm(W.at(0), W.at(1), W.at(2), W.at(3));
		for (int i = 0; i <= n; i++)
			F3 << y.at(i) << ";";
		F3 << endl;
	}
	F3.close();
	return 0;
}