#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

double f(double x);
double Integrate(double h, double a, int n);
pair<double, int> Newton_Cotes(double a, double b, double eps);