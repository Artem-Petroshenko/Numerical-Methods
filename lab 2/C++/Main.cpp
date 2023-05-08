#include "NM.h"

int main() {
	remove("root.csv");
	//Files for part 1
	const char* filename1 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\matrix.csv";
	const char* filename2 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\rightpart.csv";
	const char* filename3 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\rang.csv";
	const char* filename4 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\num_of_matrix.csv";
	const char* filename5 = "root.csv";
	//Part 1
	ifstream F1(filename1, ios_base::in);
	ifstream F2(filename2, ios_base::in);
	int num_of_matrix = GetNum(filename4);
	int rang = GetNum(filename3);
	//temporary variables for matrix and right part for SLAE
	vector<double> tmp(rang * rang);
	vector<double> rp(rang);
	//Matrix
	vector<matrix_t> M;
	//Chol matrix
	vector<matrix_t> S;
	vector<vector<double>> b;
	vector<vector<double>> root;
	for (int i = 0; i < num_of_matrix; i++)
	{
		for (int j = 0; j < rang * rang; j++)
			F1 >> tmp.at(j);
		for (int j = 0; j < rang; j++)
			F2 >> rp.at(j);
		M.resize(i + 1);
		M.at(i) = ImportMatrix(tmp, rang);
		S.resize(i + 1);
		S.at(i) = CholFactorization(M.at(i));
		b.resize(i + 1);
		b.at(i) = ImportRightPart(rp, rang);
		root.resize(i + 1);
		root.at(i) = FindX(Transpose(S.at(i)), FindY(S.at(i), b.at(i)));
	}
	F1.close();
	F2.close();
	for (int i = 0; i < num_of_matrix; i++)
	{
		OutputVector(root.at(i), filename5);
	}
	//Files for part 2
	remove("root2.csv");
	const char* filename_part2_1 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\matrix2.csv";
	const char* filename_part2_2 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\rightpart2.csv";
	const char* filename_part2_3 = "root2.csv";
	//Part 2
	ifstream F1_2(filename_part2_1, ios_base::in);
	ifstream F2_2(filename_part2_2, ios_base::in);
	num_of_matrix = 2;
	int num_of_delta = 10;
	for (int i = 0; i < num_of_matrix; i++)
	{
		for (int j = 0; j < rang * rang; j++)
			F1_2 >> tmp.at(j);
		M.resize(i + 1);
		M.at(i) = ImportMatrix(tmp, rang);
		for (int k = 0; k < num_of_delta; k++)
		{
			for (int j = 0; j < rang; j++)
				F2_2 >> rp.at(j);
			S.resize(i * num_of_delta + k + 1);
			S.at(i * num_of_delta + k) = CholFactorization(M.at(i));
			b.resize(i * num_of_delta + k + 1);
			b.at(i * num_of_delta + k) = ImportRightPart(rp, rang);
			root.resize(i * num_of_delta + k + 1);
			root.at(i * num_of_delta + k) = FindX(Transpose(S.at(i * num_of_delta + k)), FindY(S.at(i * num_of_delta + k), b.at(i * num_of_delta + k)));
		}
	}
	F1_2.close();
	F2_2.close();
	for (int i = 0; i < num_of_matrix * num_of_delta; i++)
		OutputVector(root.at(i), filename_part2_3);
	//Part 3
	remove("time.csv");
	clock_t timer;
	filename1 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\matrix3.csv";
	filename2 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\rightpart3.csv";
	filename3 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\rang3.csv";
	filename4 = "C:\\Users\\user\\Documents\\MATLAB\\lab2\\matrixnum3.csv";
	filename5 = "time.csv";
	ifstream F1_3(filename1, ios_base::in);
	ifstream F2_3(filename2, ios_base::in);
	ifstream F3_3(filename3, ios_base::in);
	ifstream F4_3(filename4, ios_base::in);
	ofstream F5_3(filename5, ios_base::app);
	//F5_3.precision(20);
	F4_3 >> num_of_matrix;
	for (int i = 0; i < num_of_matrix; i++)
	{
		F3_3 >> rang;
		tmp.resize(rang * rang);
		rp.resize(rang);
		for (int j = 0; j < rang * rang; j++)
			F1_3 >> tmp.at(j);
		for (int j = 0; j < rang; j++)
			F2_3 >> rp.at(j);
		timer = clock();
		M.resize(i + 1);
		M.at(i) = ImportMatrix(tmp, rang);
		S.resize(i + 1);
		S.at(i) = CholFactorization(M.at(i));
		b.resize(i + 1);
		b.at(i) = ImportRightPart(rp, rang);
		root.resize(i + 1);
		root.at(i) = FindX(Transpose(S.at(i)), FindY(S.at(i), b.at(i)));
		timer = clock() - timer;
		F5_3 << (double)timer / CLOCKS_PER_SEC << ";";
	}
	return 1;
}
