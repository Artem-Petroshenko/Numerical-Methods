#include "NM.h"

int main() {
	const char* file = "integral.csv";
	remove(file);
	ofstream F(file, ios_base::app);
	double a = -6, b = 6;
	double eps;
	F.precision(20);
	for (eps = 1e-1; eps >= 1e-13; eps /= 10) {
		F << Chebyshev(a, b, eps).first << ';' << Chebyshev(a, b, eps).second << '\n';
	}
	F.close();
	return 0;
}