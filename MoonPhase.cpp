#include "MoonPhase.h" 

/* Takes the year + year fraction of a new mooon and returns the Julian Day corresponding to that date
k: Julian day number of the lunation
T: Julian year fraction of the Julian day number
E: Eccentricity of the Earth's orbit
JDE: Ephemeris Julian Day
M: Mean anomaly of the Moon at tine JDE
MS: Mean anomaly of the Sun at time JDE
F: Moon's argument of latitude
Omega: Longitude of lunar orbit ascending node
*/


// Takes the value kYear, 
double fn_PhaseJDay(int k) {
    double T = k / JCentury_Lunations;
    double E = 1 - 0.002516 * T - 0.0000074 * pow(T, 2);
    double F = 160.7108 + 390.67050274 * k - 0.0016431 * pow(T, 2) - 0.000000227 * pow(T, 3) + 0.000000011 * pow(T, 4);
    double M = fn_Radians(fmod(201.5643 + 385.81693528 * k + 0.0107438 * pow(T, 2) + 0.00001239 * pow(T, 3) - 0.000000058 * pow(T, 4), 360.0));
    double MS = fn_Radians(fmod(2.5534 + 29.10535669 * k - 0.0000218 * pow(T, 2) - 0.00000011 * pow(T, 3), 360.0));
    double Omega = fn_Radians(fmod(124.7746 - 1.5637558 * k + 0.0020691 * pow(T, 2) + 0.00000215 * pow(T, 3), 360.0));
    double JDE = fn_JDE(k, T);
    return JDE + fn_PA(k, T) + fn_PT(E, F, M, MS, Omega) + fn_DeltaT(T);
};

double fn_PhaseJDE(double k, double T) {
    return Epoch_StartJD + Lunation_Days * k + 0.0001137 * pow(T, 2) - 0.00000015 * pow(T, 3) + 0.00000000073 * pow(T, 4);
};

double fn_PA(double k, double T) {
    double A1 = fn_Radians(fmod(299.77 + 0.107408 * k - 0.009173 * pow(T, 2), 360.0));
    double A2 = fn_Radians(fmod(251.88 + 0.01631 * k, 360.0));
    double A3 = fn_Radians(fmod(251.83 + 26.651886 * k, 360.0));
    double A4 = fn_Radians(fmod(349.42 + 36.412478 * k, 360.0));
    double A5 = fn_Radians(fmod(84.66 + 18.206239 * k, 360.0));
    double A6 = fn_Radians(fmod(141.74 + 503.303711 * k, 360.0));
    double A7 = fn_Radians(fmod(207.14 + 2.453732 * k, 360.0));
    double A8 = fn_Radians(fmod(154.84 + 7.30686 * k, 360.0));
    double A9 = fn_Radians(fmod(34.52 + 27.261239 * k, 360.0));
    double A10 = fn_Radians(fmod(207.19 + 0.121824 * k, 360.0));
    double A11 = fn_Radians(fmod(291.34 + 1.844379 * k, 360.0));
    double A12 = fn_Radians(fmod(161.72 + 1.844379 * k, 360.0));
    double A13 = fn_Radians(fmod(239.56 + 25.513099 * k, 360.0));
    double A14 = fn_Radians(fmod(331.55 + 3.592518 * k, 360.0));

    return 0.0000325 * sin(A1) + 0.0000165 * sin(A2) + 0.0000164 * sin(A3) + 0.0000126 * sin(A4) + 0.000011 * sin(A5) + 0.0000062 * sin(A6) + 0.000006 * sin(A7) + 0.0000056 * sin(A8)
        + 0.0000047 * sin(A9) + 0.000042 * sin(A10) + 0.00004 * sin(A11) + 0.000037 * sin(A12) + 0.000035 * sin(A13) + 0.000023 * sin(A14);           
};

double fn_PT(double E, double F, double M, double MS, double Omega) {
    return -0.4072 * sin(MS) + 0.17241 * E * sin(M) + 0.01608 * sin(2 * MS) + 0.01039 * sin(2 * F) + 0.00739 * E * sin(MS - M) - 0.00514 * E * sin(MS + M) + 0.00208 * pow(E, 2) * sin(2 * M)
        - 0.00111 * sin(MS - 2 * F) - 0.00057 * sin(MS + 2 * F) + 0.00056 * E * sin(2 * MS + M) - 0.00042 * sin(3 * MS) + 0.00042 * E * sin(M + 2 * F) + 0.00038 * E * sin(M - 2 * F)
        - 0.00024 * E * sin(2 * MS - M) - 0.00017 * sin(Omega) - 0.00007 * sin(MS + 2 * M) + 0.00004 * sin(2 * MS - 2 * F) + 0.00004 * sin(3 * M) + 0.00003 * sin(MS + M - 2 * F)
        + 0.00003 * sin(2 * MS + 2 * F) - 0.00003 * sin(MS + M + 2 * F) + 0.00003 * sin(MS - M + 2 * F) - 0.00002 * sin(MS - M - 2 * F) - 0.00002 * sin(3 * MS + M) + 0.00002 * sin(4 * MS);
};

double fn_DeltaT(double T) {
    return (102.3 + 123.5 * T + 32.5 * pow(T, 2)) / 86400;
};
