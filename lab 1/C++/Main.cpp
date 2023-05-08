#include "NM.h"

int main(void) {
	const char* datapoints = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab1\\datapoints.csv";
	const char* datapoints2 = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab1\\abs_func_datapoints.csv";
	const char* filexx = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab1\\xx.csv";
	const char* nodes = "C:\\Users\\user\\Documents\\MATLAB\\sem4\\lab1\\nodes.csv";
	const char* fileoutput = "yy.csv";
	const char* fileoutput2 = "abs_yy.csv";
	const char* fileoutput3 = "yy_uniform.csv";
	remove(fileoutput);
	remove(fileoutput2);
	remove(fileoutput3);
	ifstream F1(datapoints);
	ifstream F2(datapoints2);
	ifstream F3(filexx);
	ifstream F4(nodes);
	ofstream F5(fileoutput, ios_base::app);
	ofstream F6(fileoutput2, ios_base::app);
	ofstream F7(fileoutput3, ios_base::app);
	int k = GetNum(&F4);
	F4.close();
	vector<double> xx = ImportData(&F3, 1000);
	F3.close();
	for (int i = 0; i < k; i++) {
		int n = GetNum(&F1);
		vector<double> x_i = ImportData(&F1, n);
		vector<double> y_i = ImportData(&F1, n);
		vector<double> abs_y_i = ImportData(&F2, n);
		vector<double> yy = Values(xx, x_i, y_i);
		vector<double> abs_yy = Values(xx, x_i, abs_y_i);
		vector<double> yy_uniform = ValuesUniformGrid(xx, x_i, y_i);
		OutputVector(yy, &F5);
		OutputVector(abs_yy, &F6);
		OutputVector(yy_uniform, &F7);
	}
	F1.close();
	F2.close();
	F5.close();
	F6.close();
	F7.close();
}