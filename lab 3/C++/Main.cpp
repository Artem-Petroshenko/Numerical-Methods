#include "NM.h"

int main() {
	remove("root.csv");
	remove("iterations.csv");
	double eps = 1e-10;
	const char* filename1 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\matrix.csv";
	const char* filename2 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\rightpart.csv";
	const char* filename3 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\rang.csv";
	const char* filename4 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\num_of_matrix.csv";
	const char* filename5 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\cond.csv";
	const char* filename6 = "root.csv";
	const char* filename7 = "iterations.csv";
	ifstream F1(filename1);
	ifstream F2(filename2);
	ifstream F3(filename3);
	ifstream F4(filename4);
	ifstream F5(filename5);
	int num_of_matrix = GetNum(&F4);
	int rang = GetNum(&F3);
	double cond;
	matrix_t A;
	vector<double> b;
	vector<vector<double>> root;
	F3.close();
	F4.close();
	for (int i = 0; i < num_of_matrix; i++)
	{
		cond = (double)GetNum(&F5);
		A = ImportMatrix(&F1, rang);
		b = ImportRightPart(&F2, rang);
		root = GradientMethod(A, b, cond, eps);
		ofstream F6(filename6, ios_base::app);
		for (int i = 0; i < root.size(); i++)
			OutputVector(root.at(i), &F6);
		F6.close();
		ofstream F7(filename7, ios_base::app);
		F7 << root.size() << ";";
		F7.close();
	}
	F1.close();
	F2.close();
	F5.close();
	//Part 2
	/*remove("CholTime.csv");
	remove("GradientTime.csv");*/
	const char* filename1_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\matrix2.csv";
	const char* filename2_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\rightpart2.csv";
	const char* filename3_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\rang2.csv";
	const char* filename4_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\accur_roots.csv";
	const char* filename5_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab3\\num_of_matrix2.csv";
	const char* fileout1 = "CholTime.csv";
	const char* fileout2 = "GradientTime.csv";
	ifstream F1_2(filename1_2);
	ifstream F2_2(filename2_2);
	ifstream F3_2(filename3_2);
	ifstream F4_2(filename4_2);
	ifstream F5_2(filename5_2);
	cond = 10;
	double error;
	num_of_matrix = GetNum(&F5_2);
	vector<double> rootCH;
	vector<vector<double>> rootG;
	vector<double> accur_root;
	clock_t CholT;
	clock_t GradT;
	for (int i = 0; i < num_of_matrix; i++)
	{
		rang = GetNum(&F3_2);
		A = ImportMatrix(&F1_2, rang);
		b = ImportRightPart(&F2_2, rang);
		accur_root = ImportRightPart(&F4_2, rang);
		CholT = clock();
		matrix_t S = CholFactorization(A);
		rootCH = FindX(Transpose(S), FindY(S, b));
		CholT = (double)clock() - CholT;
		error = Norm(VectorSubstract(accur_root, rootCH));
		printf("error is %.20lf\n", error);
		printf("Chol time is %lf\n", (double)CholT / CLOCKS_PER_SEC);
		GradT = clock();
		rootG = GradientMethod(A, b, cond, error * 10); //trouble with epsilon, for double type it is about 1e-16 exactly like error
		GradT = clock() - GradT;
		printf("Gradient time is %lf\n", (double)GradT / CLOCKS_PER_SEC);
		ofstream F6_2(fileout1, ios_base::app);
		ofstream F7_2(fileout2, ios_base::app);
		F6_2 << (double)CholT / CLOCKS_PER_SEC << ";";
		F7_2 << (double)GradT / CLOCKS_PER_SEC << ";";
		F6_2.close();
		F7_2.close();
	}
	F1_2.close();
	F2_2.close();
	F3_2.close();
	F4_2.close();
	F5_2.close();
}