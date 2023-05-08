#include "NM.h"

int main(void) {
	const char* fileinput1 = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\matrix.csv";
	const char* fileinput2 = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\rang.csv";
	const char* fileoutput = "eigenvector_+_value.csv";
	remove(fileoutput);
	ifstream F1(fileinput1);
	ifstream F2(fileinput2);
	int rang = GetNum(&F2);
	matrix_t A = ImportMatrix(&F1, rang);
	F1.close();
	F2.close();
	double eps = 1e-13;
	const char* firsteig = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\firsteig.csv";
	const char* lasteig = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\lasteig.csv";
	ifstream Feig(firsteig);
	ifstream Leig(lasteig);
	double first = fGetNum(&Feig);
	double last = fGetNum(&Leig);
	Feig.close();
	Leig.close();
	vector<double> eigenvector_value;
	double delta = (first - last) / 2 / 1000;
	for (double i = last; i <= (first + last) / 2 - 100 * delta; i += delta) {
		eigenvector_value = ShiftPowerMethod(A, i, eps);
		ofstream F(fileoutput, ios_base::app);
		OutputVector(eigenvector_value, &F);
		F.close();
	}

	//Part 1
	const char* fileinput1_1 = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\matrix1.csv";
	const char* fileinput2_1 = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\rang1.csv";
	const char* fileinput3_1 = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\shift1.csv";
	const char* fileoutput_1 = "eigenvector_+_value1.csv";
	remove(fileoutput_1);
	int num_of_matrix = 2;
	double shift;
	ifstream F1_1(fileinput1_1);
	ifstream F2_1(fileinput2_1);
	rang = fGetNum(&F2_1);
	F2_1.close();
	ifstream F3_1(fileinput3_1);
	for (int i = 0; i < num_of_matrix; i++) {
		shift = fGetNum(&F3_1);
		A = ImportMatrix(&F1_1, rang);
		for (eps = 1e-5; eps > 1e-15; eps /= 10.0) {
			eigenvector_value = ShiftPowerMethod(A, shift, eps);
			ofstream F_1(fileoutput_1, ios_base::app);
			OutputVector(eigenvector_value, &F_1);
			F_1.close();
		}
	}
	F1_1.close();
	F3_1.close();

	//Part 2
	const char* fileinput1_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\disturb_matrix2.csv";
	const char* fileinput2_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\rang2.csv";
	const char* fileinput3_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab4\\shift2.csv";
	const char* fileoutput_2 = "eigenvector_+_value2.csv";
	remove(fileoutput_2);
	num_of_matrix = 10;
	int num_of_shift = 2;
	eps = 1e-10;
	ifstream F1_2(fileinput1_2);
	ifstream F2_2(fileinput2_2);
	rang = fGetNum(&F2_2);
	F2_2.close();
	ifstream F3_2(fileinput3_2);
	for (int k = 0; k < num_of_shift; k++) {
		shift = fGetNum(&F3_2);
		for (int i = 0; i < num_of_matrix; i++) {
			A = ImportMatrix(&F1_2, rang);
			eigenvector_value = ShiftPowerMethod(A, shift, eps);
			ofstream F_2(fileoutput_2, ios_base::app);
			OutputVector(eigenvector_value, &F_2);
			F_2.close();
		}
	}
	//random matrix
	for (int k = 0; k < num_of_shift; k++) {
		shift = fGetNum(&F3_2);
		for (int i = 0; i < num_of_matrix; i++) {
			A = ImportMatrix(&F1_2, rang);
			eigenvector_value = ShiftPowerMethod(A, shift, eps);
			ofstream F_2(fileoutput_2, ios_base::app);
			OutputVector(eigenvector_value, &F_2);
			F_2.close();
		}
	}
	F1_2.close();
	F3_2.close();
	return 0;
}