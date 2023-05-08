#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>
#include <ctime>

using namespace std;

typedef struct{
	vector<vector<double>> A;
	int rang;
}matrix_t;

int GetNum(const char* filename);
matrix_t ImportMatrix(vector<double> str, int rang);
vector<double> ImportRightPart(vector<double> str, int rang);
matrix_t Zero(int rang);
matrix_t CholFactorization(matrix_t matrix);
matrix_t Transpose(matrix_t matrix);
vector<double> FindY(matrix_t matrix, vector<double> b);
vector<double> FindX(matrix_t matrix, vector<double> y);
void OutputVector(vector<double> vec, const char* filename);
void OutputMatrix(matrix_t matrix, const char* filename);