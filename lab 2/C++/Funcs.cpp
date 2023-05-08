#include "NM.h"

int GetNum(ifstream* F) {
	int num;
	*F >> num;
	return num;
}

double fGetNum(ifstream* F) {
	double num;
	*F >> num;
	return num;
}

vector<double> ImportData(ifstream* F, int n) {
	vector<double> vec(n);
	for (int i = 0; i < n; i++)
		*F >> vec.at(i);
	return vec;
}

matrix_t MatrixInit(int size) {
	matrix_t A;
	A.rang = size;
	A.cell.resize(size);
	for (int i = 0; i < A.rang; i++)
		A.cell.at(i).resize(size);
	return A;
}

vector<double> ThomasAlgorythm(double h, vector<double> y_i, double a_der, double b_der) {
	vector<double> M_i(y_i.size());
	//filling the SLAE
	int n = y_i.size() - 2;
	matrix_t M = MatrixInit(n);
	vector<double> r(n);
	M.cell.at(0).at(0) = 2 * h / 3;
	M.cell.at(0).at(1) = h / 6;
	M.cell.at(n - 1).at(n - 2) = h / 6;
	M.cell.at(n - 1).at(n - 1) = 2 * h / 3;
	r.at(0) = (y_i.at(2) + y_i.at(0) - 2 * y_i.at(1)) / h - a_der * h / 6;
	r.at(n - 1) = (y_i.at(n + 1) + y_i.at(n - 1) - 2 * y_i.at(n)) / h - b_der * h / 6;
	for (int i = 1; i < n - 1; i++) {
		M.cell.at(i).at(i - 1) = h / 6;
		M.cell.at(i).at(i) = 2 * h / 3;
		M.cell.at(i).at(i + 1) = h / 6;
		r.at(i) = (y_i.at(i + 2) + y_i.at(i) - 2 * y_i.at(i + 1)) / h;
	}
	//Thomas Algorythm
	vector<double> delta(M.rang);
	vector<double> lambda(M.rang);
	delta.at(0) = -M.cell.at(0).at(1) / M.cell.at(0).at(0);
	lambda.at(0) = r.at(0) / M.cell.at(0).at(0);
	for (int i = 1; i < n - 1; i++) {
		double b = M.cell.at(i).at(i - 1);
		double c = M.cell.at(i).at(i);
		double d = M.cell.at(i).at(i + 1);
		delta.at(i) = -d / (b * delta.at(i - 1) + c);
		lambda.at(i) = (r.at(i) - b * lambda.at(i - 1)) / (b * delta.at(i - 1) + c);
	}
	double b = M.cell.at(n - 1).at(n - 2);
	double c = M.cell.at(n - 1).at(n - 1);
	delta.at(n - 1) = 0;
	lambda.at(n - 1) = (r.at(n - 1) - b * lambda.at(n - 2)) / (b * delta.at(n - 2) + c);
	M_i.at(n - 1) = lambda.at(n - 1);
	for (int i = n - 2; i >= 0; i--)
		M_i.at(i) = delta.at(i) * M_i.at(i + 1) + lambda.at(i);
	vector<double> X(n + 2);
	X.at(0) = a_der;
	for (int i = 0; i < n; i++)
		X.at(i + 1) = M_i.at(i);
	X.at(n + 1) = b_der;
	return X;
}

pair<vector<double>, vector<double>> FindConstants(double h, vector<double> y_i, vector<double> M_i) {
	vector<double> C(y_i.size() - 1);
	vector<double> C_tilda(y_i.size() - 1);
	for (int i = 0; i < C.size(); i++) {
		C.at(i) = (y_i.at(i + 1) - y_i.at(i)) / h - (M_i.at(i + 1) - M_i.at(i)) * h / 6;
		C_tilda.at(i) = y_i.at(i) - M_i.at(i) * h * h / 6;
	}
	pair<vector<double>, vector<double>> constants;
	constants = make_pair(C, C_tilda);
	return constants;
}

double g_i(double xx, double left_M, double right_M, double left_x, double right_x, double C, double C_tilda) {
	double h = right_x - left_x;
	return left_M * pow((right_x - xx), 3) / (6 * h) + right_M * pow((xx - left_x), 3) / (6 * h) + C * (xx - left_x) + C_tilda;
}

vector<double> CubicSpline(vector<double> xx, vector<double> x_i, vector<double> y_i, vector<double> M_i, pair<vector<double>, vector<double>> C) {
	vector<double> yy(xx.size());
	for (int i = 1, j = 0; i < x_i.size(); i++)
		while (j < xx.size() && xx.at(j) <= x_i.at(i)) {
			//C.first = C
			//C.second = C_tilda; 
			yy.at(j) = g_i(xx.at(j), M_i.at(i - 1), M_i.at(i), x_i.at(i - 1), x_i.at(i), C.first.at(i - 1), C.second.at(i - 1));
			j++;
		}
	return yy;
}

void OutputVector(vector<double> vec, ofstream* F) {
	F->precision(20);
	for (int i = 0; i < vec.size(); i++)
		*F << vec.at(i) << ";";
	*F << "\n";
	return;
}