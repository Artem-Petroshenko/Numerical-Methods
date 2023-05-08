#include "NM.h"

int main() {
	const char* filename1 = "Polynom_half_division.csv";
	const char* filename2 = "Complex_Func_half_division.csv";
	const char* filename3 = "Polynom_Newton_method.csv";
	const char* filename4 = "Complex_Func_Newton_method.csv";
	const char* filenamep = "Influence_of_first_approximation_Polynom.csv";
	const char* filenamec = "Influence_of_first_approximation_Complex_Func.csv";
	const char* filenamep1 = "Influence_of_first_approximation_Polynom_hd.csv";
	const char* filenamec1 = "Influence_of_first_approximation_Complex_Func_hd.csv";
	vector<double> epsilon = { 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10, 1e-11, 1e-12, 1e-13, 1e-14, 1e-15 };
	double a_polynom_hd = 1.0, b_polynom_hd = 2.0;										
	double a_polynom_n = 1.5, b_polynom_n = 2.0;		
	double a_complex_func_hd = -1.0, b_complex_func_hd = 1.0;
	double a_complex_func_n = 0.0, b_complex_func_n = 1.0;
	/*for (int i = epsilon.size() - 1; i >= 0; i--)
	{
		Output(Fzero_half_division(a_polynom_hd, b_polynom_hd, epsilon.at(i), Polynom), epsilon.at(i), filename1);
		Output(Fzero_half_division(a_complex_func_hd, b_complex_func_hd, epsilon.at(i), Complex_Func), epsilon.at(i), filename2);
		Output(Fzero_mod_Newton(a_polynom_n, b_polynom_n, epsilon.at(i), Polynom), epsilon.at(i), filename3);
		Output(Fzero_mod_Newton(a_complex_func_n, b_complex_func_n, epsilon.at(i), Complex_Func), epsilon.at(i), filename4);
	}
	Influence_of_first_approximation_n(a_polynom_n, b_polynom_n * 30, 1e-15, Polynom, filenamep);
	Influence_of_first_approximation_n(a_complex_func_n, b_complex_func_n * 50, 1e-15, Complex_Func, filenamec);*/
	Influence_of_first_approximation_hd(a_polynom_hd, b_polynom_hd, b_polynom_hd * 30, 1e-15, Polynom, filenamep1);
	Influence_of_first_approximation_hd(a_complex_func_hd, b_complex_func_hd, b_complex_func_hd * 50, 1e-15, Complex_Func, filenamec1);
}