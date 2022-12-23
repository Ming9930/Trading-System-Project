/**
 * TradesGenerator.hpp
 * generate trades.txt
 * 
 * 
 * @author: Ming Fu
 */ 
#pragma once

#ifndef TRADES_GENERATOR_HPP
#define TRADES_GENERATOR_HPP

using namespace std;

#include "BondInformation.hpp"
#include <fstream>
#include <random>
#include <vector>
#include <string>

class TradesGenerator {
public:
	// ctor
	TradesGenerator();

	// overload ( operator 
	void operator()(int n);
};

TradesGenerator::TradesGenerator() {
}

void TradesGenerator::operator()(int n) {
	ofstream output;
	output.open("trades.txt");
	// output << "cusip, tradeID, price, book, trades, B/S" << endl;
	
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
		string cusip= bondCusip[j];
		counter[j]++;
		
		j = rand() % 5;
		string tradeID;
		switch(j){
			case 0:tradeID = "Ming"; break;
			case 1:tradeID = "Dixee"; break;
			case 2:tradeID = "Ildoo"; break;
			case 3:tradeID = "Giseok"; break;
			case 4:tradeID = "Daniel"; break;
		}
		output << cusip << "," << tradeID << ",";
		
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
		output << price << ",";
		
		output<<"Book"<<",";
		// quantity
		output << to_string((rand() % 5 + 1) * 1000000) << ",";
		// Buy or sell
		output << (rand() % 2 == 0 ? "BUY" : "SELL") << endl;
		
	}
	output.close();
	return;
}
#endif