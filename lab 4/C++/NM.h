#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

double f(double x);
vector<double> Nodes(double a, double b);
double Integrate(double a, double h, int n);
pair<double, int> Chebyshev(double a, double b, double eps);