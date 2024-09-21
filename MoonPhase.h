using namespace std;

#define _USE_MATH_DEFINES
#include <cmath>

/* Defining certain constants for use in equations:
TYear_Days: A double-precision floating-point number representing the legnth of the tropical year in solar days. Used for calculating year fractions for kYear.
Epoch_StartJD: A double-precision floating-point nubmer representing the Julian Date of the start of the epoch being considered. Used for calculating ephemerides.
	For test purposes, this is the new moon that occurred at 10:20:00 2000-8-29. 
Day_Minutes: A double-precision floating-point number representing the length of the day in minutes. Used for calculating Julian dates.
JDAY_Secs: A double-precision floating-point number representing the legnth of the day in seconds. Used for calculating Julian dates.
JYear_Days: A double-precision floating-point number representing the length of the Julian year in days. Used for calculating Julian dates and ephemerides.
TYear_Days: A double-precision floating-point number representing the length of the mean tropical year in days. Used for calculatingyear fractions for kYear.
Start_Year: A double-precision floating-point number representing the year number of the first new moon to be computed. For test purposes, this is set to 2000.
First_Lunation: A double-precision floating-point number representing the first lunation since the start of Epoch_StartJD (starting with 1) to calculate. 
Last_Lunation: A double-precision floating-point number representing the number of lunations since Epoch_StartJD to compute.
JLunar_Period = A double-precision floating-point number representing the fraction of a Julian year represented by one mean lunation. Used for calcuationg ephemerides.
TLunar_Period: A double-precision floating-point number representing the fraction of a mean tropical year represented by one mean lunation. Used for calculating year fractions for kYear.
Lunation_Days: A double-precision floating-point number representing the mean length of a lunation in 24-hour days. Always equal to 29.53058449074074.
JYear_Lunations: A double-precision floating-point number representing the mean number lunations per Julian year. Used for calculating ephemerides.
TYear_Lunations: A double-precision floating-point number representing the mean number lunations per mean tropical year. Used for calculation year fractions for kYear.
Century_Lunations: A double-precision floating-point number representing the number of lunations per 100 Julian years. Used for calculating ephemerides.
*/

// const double TYear_Days = 365.2425;
// const int Last_Month = 1374;
const double Epoch_StartJD = 2451550.250196759;
const double Day_Minutes = 1440.0;
const double Day_Secs = 86400.0;
const double JYear_Days = 365.25;
// const double TYear_Days = 365.2425;
const int Start_Month = 9;
const int End_Month = 1342;
const double Start_Year = 2000.0;
const double Lunation_Days = 29.5 + 44.0 / Day_Minutes + 2.9 / Day_Secs;
// const double JLunar_Period = Lunation_Days / JYear_Days;
// const double TLunar_Period = Lunation_Days / TYear_Days;
// const double JYear_Lunations = JYear_Days / Lunation_Days;
// const double TYear_Lunations = TYear_Days / Lunation_Days;
const double JCentury_Lunations = (JYear_Days / Lunation_Days) * 100.0;

// Function prototypes 
double fn_PhaseJDay(int);
double fn_PhaseJDE(double, double);
double fn_PA(double, double);
double fn_PT(double, double, double, double, double);
double fn_DeltaT(double);
double fn_Radians(double);