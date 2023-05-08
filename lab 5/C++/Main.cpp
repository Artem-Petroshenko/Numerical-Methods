#include "NM.h"

int main() {
	const char* filepert = "pert.csv";
	const char* fileout = "Koshi.csv";
	const char* filerr = "Error.csv";
	remove(fileout);
	remove(filerr);
	remove(filepert);
	ofstream F1(fileout, ios_base::app);
	ofstream F2(filerr, ios_base::app);
	ofstream F3(filepert, ios_base::app);
	double a = 1, b = 5;
	double f_a = 1 / exp(1);
	double eps;
	vector<double> tmp;
	F1.precision(20);
	F2.precision(20);
	F3.precision(20);
	int n = pow(2, 5);
	tmp = Runge_Kutta(a, f_a, b, n);
	for (int i = -1; i < n; i++) 
		F1 << tmp.at(i + 1) << endl;
	Error(a, f_a, b, &F2);
	double pert;
	n = pow(2, 10);
	for (pert = 1.0; pert >= 1e-10; pert /= 10) {
		F3 << Pertubation(a, f_a, pert * f_a, b, n) << endl;
		F3 << Pertubation(a, f_a, -pert * f_a, b, n) << endl;
	}
	F1.close();
	F2.close();
	F3.close();
	return 0;
}