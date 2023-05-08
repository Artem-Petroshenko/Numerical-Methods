#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>
#include <ctime>

using namespace std;

typedef struct {
	vector<vector<double>> A;
	int rang;
}matrix_t;

int GetNum(ifstream* F);
double fGetNum(ifstream* F);
matrix_t ImportMatrix(ifstream* F1, int rang);
vector<double> VectorSubstract(vector<double> vec1, vector<double> vec2);
vector<double> MatrixMulVector(matrix_t matrix, vector<double> vec);
vector<double> VectorMulNumber(vector<double> vec, double num);
double Norm(vector<double> vec);
vector<double> RandomVector(int size);
double MaxComponent(vector<double> vec);
vector<double> PowerMethod(matrix_t A, double eps);
matrix_t Shift(matrix_t A, double mu);
vector<double> ShiftPowerMethod(matrix_t A, double mu, double eps);

void OutputVector(vector<double> vec, ofstream* F);