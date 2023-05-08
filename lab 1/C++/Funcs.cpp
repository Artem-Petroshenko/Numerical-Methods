#include "NM.h"

double Complex_Func(double x) {
	return pow(5, x) + 3 * x;
}

double Polynom(double x) {
	return pow(x, 5) + pow(x, 2) - 5;
}

double first_derivative(double x, double (*Func)(double)) {
	const double h = 1e-10;
	return (Func(x + h) - Func(x - h)) / (2.0 * h);
}

double second_derivative(double x, double (*Func)(double)) {
	const double h = 1e-10;
	return (Func(x + h) - 2. * Func(x) + Func(x - h)) / (h * h);
}

double first_approximation(double a, double b) {
	srand(1000 * time(NULL));
	return ((double)rand() / (RAND_MAX + 1.0)) * (b - a) + a;
}

vector<double> Fzero_half_division(double a, double b, double epsilon, double (*Func)(double)) {
	vector<double> X;
	int i = 0;
	double c;
	while (abs(b - a) > 2 * epsilon)
	{
		c = (a + b) / 2;
		X.resize(i + 1);
		X.at(i) = c;
		i++;
		if (Func(a) * Func(c) < 0)
			b = c;
		else
			a = c;
	}
	X.resize(i + 1);
	X.at(i) = (a + b) / 2;
	return X;
}

vector<double> Fzero_mod_Newton(double a, double b, double epsilon, double (*Func)(double)) {
	vector<double> X;
	double x0 = first_approximation(a, b);
	double new_x, prev_x;
	double der = first_derivative(x0, Func);
	prev_x = x0;
	new_x = x0 - (Func(x0) / der);
	X = { x0, new_x };
	int i = 2;
	while (Func(new_x - epsilon) * Func(new_x + epsilon) > 0)  // универсальное условие остановки цикла
	{
		if (i % 2 == 0)
			der = first_derivative(new_x, Func);
		prev_x = new_x;
		new_x = prev_x - (Func(prev_x) / der);
		X.resize(i + 1);
		X.at(i) = new_x;
		i++;
	}
	return X;
}

void Influence_of_first_approximation_n(double a, double b, double epsilon, double (*Func)(double), const char* filename) {
	ofstream F(filename, ios_base::app);
	for (double i = a; i < b + 0.05; i += 0.05)
	{
		vector<double> X;
		double x0 = i;
		double new_x, prev_x;
		double der = first_derivative(x0, Func);
		prev_x = x0;
		new_x = x0 - (Func(x0) / der);
		X = { x0, new_x };
		int k = 2;
		while (Func(new_x - epsilon) * Func(new_x + epsilon) > 0)  // универсальное условие остановки цикла
		{
			if (k % 2 == 0)
				der = first_derivative(new_x, Func);
			prev_x = new_x;
			new_x = prev_x - (Func(prev_x) / der);
			X.resize(k + 1);
			X.at(k) = new_x;
			k++;
		}
		F << i << ';' << X.size() << ';' << endl;
	}
	F.close();
	return;
}

void Influence_of_first_approximation_hd(double a, double b_start, double b_end, double epsilon, double (*Func)(double), const char* filename) {
	ofstream F(filename, ios_base::app);
	vector<double> X;
	int i = 0;
	double c;
	for (double k = b_start; k <= b_end; k += 1)
	{
		i = 0;
		X.resize(i);
		double b = k;
		while (abs(b - a) > 2 * epsilon)
		{
			c = (a + b) / 2;
			X.resize(i + 1);
			X.at(i) = c;
			i++;
			if (Func(a) * Func(c) < 0)
				b = c;
			else
				a = c;
		}
		X.resize(i + 1);
		X.at(i) = (a + b) / 2;
		F << k << ';' << X.size() << ';' << endl;
	}
	F.close();
	return;
}

void Output(vector<double> vec, double epsilon, const char* filename) {
	ofstream F(filename, ios_base::app);
	F << epsilon << ';';
	F << vec.size() << ';';
	F.precision(16);
	F << vec.at(vec.size() - 1) << ';';
	for (int i = 0; i < vec.size(); i++)
	{
		F << vec.at(i) << ';';
	}
	F << endl;
	F.close();
}