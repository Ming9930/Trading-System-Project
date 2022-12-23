/**
 * BondInformation.hpp
 * US treasuries with 7 securities: 2,3,5,7,10,20,30Y
 * CUSIP, coupons, maturity dates for each security
 * 
 * @author: Ming Fu
 */
#pragma once

#include <vector>
#include <string>

#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace boost::gregorian;


vector<string> bondCusip = { "912810ES3", // 2Years
"912810EW4", // 3Years
"912810FB9", // 5Years
"912810FM5", // 7Years
"912810FP8", // 10Years
"912810QY7", // 20Years
"912810TL2" }; // 30Years

vector<float> bondCoupon = { 0.07558, // 2Years
0.06119, // 3Years
0.06201, // 5Years
0.0634,  // 7Years
0.0546,  // 10Years
0.0282,  // 20Years
0.04 };  // 30Years

vector<date> bondMaturity = { date(2024,Nov,15), // 2Years
date(2026,Feb,15), // 3Years
date(2027,Nov,15), // 5Years
date(2030,May,15), // 7Years
date(2031,Feb,15), // 10Years
date(2042,Nov,15), // 20Years
date(2052,Nov,15) }; // 30Years

map<string, float> bondRisk = { {"912810ES3",0.075}, // 2Years
{"912810EW4",0.06}, // 3Years
{"912810FB9",0.06125}, // 5Years
{"912810FM5",0.0625}, // 7Years
{"912810FP8",0.05375}, // 10Years
{"912810QY7",0.0275}, // 20Years
{"912810TL2",0.4} }; // 30Years
