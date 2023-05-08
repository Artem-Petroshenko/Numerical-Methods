#include "NM.h"

int GetNum(const char* filename) {
	int num;
	ifstream F(filename, ios_base::in);
	F >> num;
	F.close();
	return num;
}

matrix_t ImportMatrix(vector<double> str, int rang) {
	matrix_t matrix;
	matrix.rang = rang;
	for (int i = 0; i < rang; i++)
	{
		matrix.A.resize(i + 1);
		for (int j = 0; j < rang; j++)
		{
			matrix.A.at(i).resize(j + 1);
			matrix.A.at(i).at(j) = str.at(i * rang + j);
		}
	}
	return matrix;
}

vector<double> ImportRightPart(vector<double> str, int rang) {
	vector<double> b;
	for (int i = 0; i < rang; i++)
	{
		b.resize(i + 1);
		b.at(i) = str.at(i);
	}
	return b;
}

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

void OutputVector(vector<double> vec, const char* filename) {
	ofstream F(filename, ios_base::app);
	F.precision(20);
	for (int i = 0; i < vec.size(); i++)
		F << vec.at(i) << ';';
	F << endl;
	F.close();
	return;
}

void OutputMatrix(matrix_t matrix, const char* filename) {
	ofstream F(filename, ios_base::app);
	F.precision(20);
	for (int i = 0; i < matrix.rang; i++)
	{
		for (int j = 0; j < matrix.rang; j++)
			F << matrix.A.at(i).at(j) << ';';
	}
	F << endl;
	F.close();
	return;
}