using namespace std;

#include <cmath>
#include <array>

/*********************************************************************************** Math Functions **************************************************************************************/

double fn_Radians(double);
/*****************************************************************************************************************************************************************************************/
/*************************************************************************************** Constants ***************************************************************************************/
/* These constants are defined for use in calculating  moon phases.																														 */
/* TYear_Days: A double-precision floating-point number representing the legnth of the tropical year in solar days.Used for calculating year fractions for kYear. Currently unused, but  */
/*		defined for future use.																																							 */
/* Epoch_StartJD: A double-precision floating-point nubmer representing the Julian Date of the start of the epoch being considered. Used for calculating ephemerides. Currently, this is */
/*		the new moon that occurred at 10:20:00 2000-8-29.																																 */	 																																	
/* Day_Minutes: A double-precision floating-point number representing the length of the day in minutes. Used for calculating Julian dates.												 */
/* JDay_Secs: A double-precision floating-point number representing the legnth of the day in seconds. Used for calculating Julian dates.												 */													
/* JYear_Days: A double-precision floating-point number representing the length of the Julian year in days.Used for calculating Julian dates and ephemerides.							 */
/* TYear_Days: A double-precision floating-point number representing the length of the mean tropical year in days. Used for calculatingyear fractions for kYear.						 */
/* JEpoch_Start: A double-precision floating-point number rpresenting the Julian day number with which the current epoch commenced. Used for calculating ephemerides.					 */
/*		For test purposes, this is set to 12:00:00 2000-1-1, rpresenting the J2000 epoch.																								 */		
/* Start_Year: A double-precision floating-point number representing the year number of the first equinox to be computed. Currently, this is AD 2000.									 */
/* First_Lunation: n integer representing the first month since the start of Epoch_StartJD (starting with 1) to calculate. Currently, this is 9, for September.							 */
/* End_Month: An integer representing the number of months since Epoch_StartJD to compute to. Currently set to 1374.																	 */
/* JLunar_Period = A double-precision floating-point number representing the fraction of a Julian year represented by one mean lunation. Currently unused.								 */
/* TLunar_Period: A double-precision floating-point number representing the fraction of a mean tropical year represented by one mean lunation. Currently unused.						 */
/* Lunation_Days: A double-precision floating-point number representing the mean length of a lunation in 24-hour days. Always equal to 29.53058449074074.								 */		
/* JYear_Lunations: A double-precision floating-point number representing the mean number lunations per Julian year. Currently unused.													 */
/* TYear_Lunations: A double-precision floating-point number representing the mean number lunations per mean tropical year. Currently unused.											 */
/* Century_Lunations: A double-precision floating-point number representing the number of lunations per 100 Julian years. Used for calculating ephemerides.								 */
/*****************************************************************************************************************************************************************************************/

// const double TYear_Days = 365.2425;
const double Epoch_StartJD = 2451550.250196759;
const double Day_Minutes = 1440.0;
const double Day_Secs = 86400.0;
const double JYear_Days = 365.25;
const double TYear_Days = 365.2425;
const int Start_Month = 9;
const int End_Month = 1374;
const int Start_Year = 2000;
const double Lunation_Days = 29.5 + 44.0 / Day_Minutes + 2.9 / Day_Secs;
// const double JLunar_Period = Lunation_Days / JYear_Days;
// const double TLunar_Period = Lunation_Days / TYear_Days;
const double JYear_Lunations = JYear_Days / Lunation_Days;
// const double TYear_Lunations = TYear_Days / Lunation_Days;
const double JCentury_Lunations = JYear_Lunations * 100.0;

/******************************************************************************** Moon Phase Calculations ********************************************************************************/
/********************************************************************************** Function Prototypes **********************************************************************************/
double fn_EquinoxJDE0(int);
double fn_EquinoxJDE(int);
double fn_DeltaLambda(double);
double fn_S(double, const double[24][3]);
double fn_W(double);
/*****************************************************************************************************************************************************************************************/

/********************************************************************************** Equinox Calculations *********************************************************************************/
/*************************************************************************************** Constants ***************************************************************************************/
/* The arrays below contain coefficients for the periodic terms required for calculating the dates of the September Equinox.																				 */
/*****************************************************************************************************************************************************************************************/

const double PT[24][3]{
	{ 485.0, 324.96, 1934.136 },
	{ 203.0, 337.23, 32694.17 },
	{ 199.0, 324.0, 20.186 },
	{ 182.0, 27.85, 445267.112 },
	{ 156.0, 73.14, 435036.886 },
	{ 136.0, 171.52, 22158.443 },
	{ 77.0, 222.54, 65928.934 },
	{ 74.0, 296.72, 3034.906 },
	{ 70.0, 243.58, 9037.513 },
	{ 58.0, 119.81, 33718.147 },
	{ 52.0, 297.17, 150.678},
	{ 50.0, 21.02, 2281.226},
	{ 45.0, 247.54, 29929.562 },
	{ 44.0, 325.15, 31555.956 },
	{ 29.0, 60.93, 41443.417 },
	{ 18.0, 155.12, 67555.328 },
	{ 17.0, 288.79, 4562.452 },
	{ 16.0, 198.04, 62984.029 },
	{ 14.0, 199.76, 31346.921 },
	{ 12.0, 95.39, 14577.848 },
	{ 12.0, 287.11, 31931.756 },
	{ 12.0, 320.81, 34777.259 },
	{ 9.0, 277.73, 1222.114 },
	{ 8.0, 15.45, 16859.074 }
};
/*****************************************************************************************************************************************************************************************/
/********************************************************************************** Function Prototypes **********************************************************************************/
double fn_EquinoxJDE0(int);
double fn_S(double, const double**);
double fn_W(double);
double fn_DeltaLambda(double);
double fn_EquninoxJDE(int);