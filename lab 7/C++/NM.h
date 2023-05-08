#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

double p(double x);
double q(double x);
double r(double x);
double f(double x);
vector<vector<double>> CreateMatrix(double a, double b, int n, double alpha0, double alpha1, double beta0, double beta1, double A, double B);
vector<double> ThomasAlgorithm(vector<double> w0, vector<double> w1, vector<double> w2, vector<double> F);