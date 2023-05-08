#include "NM.h"

int GetNum(ifstream* F) {
	int num;
	*F >> num;
	return num;
}

vector<double> ImportData(ifstream *F, int n) {
	vector<double> vec(n);
	for (int i = 0; i < n; i++)
		*F >> vec.at(i);
	return vec;
}

double Lagrange(double x, vector<double> x_i, vector<double> y_i) {
	double y = 0;
	double tmp = 1;
	for (int i = 0; i < y_i.size(); i++) {
		for (int k = 0; k < x_i.size(); k++) {
			if (k == i)
				continue;
			tmp *= (x - x_i.at(k)) / (x_i.at(i) - x_i.at(k));
		}
		y += y_i.at(i) * tmp;
		tmp = 1;
	}
	return y;
}

vector<double> Values(vector<double> xx, vector<double> x_i, vector<double> y_i) {
	vector<double> yy(xx.size());
	for (int i = 0; i < xx.size(); i++)
		yy.at(i) = Lagrange(xx.at(i), x_i, y_i);
	return yy;
}

double LagrangeUniformGrid(double x, vector<double> x_i, vector<double> y_i) {
	double y = 0;
	double tmp = 1;
	double h = x_i.at(1) - x_i.at(0);
	double t = (x - x_i.at(0)) / h;
	for (int i = 0; i < y_i.size(); i++) {
		for (int k = 0; k < x_i.size(); k++) {
			if (k == i)
				continue;
			tmp *= (t - k) / (i - k);
		}
		y += y_i.at(i) * tmp;
		tmp = 1;
	}
	return y;
}

vector<double> ValuesUniformGrid(vector<double> xx, vector<double> x_i, vector<double> y_i) {
	vector<double> yy(xx.size());
	for (int i = 0; i < xx.size(); i++)
		yy.at(i) = LagrangeUniformGrid(xx.at(i), x_i, y_i);
	return yy;
}

void OutputVector(vector<double> vec, ofstream* F) {
	F->precision(20);
	for (int i = 0; i < vec.size(); i++)
		*F << vec.at(i) << ";";
	*F << "\n";
	return;
}