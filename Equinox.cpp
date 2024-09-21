#include "Calation.h"
#include "MoonPhase.hpp"

double fn_EquinoxJDE0(int y) {
	
	if (y == 0)
		return 245810.56767;
	else
		return 245810.56767 + 365242.07167 * y + 0.11575 * pow(y, 2) - 0.00337 * pow(y, 3) - 0.00078 * pow(y, 4);
};

double fn_W(double T) {
	return fn_Radians(fmod(35999.3713 * T - 2.47, 360));
};

double fn_DeltaLambda(double W) {
	return 1 + 0.0334 * cos(W) + 0.00007 * cos(2 * W);
};

double fn_S(double T, const double* A, const double* B, const double* C) {
	double S = 0.0;
	
	for (int i = 0; i < 12; i++) {
		S += A[i] * fn_Radians(fmod(B[i] + C[i] * T, 360));
	};
};

double fn_EquninoxJDE(int Year) {
	int y = (Year - 2000) / 1000;
	double JDE0 = fn_EquinoxJDE0(y);
	double T = (JDE0 - 2451545.0) / 36525;
	double W = fn_W(T);
	double DeltaLambda = fn_DeltaLambda(W);
	double S = fn_S(T, A, B, C);

	return JDE0 + (0.00001 * S) / DeltaLambda;
};
