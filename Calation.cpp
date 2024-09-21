/*
* This program is intended to build a calendar based on the ancient Corinthian calenar from the Antikythera mechanism. I initially started working on it using Excel VBA,
* but I was dissatisifed with the precision it offered, so I decided to use C++, since I had some familiarity with the language. A month begins with the "new moon,"
* i.e., the day on which the first sliver of the moon is visible following an astronomical new moon. Currently, this is assumed to be the day following the date of the 
* astronomical new moon. Thus, the first step is to calculate the Julian date of the astronomical new moon. A year begins on the first day of the month during which the
* September equinox occurs, which occasionally involves inserting extra months. Todetermine this, it's necessary to calculate the Julian date of the equinox, and
* determine whether the last Julian date (the astronomical new moon) of every 13th month falls before or after the equinox. If it falls after the equinox, the following
* month will begin a new year. If it falls before the equinox, it will be necessary to insert an intercalary month between the fifth and six months. The program is
* currently designed to use the J0000 Epoch, but the algorithms should theoretically work for the proleptic Gregorian calendar. The algorithm is derived from that 
* provided by Jean Meuss in his Astronomical Algorithsm (1991), with corrections to certain coefficient values for precision.
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Calation.h"
// #include "csv2.hpp"

int main()
{
    //using namespace csv2;
    std::ofstream out("dates.csv");
    //Writer <delimiter<',' >> writer(out);
 
    /*  cout << "Lunation_Days = " << Lunation_Days << "\n";
    cout << "JLunar_Period = " << JLunar_Period << "\n";
    cout << "TLunar_Period = " << TLunar_Period << "\n";
    cout << "JYear_Lunations = " << JYear_Lunations << "\n";
    cout << "TYear_Lunations = " << TYear_Lunations << "\n";
    cout << "JCentury_Lunations = " << JCentury_Lunations << "\n\n"; */
    
    int Lunation = Start_Month;
    int Year = Start_Year;
 
    while (Lunation <= End_Month) {
        /*
            double T = Lunation / JCentury_Lunations;
            double A1 = fn_Radians(fmod(299.77 + 0.107408 * Lunation - 0.009173 * pow(T, 2), 360.0));
            double A2 = fn_Radians(fmod(251.88 + 0.01631 * Lunation, 360.0));
            double A3 = fn_Radians(fmod(251.83 + 26.651886 * Lunation, 360.0));
            double A4 = fn_Radians(fmod(349.42 + 36.412478 * Lunation, 360.0));
            double A5 = fn_Radians(fmod(84.66 + 18.206239 * Lunation, 360.0));
            double A6 = fn_Radians(fmod(141.74 + 503.303711 * Lunation, 360.0));
            double A7 = fn_Radians(fmod(207.14 + 2.453732 * Lunation, 360.0));
            double A8 = fn_Radians(fmod(154.84 + 7.30686 * Lunation, 360.0));
            double A9 = fn_Radians(fmod(34.52 + 27.261239 * Lunation, 360.0));
            double A10 = fn_Radians(fmod(2017.19 + 0.121824 * Lunation, 360.0));
            double A11 = fn_Radians(fmod(291.34 + 1.844379 * Lunation, 360.0));
            double A12 = fn_Radians(fmod(161.72 + 1.844379 * Lunation, 360.0));
            double A13 = fn_Radians(fmod(239.56 + 25.513099 * Lunation, 360.0));
            double A14 = fn_Radians(fmod(331.55 + 3.592518 * Lunation, 360.0));
            double E = 1 - 0.002516 * T - 0.0000074 * pow(T, 2);
            double F = fn_Radians(fmod(160.7108 + 390.67050274 * Lunation - 0.0016431 * pow(T, 2) - 0.000000227 * pow(T, 3) + 0.000000011 * pow(T, 4), 360.0));
            double M = fn_Radians(fmod(201.5643 + 385.81693528 * Lunation + (0.0107438 * pow(T, 2)) + (0.00001239 * pow(T, 3)) - (0.000000058 * pow(T, 4)), 360.0));
            double MS = fn_Radians(fmod(2.5534 + 29.10535669 * Lunation - 0.0000218 * pow(T, 2) - 0.00000011 * pow(T, 3), 360.0));
            double Omega = fn_Radians((124.7746 - (1.5637558 * Lunation) + (0.0020691 * pow(T, 2)) + (0.00000215 * pow(T, 3)), 360.0));
            double PA = 0.0000325 * sin(A1) + 0.0000165 * sin(A2) + 0.0000164 * sin(A3) + 0.0000126 * sin(A4) + 0.000011 * sin(A5) + 0.0000062 * sin(A6) + 0.000006 * sin(A7) + 0.0000056 * sin(A8)
                + 0.0000047 * sin(A9) + 0.000042 * sin(A10) + 0.00004 * sin(A11) + 0.000037 * sin(A12) + 0.000035 * sin(A13) + 0.000023 * sin(A14);
            double PT = -0.4072 * sin(MS) + 0.17241 * E * sin(M) + 0.01608 * sin(2 * MS) + 0.01039 * sin(2 * F) + 0.00739 * E * sin(MS - M) - 0.00514 * E * sin(MS + M) + 0.00208 * pow(E, 2) * sin(2 * M)
                - 0.00111 * sin(MS - 2 * F) - 0.00057 * sin(MS + 2 * F) + 0.00056 * E * sin(2 * MS + M) - 0.00042 * sin(3 * MS) + 0.00042 * E * sin(M + 2 * F) + 0.00038 * E * sin(M - 2 * F)
                - 0.00024 * E * sin(2 * MS - M) - 0.00017 * sin(Omega) - 0.00007 * sin(MS + 2 * M) + 0.00004 * sin(2 * MS - 2 * F) + 0.00004 * sin(3 * M) + 0.00003 * sin(MS + M - 2 * F) + 0.00003
                * sin(2 * MS + 2 * F) - 0.00003 * sin(MS + M + 2 * F) + 0.00003 * sin(MS - M + 2 * F) - 0.00002 * sin(MS - M - 2 * F) - 0.00002 * sin(3 * MS + M) + 0.00002 * sin(4 * MS);
            double JDE = Epoch_StartJD + Lunation_Days * Lunation + 0.0001137 * pow(T, 2) - 0.00000015 * pow(T, 3) + 0.00000000073 * pow(T, 4);
            double deltaT = (102.3 + 123.5 * T + 32.5 * pow(T, 2)) / 86400;
            double JD = JDE + PA + PT + deltaT;

            cout << "JDE = " << JDE << "\n";
            cout << "JD = " << JD << "\n\n";
            */

        /*
        double PhaseJDay = fn_PhaseJDay(Lunation);
        string JDayStr = std::to_string(PhaseJDay);

        std::vector<std::vector<std::string>> row = 
        {
            {JDayStr},
        };
        writer.write_row(row);
        */

        Lunation++;
        Year++;
    };
    
    out.close();
    return 0;
};


/********************************************************************************** Function Definitions *********************************************************************************/
/*********************************************************************************** Math Functions **************************************************************************************/
/************************************************************************************** fn_Radians ***************************************************************************************/
/* Input: Theta, a double-precision floating-point number representing the angle measurement in degrees.                                                                                 */
/* Output: A double-precision floating-point number rpresenting the angle measurement in radians.                                                                                        */
/*****************************************************************************************************************************************************************************************/

double fn_Radians(double Theta) {
    return Theta * (M_PI / 180);
};

/*****************************************************************************************************************************************************************************************/
/******************************************************************************* Moon Phase Calculations *********************************************************************************/
/************************************************************************************* fn_PhaseJDay **************************************************************************************/
/* Input: k, an integer rperesenting the Gregorian month (lunation) number.                                                                                                              */     
/* Output: A double-precision floating-point number rpresenting the Julian date of the new moon corresponding to k.                                                                      */    
/*****************************************************************************************************************************************************************************************/

double fn_PhaseJDay(int k) {
    double T = k / JCentury_Lunations;
    double E = 1 - 0.002516 * T - 0.0000074 * std::pow(T, 2);
    double F = 160.7108 + 390.67050274 * k - 0.0016431 * std::pow(T, 2) - 0.000000227 * std::pow(T, 3) + 0.000000011 * std::pow(T, 4);
    double M = fn_Radians(fmod(201.5643 + 385.81693528 * k + 0.0107438 * pow(T, 2) + 0.00001239 * pow(T, 3) - 0.000000058 * pow(T, 4), 360.0));
    double MS = fn_Radians(fmod(2.5534 + 29.10535669 * k - 0.0000218 * pow(T, 2) - 0.00000011 * pow(T, 3), 360.0));
    double Omega = fn_Radians(fmod(124.7746 - 1.5637558 * k + 0.0020691 * pow(T, 2) + 0.00000215 * pow(T, 3), 360.0));
    double JDE = fn_PhaseJDE(static_cast<double>(k), T);
    return JDE + fn_PA(static_cast<double>(k), T) + fn_PT(E, F, M, MS, Omega) + fn_DeltaT(T);
};

/************************************************************************************** fn_PhaseJDE **************************************************************************************/
/* Input: k, a double-precision floating-point number representing the Gregorian month (lunation) number.                                                                                */
/*        T, a double-precision floating-point number representing the time in Julian centuries since the beginning of the J2000 epoch represented by k.                                 */
/* Output: A double-precision floating-point number rpresenting the Julian ephemeris date of the lunation.                                                                               */
/*****************************************************************************************************************************************************************************************/


double fn_PhaseJDE(double k, double T) {
    return Epoch_StartJD + Lunation_Days * k + 0.0001137 * pow(T, 2) - 0.00000015 * pow(T, 3) + 0.00000000073 * pow(T, 4);
};

/***************************************************************************************** fn_PA *****************************************************************************************/
/* Input: k, a double-precision floating-point number representing the Gregorian month (lunation) number.                                                                                */
/*        T, a double-precision floating-point number representing the time in Julian centuries since the beginning of the J2000 epoch.                                                  */
/* Output: A double-precision floating-point number rpresenting the sum of the planetary arguments required to calculate the true Julian date of the lunation.                           */
/*****************************************************************************************************************************************************************************************/

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

/***************************************************************************************** fn_PT *****************************************************************************************/
/* Input: E, a double-precision floating-point number representing the eccentricity of the Earth's orbit around the sun.                                                                 */
/*        F, a double-precision floating-point number representing the Moon's argument of latitude.                                                                                      */
/*        M, a double-precision floating-point number representing the Sun's mean anomaly at time JDE.                                                                                   */
/*        MS, a double-precision floating-point number representing the Moon's mean anomaly.                                                                                             */
/*        Omega, a double-precision floating-point number representing the longitude of the ascending node of the Moon's orbit.                                                          */
/* Output: A double-precision floating-point number rpresenting the v sum of the periodic arguments required to calculate the true Julian date of the lunation.                          */
/*****************************************************************************************************************************************************************************************/

double fn_PT(double E, double F, double M, double MS, double Omega) {
    return -0.4072 * sin(MS) + 0.17241 * E * sin(M) + 0.01608 * sin(2 * MS) + 0.01039 * sin(2 * F) + 0.00739 * E * sin(MS - M) - 0.00514 * E * sin(MS + M) + 0.00208 * pow(E, 2) * sin(2 * M)
        - 0.00111 * sin(MS - 2 * F) - 0.00057 * sin(MS + 2 * F) + 0.00056 * E * sin(2 * MS + M) - 0.00042 * sin(3 * MS) + 0.00042 * E * sin(M + 2 * F) + 0.00038 * E * sin(M - 2 * F)
        - 0.00024 * E * sin(2 * MS - M) - 0.00017 * sin(Omega) - 0.00007 * sin(MS + 2 * M) + 0.00004 * sin(2 * MS - 2 * F) + 0.00004 * sin(3 * M) + 0.00003 * sin(MS + M - 2 * F)
        + 0.00003 * sin(2 * MS + 2 * F) - 0.00003 * sin(MS + M + 2 * F) + 0.00003 * sin(MS - M + 2 * F) - 0.00002 * sin(MS - M - 2 * F) - 0.00002 * sin(3 * MS + M) + 0.00002 * sin(4 * MS);
};

/*************************************************************************************** fn_DeltaT ***************************************************************************************/
/* Input: T, a double-precision floating-point number representing the time in Julian centuries since the beginning of the Julian epoch.                                                 */
/* Output: A double-precision floating-point number rpresenting the variance between Dynamic Terrestrial Time and Universal Time in seconds.                                                                                                  */
/*****************************************************************************************************************************************************************************************/

double fn_DeltaT(double T) {
    return (102.3 + 123.5 * T + 32.5 * std::pow(T, 2)) / 86400;
};

/************************************************************************************* fn_EquinoxJDE0 ************************************************************************************/
/* Input: y, an integer representing the year.                                                                                                                                           */
/* Output: A double-precision floating-point number rpresenting the Julian ephemeris date of the equinox.                                                                                */
/*****************************************************************************************************************************************************************************************/

double fn_EquinoxJDE0(int y) {
    return 2451810.227662 + 365242.07167 * y + 0.11575 * pow(y, 2) - 0.00337 * pow(y, 3) - 0.00078 * pow(y, 4);
};

/************************************************************************************* fn_EquinoxJDE0 ************************************************************************************/
/* Input: Year, an integer representing the year in which the equinox occurs.                                                                                                            */
/* Output: A double-precision floating-point number rpresenting the Julian date of the equinox.                                                                                          */
/*****************************************************************************************************************************************************************************************/

double fn_EquninoxJDE(int Year) {
    int y = (Year - 2000) / 1000;
    double JDE0 = fn_EquinoxJDE0(y);
    double T = (JDE0 - 2451545.0) / 36525.0;
    double W = fn_W(T);
    double DeltaLambda = fn_DeltaLambda(W);
    double S = fn_S(T, PT);

    return JDE0 + (0.00001 * S) / DeltaLambda;
};

/***************************************************************************************** fn_S ******************************************************************************************/
/* Input: T a double-precision floating-point number representing the time in Julian centuries since the beginning of the Julian epoch.                                                  */
/*        P, a pointer to a two-domensional array of double-precision floating-point numbers containing the coefficients of the periodic terms required for calculating the dates of the */
/*           September Equinox.                                                                                                                                                          */  
/* Output: A double-precision floating-point number representing the sums of the periodic terms in radians.                                                                                         */
/*****************************************************************************************************************************************************************************************/

double fn_S(double T, const double** PT) {
    double S = 0.0;

    for (int i = 0; i < 24; i++) {
        S += PT[i][0] * fn_Radians(fmod(PT[i][1] + PT[i][2] * T, 360.0));
    };

    return S;
};

/***************************************************************************************** fn_W ******************************************************************************************/
/* Input: T, a double-precision floating-point number representing the time in Julian centuries since the beginning of the Julian epoch.                                                 */
/* Output: A double-precision floating-point number representing the polar angular motion of the Earth at time T.                                                                        */                                                               */
/*****************************************************************************************************************************************************************************************/

double fn_W(double T) {
    
    return fn_Radians(fmod(35999.3713 * T - 2.47, 360.0));
};

/************************************************************************************* fn_DeltaLambda ************************************************************************************/
/* Input: W, a double-precision floating-point number representing the polar angular motion of the Earth.                                                                                */
/* Output: A double-precision floating-point number representing the variance between the celestial longitude of the moon from the celestial meridian.                                                                                           */
/*****************************************************************************************************************************************************************************************/

double fn_DeltaLambda(double W) {
    return 1 + 0.0334 * cos(W) + 0.00007 * cos(2 * W);
};




// Run program: Ctrl + F5 or Debug > Start_ Without Debugging menu
// Debug program: F5 or Debug > Start_ Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
