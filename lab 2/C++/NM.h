#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

typedef struct {
	int rang;
	vector<vector<double>> cell;
} matrix_t;

int GetNum(ifstream* F);
double fGetNum(ifstream* F);
vector<double> ImportData(ifstream* F, int n);
matrix_t MatrixInit(int size);
vector<double> ThomasAlgorythm(double h, vector<double> y_i, double a_der, double b_der);
pair<vector<double>, vector<double>> FindConstants(double h, vector<double> y_i, vector<double> M_i);
double g_i(double xx, double left_M, double right_M, double left_x, double right_x, double C, double C_tilda);
vector<double> CubicSpline(vector<double> xx, vector<double> x_i, vector<double> y_i, vector<double> M_i, pair<vector<double>, vector<double>> C);
void OutputVector(vector<double> vec, ofstream* F);