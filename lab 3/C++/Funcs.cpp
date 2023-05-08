#include "NM.h"

int GetNum(ifstream* F) {
	int num;
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

vector<double> ImportRightPart(ifstream* F, int rang) {
	vector<double> b;
	for (int i = 0; i < rang; i++)
	{
		b.resize(i + 1);
		*F >> b.at(i);
	}
	return b;
}

vector<double> RandomVector(int size) {
	vector<double> Res;
	for (int i = 0; i < size; i++)
		Res.push_back(0);
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

double ScalarProduct(vector<double> vec1, vector<double> vec2) {
	double Res = 0.0;
	for (int i = 0; i < vec1.size(); i++)
		Res += vec1.at(i) * vec2.at(i);
	return Res;
}

double Norm(vector<double> vec) {
	double Res = 0;
	for (int i = 0; i < vec.size(); i++)
		Res += vec.at(i) * vec.at(i);
	return sqrt(Res);
}

double EnergyNorm(vector<double> vec, matrix_t A) {
	return sqrt(ScalarProduct(MatrixMulVector(A, vec), vec));
}

vector<double> Gradient(matrix_t A, vector<double> x, vector<double> b) {
	return VectorSubstract(MatrixMulVector(A, x), b);
}

double AlphaCoefficient(vector<double> g, matrix_t A) {
	return ScalarProduct(g, g) / ScalarProduct(MatrixMulVector(A, g), g);
}

vector<vector<double>> GradientMethod(matrix_t A, vector<double> b, double cond, double eps) {
	vector<vector<double>> Res;
	vector<double> new_x = RandomVector(b.size());
	Res.push_back(new_x);
	vector<double> old_x(b.size());
	vector<double> g(b.size());
	double alpha;
	double M = (cond - 1.0) / (cond + 1.0);
	int k = 1;
	do
	{
		k++;
		old_x = new_x;
		g = Gradient(A, old_x, b);
		alpha = AlphaCoefficient(g, A);
		new_x = VectorSubstract(old_x, VectorMulNumber(g, alpha));
		Res.push_back(new_x);
	} while (EnergyNorm(VectorSubstract(new_x, old_x), A) > (1.0 - M) * eps / M);
	printf("%i\n", k);
	return Res;
}

void OutputVector(vector<double> vec, ofstream* F) {
	F->precision(20);
	for (int i = 0; i < vec.size(); i++)
		*F << vec.at(i) << ";";
	*F << "\n";
	return;
}

// Lab2 functions
matrix_t Zero(int rang) {
	matrix_t zero;
	for (int i = 0; i < rang; i++)
	{
		zero.A.resize(i + 1);
		for (int j = 0; j < rang; j++)
		{
			zero.A.at(i).resize(j + 1);
			zero.A.at(i).at(j) = 0.0;
		}
	}
	return zero;
}


matrix_t CholFactorization(matrix_t matrix) {
	int m = 0, j = 0;
	matrix_t S = Zero(matrix.rang);
	S.rang = matrix.rang;
	for (m; m < matrix.rang; m++)
	{
		j = m;
		if (m == 0)
			S.A.at(m).at(j) = sqrt(matrix.A.at(m).at(j));
		else
		{
			S.A.at(m).at(j) = matrix.A.at(m).at(j);
			for (int k = 0; k < m; k++)
				S.A.at(m).at(j) = S.A.at(m).at(j) - S.A.at(m).at(k) * S.A.at(m).at(k);
			S.A.at(m).at(j) = sqrt(S.A.at(m).at(j));
		}
		for (j = m + 1; j < matrix.rang; j++)
		{
			if (m == 0)
				S.A.at(j).at(m) = matrix.A.at(m).at(j) / S.A.at(0).at(0);
			else
			{
				S.A.at(j).at(m) = matrix.A.at(m).at(j);
				for (int k = 0; k < m; k++)
					S.A.at(j).at(m) = S.A.at(j).at(m) - S.A.at(m).at(k) * S.A.at(j).at(k);
				S.A.at(j).at(m) /= S.A.at(m).at(m);
			}
		}
	}
	return S;
}

matrix_t Transpose(matrix_t matrix) {
	for (int i = 0; i < matrix.rang; i++)
		for (int j = i + 1; j < matrix.rang; j++)
		{
			double tmp = matrix.A.at(i).at(j);
			matrix.A.at(i).at(j) = matrix.A.at(j).at(i);
			matrix.A.at(j).at(i) = tmp;
		}
	return matrix;
}

vector<double> FindY(matrix_t matrix, vector<double> b) {
	vector<double> y;
	y.resize(matrix.rang);
	for (int i = 0; i < matrix.rang; i++)
	{
		y.at(i) = b.at(i);
		for (int k = 0; k < i; k++)
			y.at(i) -= matrix.A.at(i).at(k) * y.at(k);
		y.at(i) /= matrix.A.at(i).at(i);
	}
	return y;
}

vector<double> FindX(matrix_t matrix, vector<double> y) {
	vector<double> x;
	x.resize(matrix.rang);
	for (int i = matrix.rang - 1; i >= 0; i--)
	{
		x.at(i) = y.at(i);
		for (int k = i + 1; k < matrix.rang; k++)
			x.at(i) -= matrix.A.at(i).at(k) * x.at(k);
		x.at(i) /= matrix.A.at(i).at(i);
	}
	return x;
}