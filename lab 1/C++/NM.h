#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

int GetNum(ifstream* F);
vector<double> ImportData(ifstream* F, int n);
double Lagrange(double x, vector<double> x_i, vector<double> y_i);
vector<double> Values(vector<double> xx, vector<double> x_i, vector<double> y_i);
double LagrangeUniformGrid(double x, vector<double> x_i, vector<double> y_i);
vector<double> ValuesUniformGrid(vector<double> xx, vector<double> x_i, vector<double> y_i);
void OutputVector(vector<double> vec, ofstream* F);