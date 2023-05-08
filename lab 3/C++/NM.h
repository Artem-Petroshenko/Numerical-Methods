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
matrix_t ImportMatrix(ifstream* F1, int rang);
vector<double> ImportRightPart(ifstream* F, int rang);
vector<double> VectorSubstract(vector<double> vec1, vector<double> vec2);
vector<double> MatrixMulVector(matrix_t matrix, vector<double> vec);
vector<double> VectorMulNumber(vector<double> vec, double num);
double ScalarProduct(vector<double> vec1, vector<double> vec2);
double EnergyNorm(vector<double> vec, matrix_t A);
double Norm(vector<double> vec);
vector<double> Gradient(matrix_t A, vector<double> x, vector<double> b);
double AlphaCoefficient(vector<double> g, matrix_t A);
vector<vector<double>> GradientMethod(matrix_t A, vector<double> b, double cond, double eps);
void OutputVector(vector<double> vec, ofstream* F);

matrix_t Zero(int rang);
matrix_t CholFactorization(matrix_t matrix);
matrix_t Transpose(matrix_t matrix);
vector<double> FindY(matrix_t matrix, vector<double> b);
vector<double> FindX(matrix_t matrix, vector<double> y);