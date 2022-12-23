/*
 * MarketdataGenerator.hpp
 * generator marketdata.txt
 * 
 * @author: Ming Fu
 */
#pragma once

#ifndef MARKET_DATA_GENERATOR_HPP
#define MARKET_DATA_GENERATOR_HPP

#include "BondInformation.hpp"
#include <fstream>
#include <random>
#include <vector>
#include <string>

using namespace std;

class MarketdataGenerator {
public:
	// ctor
	MarketdataGenerator();

	// overload ( operator
	void operator()(int n);
};

MarketdataGenerator::MarketdataGenerator() {
}

void MarketdataGenerator::operator()(int n) {
	ofstream output;
	output.open("marketdata.txt");
	
	// for each bond, we would generate n data
	// in total, 7*n lines are generated
	// Counter
	vector<int> counter = { 0,0,0,0,0,0,0 };
	
	for (int i = 0; i < 7 * n; i++) {
		int j = rand() % 7;
		// if jth bond already has n data
		while(counter[j]==n){
			j = rand() % 7;
		}
		string cusip=bondCusip[j];
		counter[j]++;
		
		// each security with 5 orders deep on both bid and offer stacks
		// generate mid prices
		output << cusip << ",";
		// spread of top level = 2, 4, 6, 8
		// half spread of top level = 1, 2, 3, 4
		int hs = 1;
		for (int k = 0; k < 5; ++k) {
			// midprice
			// integer part
			int a = rand() % 2 + 99;			
			// factional part
			int xy = rand() % 32;
			int z = rand() % 8;

			// bidprice
			int bida = a;
			int bidxy = xy;
			int bidz = z - hs;
			if (bidz > 7) {
				bidz -= 8;
				bidxy += 1;
			}
			if (bidxy > 31) {
				bidxy -= 32;
				bida += 1;
			}
			string A = to_string(bida);
			string XY = to_string(bidxy);
			string Z = to_string(bidz);
			if (XY.size() < 2) XY = "0" + XY;
			if (z == 4) Z = "+";
			string bidprice = A + "-" + XY + Z;
			string quantity = to_string((k % 5 + 1) * 1000000);
			string side = "BID";
			output << bidprice << "," << quantity << "," << side << ",";

			// askprice
			int aska = a;
			int askxy = xy;
			int askz = z + hs;
			if (askz > 7) {
				askz -= 8;
				askxy += 1;
			}
			if (askxy > 31) {
				askxy -= 32;
				aska += 1;
			}
			A = to_string(aska);
			XY = to_string(askxy);
			Z = to_string(askz);
			if (XY.size() < 2) XY = "0" + XY;
			if (z == 4) Z = "+";
			string askprice = A + "-" + XY + Z;
			quantity = to_string((k % 5 + 1) * 1000000);
			side = "OFFER";
			output << askprice << "," << quantity << "," << side << ",";

			hs += 1;
			if (hs > 4) {
				hs = 1;
			}
		}

		output<<endl;
	}
	output.close();
}



#endif