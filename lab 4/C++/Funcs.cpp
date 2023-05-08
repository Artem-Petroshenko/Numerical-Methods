#include "NM.h"

double MyRand(void) {
	return rand() / (double)RAND_MAX;
}

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

matrix_t ImportMatrix(ifstream* F, int rang) {
	matrix_t matrix;
	matrix.rang = rang;
	for (int i = 0; i < rang; i++)
	{
		matrix.A.resize(i + 1);
		for (int j = 0; j < rang; j++)
		{
			matrix.A.at(i).resize(j + 1);
			*F >> matrix.A.at(i).at(j);
		}
	}
	return matrix;
}

vector<double> RandomVector(int size) {
	vector<double> Res;
	for (int i = 0; i < size; i++)
		Res.push_back(MyRand());
	return Res;
}

vector<double> VectorSubstract(vector<double> vec1, vector<double> vec2) {
	vector<double> VecRes;
	for (int i = 0; i < vec1.size(); i++)
		VecRes.push_back(vec1.at(i) - vec2.at(i));
	return VecRes;
}

vector<double> MatrixMulVector(matrix_t matrix, vector<double> vec) {
	vector<double> VecRes(vec.size());
	for (int i = 0; i < matrix.rang; i++)
		for (int j = 0; j < matrix.rang; j++)
			VecRes.at(i) += matrix.A.at(i).at(j) * vec.at(j);
	return VecRes;
}

vector<double> VectorMulNumber(vector<double> vec, double num) {
	vector<double> Res;
	for (int i = 0; i < vec.size(); i++)
		Res.push_back(num * vec.at(i));
	return Res;
}

double Norm(vector<double> vec) {
	double Res = 0;
	for (int i = 0; i < vec.size(); i++)
		Res += vec.at(i) * vec.at(i);
	return sqrt(Res);
}

double MaxComponent(vector<double> vec) {
	double maximum = vec.at(0);
	for (int i = 1; i < vec.size(); i++) {
		if (fabs(maximum) < fabs(vec.at(i)))
			maximum = vec.at(i);
	}
	return maximum;
}

//Возвращает вектор, последним элементом которого, является собственное число, 
//а предыдущие образуют собственный вектор,
//соответствующий этому собственному числу
vector<double> PowerMethod(matrix_t A, double eps) {
	double k = 1.0;
	vector<double> y = RandomVector(A.rang);
	double mu = MaxComponent(y);
	vector<double> y_norm = VectorMulNumber(y, 1 / mu);
	while (Norm(VectorSubstract(MatrixMulVector(A, y_norm), VectorMulNumber(y_norm, mu))) / Norm(y_norm) > eps) {
		y = MatrixMulVector(A, y_norm);
		mu = MaxComponent(y);
		y_norm = VectorMulNumber(y, 1 / mu);
		k++;
	}
	vector<double> Res = y_norm;
	Res.push_back(mu);
	Res.push_back(k);
	return Res;
}

matrix_t Shift(matrix_t A, double mu) {
	matrix_t B;
	for (int i = 0; i < A.rang; i++) 
		A.A.at(i).at(i) -= mu;
	B = A;
	return B;
}

vector<double> ShiftPowerMethod(matrix_t A, double mu, double eps) {
	matrix_t B = Shift(A, mu);
	vector<double> Res = PowerMethod(B, eps);
	Res.at(Res.size() - 2) += mu;
	return Res;
}

void OutputVector(vector<double> vec, ofstream* F) {
	F->precision(20);
	*F << vec.at(vec.size() - 1) << ";";
	for (int i = 0; i < vec.size() - 1; i++)
		*F << vec.at(i) << ";";
	*F << "\n";
	return;
}