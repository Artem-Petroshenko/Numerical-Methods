#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

double Complex_Func(double x);
double Polynom(double x);
double first_approximation(double a, double b);
double first_derivative(double x, double (*Func)(double));
double second_derivative(double x, double (*Func)(double));
vector<double> Fzero_half_division(double a, double b, double epsilon, double (*Func)(double));
vector<double> Fzero_mod_Newton(double a, double b, double epsilon, double (*Func)(double));
void Influence_of_first_approximation_n(double a, double b, double epsilon, double (*Func)(double), const char* filename);
void Influence_of_first_approximation_hd(double a, double b_start, double b_end, double epsilon, double (*Func)(double), const char* filename);
void Output(vector<double> vec, double epsilon, const char* filename);