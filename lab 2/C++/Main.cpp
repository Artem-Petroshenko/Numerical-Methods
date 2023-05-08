#include "NM.h"

int main(void) {
	const char* datapoints = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab2\\datapoints.csv";
	const char* filexx = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab2\\xx.csv";
	const char* nodes = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab2\\nodes.csv";
	const char* derivatives = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab2\\derivatives.csv";
	const char* fileoutput = "yy.csv";
	remove(fileoutput);
	ifstream F1(datapoints);
	ifstream F2(filexx);
	ifstream F3(nodes);
	ifstream F4(derivatives);
	ofstream F5(fileoutput, ios_base::app);
	int k = GetNum(&F3);
	F3.close();
	double a_der = fGetNum(&F4);
	double b_der = fGetNum(&F4);
	F4.close();
	vector<double> xx = ImportData(&F2, 1000);
	F2.close();
	for (int i = 0; i < k; i++) {
		int n = GetNum(&F1);
		vector<double> x_i = ImportData(&F1, n);
		vector<double> y_i = ImportData(&F1, n);
		double h = x_i.at(1) - x_i.at(0);
		vector<double> M = ThomasAlgorythm(h, y_i, a_der, b_der);
		pair<vector<double>, vector<double>> C = FindConstants(h, y_i, M);
		vector<double> yy = CubicSpline(xx, x_i, y_i, M, C);
		OutputVector(yy, &F5);
	}
	//Part 2
	const char* datapoints2 = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab2\\datapoints2.csv";
	const char* derivatives2 = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab2\\der_error.csv";
	const char* fileoutput2 = "yy2.csv";
	remove(fileoutput2);
	ifstream F6(datapoints2);
	ifstream F7(derivatives2);
	ofstream F8(fileoutput2, ios_base::app);
	int n = GetNum(&F6);
	vector<double> x_i = ImportData(&F6, n);
	vector<double> y_i = ImportData(&F6, n);
	F6.close();
	double h = x_i.at(1) - x_i.at(0);
	for (int i = 0; i < 11; i++) {
		a_der = fGetNum(&F7);
		b_der = fGetNum(&F7);
		vector<double> M = ThomasAlgorythm(h, y_i, a_der, b_der);
		pair<vector<double>, vector<double>> C = FindConstants(h, y_i, M);
		vector<double> yy = CubicSpline(xx, x_i, y_i, M, C);
		OutputVector(yy, &F8);
	}
	F7.close();
	F8.close();
	return 0;
}