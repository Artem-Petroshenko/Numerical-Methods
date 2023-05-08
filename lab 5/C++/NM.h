#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

double f(double x, double y);
double y(double x);
double Calculate(double h, double x_j, double y_j);
void Error(double a, double f_a, double b, ofstream* F);
vector<double> Runge_Kutta(double a, double f_a, double b, int n);
double Pertubation(double a, double f_a, double df_a, double b, int n);