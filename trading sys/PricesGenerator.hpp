/*
 * PricersGenerator.hpp
 * generator "prices.txt"
 * 
 * @author: Ming Fu
 */
#pragma once

#ifndef	PRICERS_GENERATOR_HPP
#define PRICERS_GENERATOR_HPP

#include "BondInformation.hpp"
#include <fstream>
#include <random>
#include <vector>
#include <string>

using namespace std;

class PricesGenerator {
public:
	// ctor
	PricesGenerator();

	// overload ( operator 
	void operator()(int n);
};

PricesGenerator::PricesGenerator() {
}

void PricesGenerator::operator()(int n) {
	ofstream output;
	output.open("prices.txt");
	// output << "cusip" << "," << "price" << "," << "spread" << endl;

	// for each bond, we would generate n data
	// in total, 7*n lines are generated
	// Counter
	vector<int> counter={0,0,0,0,0,0,0};
	
	for (int i = 0; i < 7 * n; i++) {
		int j = rand() % 7;
		// if jth bond already has n data
		while (counter[j] == n){
			j = rand() % 7;
		}
		string cusip= bondCusip[j];
		counter[j]++;
	
		// price
		// integer part
		int a = rand() % 2 + 99;
		string A = to_string(a);
		// factional part
		int xy = rand() % 32;
		int z = rand() % 8;
		string XY = to_string(xy);
		string Z = to_string(z); 
		if (XY.size() < 2) XY = "0" + XY;
		if (z == 4) Z = "+";
		// fractional notation
		string price = A + "-" + XY + Z;
		
		// bid-ask spread
		int b = rand() % 4;
		string spread;
		if (b == 0)spread = "0-002";
		else if (b == 1)spread = "0-00+";
		else if (b == 2)spread = "0-006";
		else spread = "0-010";
		
		// output to file
		output << cusip << "," << price << "," << spread << endl;
	}
	output.close();
}

#endif
